#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <cmath>
using namespace std;

struct Flor {
    double petal_length = 0.0;
    double petal_width = 0.0;
    string variety = "Nao definido";
    int grupo = 0;
};

double calculo_distancia(Flor flor, Flor representante) {
    double subtr_alt = representante.petal_length - flor.petal_length;
    double subtr_larg = representante.petal_width - flor.petal_width;
    return sqrt((subtr_alt * subtr_alt) + (subtr_larg * subtr_larg));
}

void definicao_grupos(Flor* vetor_flores, int tamanho, int k, int iteracoes) {

    Flor* representantes = new Flor[k];

    for (int i = 0; i < k; i++) {
        int indice = rand() % tamanho;
        vetor_flores[indice].grupo = i;
        representantes[i] = vetor_flores[indice];
    }

    // Repetir o processo iteracoes vezes
    for (int z = 0; z < iteracoes; z++) {
        // Alocar cada flor ao grupo mais próximo
        for (int i = 0; i < tamanho; i++) {
            double menor_distancia = calculo_distancia(vetor_flores[i], representantes[0]);
            int indice_grupo = 0;

            // Encontrar o representante mais próximo
            for (int j = 0; j < k; j++) {
                double distancia = calculo_distancia(vetor_flores[i], representantes[j]);
                if (distancia < menor_distancia) {
                    menor_distancia = distancia;
                    indice_grupo = j;
                }
            }

            // Atribuir o grupo ao representante mais próximo
            vetor_flores[i].grupo = indice_grupo;
        }

        // Atualizar os representantes
        for (int i = 0; i < k; i++) {
            int grupo_size = 0;
            double soma_largura = 0.0;
            double soma_altura = 0.0;

            for (int j = 0; j < tamanho; j++) {
                if (vetor_flores[j].grupo == i) {
                    grupo_size++;
                    soma_largura += vetor_flores[j].petal_width;
                    soma_altura += vetor_flores[j].petal_length;
                }
            }

            if (grupo_size > 0) {
                // Calcular o ponto médio das flores do grupo
                representantes[i].petal_width = soma_largura / grupo_size;
                representantes[i].petal_length = soma_altura / grupo_size;
            }
        }
    }

    // Liberar a memória alocada para os representantes
    delete[] representantes;
}

void exportar_grupos_flores(int tamanho, Flor* vetor_flores) {
    ofstream arquivo_flores_grupos("flores_grupos.csv", ios::out);

    arquivo_flores_grupos << left << setw(15) << "petal_length" << setw(15) << "petal_width" << setw(15) << "variety" << setw(15) << "group" << endl;

    for (int i = 0; i < tamanho; i++) {
        arquivo_flores_grupos << left << setw(15) << vetor_flores[i].petal_length << setw(15) << vetor_flores[i].petal_width << setw(15) << vetor_flores[i].variety << setw(15) << vetor_flores[i].grupo << endl;
    }

    arquivo_flores_grupos.close();
}

int main() {
    int tamanho = 0;
    int k = 0;
    string linha;
    string legenda;
    srand(time(NULL));

    ifstream arquivo_flores("iris_petalas.csv", ios::in);

    while (getline(arquivo_flores, linha)) {
        tamanho++;
    }

    arquivo_flores.clear();
    arquivo_flores.seekg(0, ios::beg);

    getline(arquivo_flores, legenda);

    tamanho -= 1;
    Flor* vetor_flores = new Flor[tamanho];

    for (int i = 0; i < tamanho; i++) {
        string largura, altura, especie;
        getline(arquivo_flores, largura, ',');
        getline(arquivo_flores, altura, ',');
        getline(arquivo_flores, especie, '\n');
        vetor_flores[i].petal_length = stod(largura);
        vetor_flores[i].petal_width = stod(altura);
        vetor_flores[i].variety = especie;
    }

    cout << "Digite a quantidade de grupos que voce deseja separar as flores: " << endl;
    cin >> k;

    int iteracoes = 1000;

    definicao_grupos(vetor_flores, tamanho, k, iteracoes);

    exportar_grupos_flores(tamanho, vetor_flores);

    delete[] vetor_flores;

    arquivo_flores.close();

    return 0;
}

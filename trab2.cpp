//Nome: João Victor Rocha. RA: 2177268

#include <iostream>
#include <fstream>
#include <string>  //bibliotecas usadas no código.
#include <cmath>
#include <iomanip>
using namespace std;

// struct para armazenar todos os atributos de uma flor.
struct Flor {

    double petal_length = 0.0;
    double petal_width = 0.0;
    string variety = "Nao definido";
    int grupo = 0;

};

//cálculo da distancia euclidiana entre um representante de grupo e uma flor aleatória.
double calculo_distancia(Flor flor, Flor representante) {

    double subtr_alt = representante.petal_length - flor.petal_length;
    double subtr_larg = representante.petal_width - flor.petal_width;
    return sqrt((subtr_alt * subtr_alt) + (subtr_larg * subtr_larg));

}

//formação dos grupos de flores que possuem fortes traços de similaridades.
void definicao_grupos(Flor* vetor_flores, int tamanho, int k, int iteracoes, Flor* flores_representantes) {

    for (int i = 0; i < k; i++) {

        int indice = rand() % tamanho;
        vetor_flores[indice].grupo = i;  //looping para definir todos os representantes de cada grupo.
        flores_representantes[i] = vetor_flores[indice]; //atribuição do representante ao vetor de representantes.
    }
    
    for (int z = 0; z < iteracoes; z++) {  //looping para repetir várias vezes o processo de refinamento de cada grupo criado.

        int membros_grupo = 0;
        double soma_largura = 0.0;
        double soma_altura = 0.0;

        for (int i = 0; i < tamanho; i++) {
            double menor_distancia = calculo_distancia(vetor_flores[i], flores_representantes[0]); //distancia usada como parametro.
            int numero_grupo = 0;

            for (int j = 0; j < k; j++) {
                double distancia = calculo_distancia(vetor_flores[i], flores_representantes[j]); //distancia entre um representante e uma flor.
                if (distancia < menor_distancia) { //verificação entre a distancia parametro e a calculada na linha acima.
                    menor_distancia = distancia; //se a condição for verdadeira, a nova distancia parametro é atualizada. E um grupo será atribuído a aquela flor.
                    numero_grupo = j;
                }
            }

            vetor_flores[i].grupo = numero_grupo; //atribuição do grupo a uma flor.

        }

        for (int i = 0; i < k; i++) {

            for (int j = 0; j < tamanho; j++) { //atualização do novo representante de cada grupo.
            
                if (vetor_flores[j].grupo == i) { //verificação para encontrar as flores que são do mesmo grupo que em o for externo esta percorrendo no momento.
                    membros_grupo++; //incremento do tamanho do grupo.
                    soma_largura += vetor_flores[j].petal_width; 
                    soma_altura += vetor_flores[j].petal_length;  // calculo da soma de todas as larguras e altura dos membros do grupo.
                }
            }
                flores_representantes[i].petal_width = soma_largura / membros_grupo;
                flores_representantes[i].petal_length = soma_altura / membros_grupo; // cálculo da média da largura e altura e atribuindo ao novo representante do grupo.
        }
    }
    
}

void exportar_grupos_flores(int tamanho, Flor* vetor_flores) { //escrita do novo arquivo csv com a quarta coluna de grupos.

    ofstream arquivo_flores_grupos("flores_grupos.csv", ios::out);

    arquivo_flores_grupos << left << setw(15) << "petal_length" << setw(15) << "petal_width" << setw(15) << "variety" << setw(15) << "group" << endl;

    for (int i = 0; i < tamanho; i++) {

        arquivo_flores_grupos << left << setw(15) << vetor_flores[i].petal_length << setw(15) << vetor_flores[i].petal_width << setw(15) << vetor_flores[i].variety << setw(15) << vetor_flores[i].grupo << endl;
    
    }

}

int main() {
    
    int tamanho = 0;
    int k = 0;
    int iteracoes = 2000; //declaração de variáveis.
    string linha;
    string legenda;
    srand(time(NULL));

    cout << "Digite a quantidade de grupos que voce deseja separar as flores: " << endl;

    cin >> k; // variavel que armazena a quantidade de grupos escolhida pelo usuário.

    ifstream arquivo_flores("iris_petalas.csv", ios::in); //leitura do arquivo csv.

    while (getline(arquivo_flores, linha)) {  //leitura das linhas do arquivo csv, para determinar o tamanho do vetor a ser alocado dinamicamente.
        tamanho++;
    }

    arquivo_flores.clear();     
    arquivo_flores.seekg(0, ios::beg);  //redefinindo o ponteiro para o ínicio do arquivo novamente.

    getline(arquivo_flores, legenda); //"excluindo" a legenda do arquivo. Enviando-a para a variável legenda, onde ela será inutilizada.

    tamanho -= 1; //subtraindo o tamanho por 1, devido a exclusão da legenda. Sendo assim, redefinindo a linha inicial do arquivo.

    Flor* vetor_flores = new Flor[tamanho]; //declaração de um vetor dinamico para armazenar cada linha lida do arquivo.
    Flor* flores_representantes = new Flor[k]; //vetor dinamico para armazenar os representantes de cada grupo.

    for (int i = 0; i < tamanho; i++) {               //looping para ler todas as linhas do arquivo.
        string largura, altura, especie;        
        getline(arquivo_flores, largura, ',');
        getline(arquivo_flores, altura, ',');          //variáveis para armazenar as strings que são "quebradas" pelo getline.
        getline(arquivo_flores, especie, '\n');
        vetor_flores[i].petal_length = stod(largura);  //conversão de string para número de tipo double. E atribuição dos valores para cada índice do vetor criado.
        vetor_flores[i].petal_width = stod(altura);
        vetor_flores[i].variety = especie;
    }

    definicao_grupos(vetor_flores, tamanho, k, iteracoes, flores_representantes); // função que define os representantes iniciais e a classificação dos grupos para cada flor.

    exportar_grupos_flores(tamanho, vetor_flores); // função que escreve todos os dados calculados em um novo arquivo csv.

    delete[] vetor_flores; // libera o espaço na memória que foi utilzado pelo vetor.
    delete[] flores_representantes;

    arquivo_flores.close(); // fecha o arquivo que foi importado(lido) pelo programa.
    
    system("cls");

    cout << "O arquivo com os grupos de cada flor foi criado com sucesso !!" << endl;

    cout << endl;

    return 0;

}
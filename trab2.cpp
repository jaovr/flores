#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
using namespace std;

struct Flor {
    double petal_length = 0.0;
    double petal_width = 0.0;
    string variety = "Nao definido";
    int grupo = 0;
};

void representantes_iniciais(int k, Flor *vetor_flores, int tamanho){
    srand(time(NULL));
    int indice_flor_representante = 0;
       for(int i = 1; i <= k; i++){
           indice_flor_representante = rand() % tamanho;
           vetor_flores[indice_flor_representante].grupo = i;
       }
}


int main() {

    //declaração de variaveis.
    int tamanho = 0;
    int k = 0;
    int indice_loop = 0; 
    string linha;

    ifstream arquivo_flores("iris_petalas.csv"); //importando o arquivo csv com os dados das flores.

    while (getline(arquivo_flores, linha)) {  //lendo o arquivo para definir o tamanho em que o vetor deverá alocado.
        tamanho++; 
    }

    arquivo_flores.clear(); //limpando o ponteiro.
    arquivo_flores.seekg(0, ios::beg); //redefinindo o ponteiro para o inicio do arquivo novamente.

    getline(arquivo_flores, linha); /* utilizando getline para ler o arquivo, com a finalidade de "quebrar" as virgulas que separam os dados.
                                    neste caso foi ele foi utilizado para "retirar" a legenda do arquivo */

    tamanho -= 1; //tamanho teve seu total subtraido por 1, porque após a leitura do tamanho do arquivo o resultado considerava a legenda + as 150 linhas.

    Flor *vetor_flores = new Flor[tamanho]; //criando um vetor dinamicamente e alocando na memoria.

      for (int i = 0; i < tamanho; i++) {
          string largura, altura, especie;
          getline(arquivo_flores, largura, ',');
          getline(arquivo_flores, altura, ',');   
          getline(arquivo_flores, especie);          
          vetor_flores[i].petal_length = atof(largura.c_str()); //c_str() utilizado para converter uma string em um array de char.
          vetor_flores[i].petal_width = atof(altura.c_str()); //atof() utilizado para converter um array de char para um numero tipo double. 
          vetor_flores[i].variety = especie;
          //Looping para ler todo o arquivo e em seguida, armazenar os dados no vetor que foi criado dinamicamente.
      }
 
    cout << "Insira a quantidade de flores do conjunto para serem os representantes iniciais de seus grupos" << endl;
    cin >> k;

    representantes_iniciais( k, vetor_flores, tamanho);


    delete[] vetor_flores;

    arquivo_flores.close();

    return 0;
}


#include <iostream>
#include <fstream>
#include <cassert>  // assert
#define TAM_MAX 100


using namespace std;


void lerEntrada(int *&n, const string &pathArquivo) {

        string linha, temp;

        cout<< "Arquivo: "<< pathArquivo << endl;

        ifstream arq(pathArquivo);

        assert(arq.is_open());
        assert(arq.good());

        getline(arq, linha);

        if (!linha.empty()) {

            n = new int[TAM_MAX];
            n[0] = stoi(linha);
            int i = 1;
            while (getline(arq, linha)) {
                if (!linha.empty()) {
                    n[i] = stoi(linha);
                    cout << n[i];
                    i++;
                }
            }
        }
        arq.close();

    }
     


int main(int argc, char **argv, char **argp) {

   //LER ARQUIVO ENTRADA

   //1 CASO SIMPLES: UM NUMERO POR LINHA, CADA LINHA UM VERTICE

    int *n = nullptr;  // vetor para armazenar os valores de n (qt. de vertices) lidos de "entrada.txt"
    //unsigned seed;  // semente de randomização

    const string ARQ_ENTRADA = "io\\entrada.txt";

    string ARQUIVO;

    // obtendo os parâmetros de entrada
    lerEntrada(n, ARQ_ENTRADA);


    // se for passado o nome do arquivo de entrada por parametro
    if (argc > 1)
        ARQUIVO = "io/" + (string) argv[1];

    assert(n != nullptr);
    cout << "Vetor obtido na leitura: " << n[0] << endl;

    return 0;
}

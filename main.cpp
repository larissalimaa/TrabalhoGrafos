#include <iostream>
#include <fstream>

using namespace std;

int main(int argc, char **argv, char **argp) {

    string linha;
    int i, result;

    FILE *arquivo;
    arquivo = fopen("../io/entrada.txt", "rt");

    if (arquivo != NULL)
    {
        while (!feof(arquivo)) //enquanto end of file for false continua
        {
            result =  fscanf(arquivo, "%d", &i);
            cout << i << endl;
        }
        fclose(arquivo);
    }

    else cout << "Unable to open file" << std::endl;

//    ofstream arquivo;
//    arquivo.open ("example.txt");
//    arquivo << "Writing this to a file.\n";
//    arquivo.close();

    std::cout << "Hello, World!" << std::endl;
    return 0;
}

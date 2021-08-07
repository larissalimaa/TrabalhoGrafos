#include <iostream>
#include <fstream>
#include <string>
#include <math.h>
#include <utility>
#include <tuple>
#include <iomanip>
#include <stdlib.h>
#include <chrono>
#include "Graph.h"
#include "Node.h"

using namespace std;

Graph* leitura(ifstream& input_file, int directed, int weightedEdge, int weightedNode){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;

    //Pegando a ordem do grafo
    input_file >> order;

    //Criando objeto grafo
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo

    if(!graph->getWeightedEdge() && !graph->getWeightedNode()){

        while(input_file >> idNodeSource >> idNodeTarget) {

            graph->insertEdge(idNodeSource, idNodeTarget, 0);

        }

    }else if(graph->getWeightedEdge() && !graph->getWeightedNode() ){

        float edgeWeight;

        while(input_file >> idNodeSource >> idNodeTarget >> edgeWeight) {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);

        }

    }else if(graph->getWeightedNode() && !graph->getWeightedEdge()){

        float nodeSourceWeight, nodeTargetWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {

            graph->insertEdge(idNodeSource, idNodeTarget, 0);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);

        }

    }else if(graph->getWeightedNode() && graph->getWeightedEdge()){

        float nodeSourceWeight, nodeTargetWeight, edgeWeight;

        while(input_file >> idNodeSource >> nodeSourceWeight >> idNodeTarget >> nodeTargetWeight) {

            graph->insertEdge(idNodeSource, idNodeTarget, edgeWeight);
            graph->getNode(idNodeSource)->setWeight(nodeSourceWeight);
            graph->getNode(idNodeTarget)->setWeight(nodeTargetWeight);

        }

    }

    return graph;
}

Graph* leituraInstancia(ifstream& input_file, int directed, int weightedEdge, int weightedNode){

    //Variáveis para auxiliar na criação dos nós no Grafo
    int idNodeSource;
    int idNodeTarget;
    int order;
    int numEdges;

    //Pegando a ordem do grafo
    input_file >> order >> numEdges;

    //Criando objeto grafo
    Graph* graph = new Graph(order, directed, weightedEdge, weightedNode);

    //Leitura de arquivo
    while(input_file >> idNodeSource >> idNodeTarget) {

        graph->insertEdge(idNodeSource, idNodeTarget, 0);

    }

    return graph;
}

int menu(){

    int selecao;

    cout << "MENU" << endl;
    cout << "----" << endl;
    cout << "[1] Fecho Transitivo Direto" << endl;
    cout << "[2] Fecho Transitivo Indireto" << endl;
    cout << "[3] Caminho Mínimo entre dois vértices - Djkstra" << endl;
    cout << "[4] Caminho Mínimo entre dois vértices - Floyd" << endl;
    cout << "[5] Árvore Geradora Mínima de Prim" << endl;
    cout << "[6] Árvore Geradora Mínima de Kruskal" << endl;
    cout << "[7] Imprimir caminhamento em Profundidade" << endl;
    cout << "[8] Imprimir Ordenacao Topológica" << endl;
    cout << "[0] Sair" << endl;

    cout << "\nDigite a Opcao Desejada: ";
    cin >> selecao;

    return selecao;

}

void selecionar(int selecao, Graph* graph, ofstream& arquivo_saida){

    switch (selecao) {

        //Fecho Transitivo Direto
        case 1:{
            int id;
            cout << "Digite o ID do vertice: ";
            cin >> id;
            list<int> closureD = graph->directedTransitiveClosure(id);
            list<int>::iterator it;
            cout << "Fecho Transitivo direto: " << endl;
            for(it = closureD.begin(); it != closureD.end(); it++){
                cout << *it << endl;
            }
            getchar();
            getchar();
            getchar();
            break;
        }
            //Fecho Transitivo Indireto
        case 2:{
            int id;
            cout << "Digite o ID do vertice: ";
            cin >> id;
            list<int> closureI = graph->indirectedTransitiveClosure(id);
            list<int>::iterator it;
            cout << "Fecho Transitivo direto: " << endl;
            for(it = closureI.begin(); it != closureI.end(); it++){
                cout << *it << endl;
            }
            getchar();
            getchar();
            getchar();
            break;
        }

            //Caminho Mínimo entre dois vértices - Djkstra;
        case 3:{

            break;
        }

            //Caminho Mínimo entre dois vértices - Floyd;
        case 4:{


            break;
        }

            //Árvore Geradora Mínima de Prim;
        case 5:{

            graph->agmPrim(arquivo_saida);
            break;
        }

            
        case 6:{

            graph->AGMKruskal(graph->getVertInduz(), arquivo_saida);
            //getchar();
            //getchar();
            //getchar();
            break;
        }
            //Imprimir caminhamento em Profundidade;
        case 7:{
            int id;
            list<minhaAresta> arestasArvore, arestasRetorno;
            cout << "Digite o ID do vertice: ";
            cin >> id;
            graph->profundidade(arquivo_saida, id, arestasArvore, arestasRetorno);
            list<minhaAresta>::iterator it;
            cout << "Arestas da arvore: " << endl;
            for(it = arestasArvore.begin(); it != arestasArvore.end(); it++){
                cout << "(" << (*it).origem << ","<< (*it).destino << ")" << endl;
            }
            getchar();
            getchar();

            break;
        }

        //Imprimir Ordenacao Topológica;
        case 8:{


            break;
        }

        default:
        {
            cout << " Erro!!!Opcao Invalida!!!" << endl;
        }

    }
}

int mainMenu(ofstream& arquivo_saida, Graph* graph){

    int selecao = menu();

    while(selecao != 0){

        if(arquivo_saida.is_open())
            selecionar(selecao, graph, arquivo_saida);

        else
            cout << "Unable to open the arquivo_saida" << endl;

        arquivo_saida << endl;

        system("clear");
        selecao = menu();
    }

    if(arquivo_saida.is_open()){
        arquivo_saida.close();
    }

    return 0;
}



int main(int argc, char const *argv[]) {

    //Verificação se todos os parâmetros do programa foram entrados
    if (argc != 6) {

        cout << "ERROR: Expecting: ./<program_name> <input_file> <arquivo_saida> <directed> <weighted_edge> <weighted_node> " << endl;
        return 1;

    }

    string program_name(argv[0]);
    string input_file_name(argv[1]);

    string instance;
    if(input_file_name.find("v") <= input_file_name.size()){
        string instance = input_file_name.substr(input_file_name.find("v"));
        cout << "Running " << program_name << " with instance " << instance << " ... " << endl;
    }

    //Abrindo arquivo de entrada
    ifstream input_file;
    ofstream arquivo_saida;
    input_file.open(argv[1], ios::in);
    arquivo_saida.open(argv[2], ios::out | ios::trunc);



    Graph* graph;

    if(input_file.is_open()){

        graph = leitura(input_file, atoi(argv[3]), atoi(argv[4]), atoi(argv[5]));

    }else
        cout << "Unable to open " << argv[1];

    //cout << "Impressao Grafo: " << endl;
    //for(Node *aux = graph->getFirstNode();aux != nullptr; aux = aux->getNextNode()){
        //cout << aux->getId();
        //for(Edge *adj = aux->getFirstEdge(); adj != nullptr; adj = adj->getNextEdge()){
            //cout << " -  " << adj->getTargetId() << " (" << adj->getWeight() << ")";
       // }
        //cout << endl;
    //}
    mainMenu(arquivo_saida, graph);



    //Fechando arquivo de entrada
    input_file.close();

    //Fechando arquivo de saída
    arquivo_saida.close();

    return 0;
}


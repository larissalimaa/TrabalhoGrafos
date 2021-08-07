#include "Graph.h"
#include "Node.h"
#include "Edge.h"
#include <iostream>
#include <fstream>
#include <stack>
#include <queue>
#include <list>
#include <math.h>
#include <cstdlib>
#include <ctime>
#include <float.h>
#include <iomanip>
#include <algorithm>

using namespace std;

#define INT_MAX 10000000

/**************************************************************************************************
 * Defining the Graph's methods
**************************************************************************************************/

// Constructor
Graph::Graph(int order, bool directed, bool weighted_edge, bool weighted_node)
{

    this->order = order;
    this->directed = directed;
    this->weighted_edge = weighted_edge;
    this->weighted_node = weighted_node;
    this->first_node = this->last_node = nullptr;
    this->number_edges = 0;
}

// Destructor
Graph::~Graph()
{

    Node *next_node = this->first_node;

    while (next_node != nullptr)
    {

        next_node->removeAllEdges();
        Node *aux_node = next_node->getNextNode();
        delete next_node;
        next_node = aux_node;
    }
}

// Getters
int Graph::getOrder()
{

    return this->order;
}
int Graph::getNumberEdges()
{

    return this->number_edges;
}
//Function that verifies if the graph is directed
bool Graph::getDirected()
{

    return this->directed;
}
//Function that verifies if the graph is weighted at the edges
bool Graph::getWeightedEdge()
{

    return this->weighted_edge;
}

//Function that verifies if the graph is weighted at the nodes
bool Graph::getWeightedNode()
{

    return this->weighted_node;
}

Node *Graph::getFirstNode()
{

    return this->first_node;
}

Node *Graph::getLastNode()
{

    return this->last_node;
}

void Graph::setFirstNode(Node *node)
{
    this->first_node = node;
}

void Graph::setLastNode(Node *node)
{
    this->last_node = node;
}

// Other methods
/*
    The outdegree attribute of nodes is used as a counter for the number of edges in the graph.
    This allows the correct updating of the numbers of edges in the graph being directed or not.
*/
void Graph::insertNode(int id)
{
    if (this->getFirstNode() == nullptr)
    {
        Node *node = new Node(id);
        this->setFirstNode(node);
        this->setLastNode(node);
    }
    else
    {
        if (!this->searchNode(id))
        {
            Node *node = new Node(id);
            this->getLastNode()->setNextNode(node);
            this->setLastNode(node);
        }
        else
        {
            cerr << "Error: Node " << id << " already exists" << endl;
        }
    }
}

void Graph::insertEdge(int id, int target_id, float weight)
{
    Node *node = this->getNode(id);
    Node *target_node = this->getNode(target_id);

    if (node == nullptr)
    {
        this->insertNode(id);
        node = this->getNode(id);
    }
    if (target_node == nullptr)
    {
        this->insertNode(target_id);
        target_node = this->getNode(target_id);
    }
    if (!node->searchEdge(target_id))
    {
        this->number_edges++;

        if (this->getDirected())
        {
            node->insertEdge(target_id, weight);
        }
        else
        {
            node->insertEdge(target_id, weight);
            target_node->insertEdge(id, weight);
        }
    }
    else
    {
        //cerr << "Error: Edge (" << id << "," << target_id << ") already exists" << endl;
    }
}

void Graph::removeNode(int id)
{
    if (this->searchNode(id))
    {
        Node *node_current = this->getFirstNode();
        Node *node_previous = nullptr;

        while (node_current->getId() != id)
        {
            node_previous = node_current;
            node_current = node_current->getNextNode();
        }
        if (node_previous == nullptr)
        {
            this->setFirstNode(node_current->getNextNode());
        }
        else
        {
            node_previous->setNextNode(node_current->getNextNode());
        }
        if (node_current->getNextNode() == nullptr)
        {
            this->setLastNode(node_previous);
        }
        node_current->removeAllEdges();
        delete node_current;
    }
    else
    {
        cerr << "Error: Node " << id << "does not exist" << endl;
    }
}

bool Graph::searchNode(int id)
{
    if (this->first_node != nullptr)
    {
        // Searching for a specific node of a id equal to target id
        for (Node *aux = this->first_node; aux != nullptr; aux = aux->getNextNode())
        {
            if (aux->getId() == id)
            {
                return true;
            }
        }
    }

    return false;
}

Node *Graph::getNode(int id)
{
    if (this->first_node != nullptr)
    {
        // Searching for a specific node of a id equal to target id
        for (Node *aux = this->first_node; aux != nullptr; aux = aux->getNextNode())
        {
            if (aux->getId() == id)
            {
                return aux;
            }
        }
    }
    return nullptr;
}

list <int> Graph::directedTransitiveClosureRec(list <int> &closureD, int id){
  closureD.push_back(id);

    for(Node *aux = this->getFirstNode();aux != nullptr; aux = aux->getNextNode()){
        if(aux->getId() == id){
            for(Edge *adj = aux->getFirstEdge(); adj != nullptr; adj = adj->getNextEdge()){
                int targetId = adj->getTargetId();
                if(find(closureD.begin(),closureD.end(),targetId)== closureD.end()){
                    directedTransitiveClosureRec(closureD,targetId);
                }
            }
            break;
        }
    }
    return closureD;
}

list <int> Graph::indirectedTransitiveClosureRec(list <int> &closureI, int id){

    closureI.push_back(id);
    for(Node *aux = this->getFirstNode();aux != nullptr; aux = aux->getNextNode()){
        int nodeId = aux->getId();
        for(Edge *adj = aux->getFirstEdge(); adj != nullptr; adj = adj->getNextEdge()){
            int targetId = adj->getTargetId();
            if((targetId == id) && (find(closureI.begin(),closureI.end(),nodeId)==closureI.end())){
                indirectedTransitiveClosureRec(closureI,nodeId);
                break;
            }
        }
    }
    return closureI;
}

list <int> Graph::directedTransitiveClosure(int id){

    list <int> closureD;
    directedTransitiveClosureRec(closureD,id);
    return closureD;
}

list <int> Graph::indirectedTransitiveClosure(int id){
    list <int> closureI;
    indirectedTransitiveClosureRec(closureI,id);
    return closureI;
}


void Graph::cleanVisited()
{
    /**
     * @brief Função para definir todos os nós do grafo como não visitados.
     *
     */

    Node *node = this->getFirstNode(); // Ponteiro que armazena o endereço de memória do primeiro nó do grafo.

    // Realiza a operação para todos os nós do grafo.
    while (node != nullptr)
    {
        node->setVisited(false);    // Define o nó como não visitado.
        node = node->getNextNode(); // Ponteiro passa a apontar para o próximo nó do grafo.
    }
}

//Function that prints a set of edges belongs breadth tree

void Graph::breadthFirstSearch(ofstream &output_file)
{
}

float Graph::floydMarshall(int idSource, int idTarget)
{
}

float Graph::dijkstra(int idSource, int idTarget)
{
}

//function that prints a topological sorting
void topologicalSorting()
{
}

void breadthFirstSearch(ofstream &output_file)
{
}
// Função para gerar um Subgrafo Vértice Induzido
Graph *Graph::getVertInduz()
{
    cout << "\nDigite os IDs dos vértices do subgrafo separados por ponto-vírgula" << endl;
    cout << "Ex: 2;7;3 " << endl;

    // Lendo os vértices do subgrafo
    string aux;
    cout << "Vertices: ";
    cin >> aux;

    // Vector para armazenar os ids dos vértices do subgrafo
    vector<int> idvertices;
    idvertices.clear();

    // Separando a string
    stringstream ss(aux);
    while (getline(ss, aux, ';'))
    {
        if (this->searchNode(stoi(aux)))
            idvertices.push_back(stoi(aux));
        else
            cout << "Vertice invalido, " << aux << "nao se encontra no grafo original" << endl;
    }

    // Criar o subgrafo vértice induzido
    Graph *subgrafo = new Graph(idvertices.size(), this->getDirected(), this->getWeightedEdge(), this->getWeightedNode());

    // Inserindo as arestas correspondentes no subgrafo
    this->cleanVisited();
    for (int i = 0; i < idvertices.size(); i++)
    {
        for (int j = i + 1; j < idvertices.size(); j++)

            // Verificar se a aresta realmente existe no grafo original
            if ((!this->getNode(idvertices[j])->getVisited()) && this->getNode(idvertices[i])->searchEdge(idvertices[j]))
            {
                Edge *aux = this->getNode(idvertices[i])->getEdge(idvertices[j]);
                subgrafo->insertEdge(idvertices[i], idvertices[j], aux->getWeight());
            }
        this->getNode(idvertices[i])->setVisited(true);
    }

    cout << "\nO Subgrafo X feito com sucesso! ";
    cout << "(Ordem = " << subgrafo->getOrder() << " e Numero de Arestas = " << subgrafo->getNumberEdges() << ")" << endl;

    return subgrafo;
}


bool verificaNo(minhaAresta nos_visitados[], int id_no, int id_destino, int tam)
{
    for (int i = 0; i < tam; i++)
    {
        if (nos_visitados[i].origem == id_destino && nos_visitados[i].destino == id_no)
        {
            return true;
        }
    }
    return false;
}

// A utility function to swap two elements
void swap(minhaAresta *a, minhaAresta *b)
{
    minhaAresta t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(minhaAresta arr[], int low, int high)
{
    int pivot = arr[high].peso; // pivot
    int i = (low - 1);          // Index of smaller element

    for (int j = low; j <= high - 1; j++)
    {
        // If current element is smaller than or
        // equal to pivot
        if (arr[j].peso <= pivot)
        {
            i++; // increment index of smaller element
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i + 1);
}

void quickSort(minhaAresta arr[], int low, int high)
{
    if (low < high)
    {
        /* pi is partitioning index, arr[p] is now
           at right place */
        int pi = partition(arr, low, high);

        // Separately sort elements before
        // partition and after partition
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

void Graph::showVet(minhaAresta array[], int k)
{
    cout<< "Lista:";
    for(int i=0; i<k; i++)
    {
        cout << "( " <<array[i].origem << ", " ;
        cout<< array[i].destino << " ," ;
        cout<< array[i].peso << " )" ;
    }

}

void Graph::imprimeKruskal(ofstream &arquivo_saida, minhaAresta solucao[], int numSolucao, int Ordem)
{
    cout << "imprime solucao" << endl;
    int somatorioPesos = 0;
    arquivo_saida << "---------AGM KRUSKAL---------" << endl;
    arquivo_saida << "[No_Origem -- No_Destino] - Peso" << endl;
    arquivo_saida << "-----------------------------" << endl;
    arquivo_saida << "Ordem:" << Ordem << endl;
    for (int i = 0; i < numSolucao; i++)
    {
        arquivo_saida << "[" << solucao[i].origem << "-> " << solucao[i].destino << "] - " << solucao[i].peso << endl;

        somatorioPesos += solucao[i].peso;
    }
    arquivo_saida << "Somatorio dos Pesos: " << somatorioPesos << endl;
    arquivo_saida << "Quantidade de arestas: " << numSolucao << endl;
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
}

/**
 * árvore geradora mínima gerado pelo algoritmo de Kruskal
 * @param subgrafo Subgrafo induzido com subconjunto X de vertices
 * @param arquivo_saida arquivo de saida de dados
 */
void Graph::AGMKruskal(Graph *subgrafo, ofstream &arquivo_saida)
{

    //Numero de Arestas
    int numArestas = subgrafo->getNumberEdges();

    //Numero de Nos
    int V = subgrafo->getOrder();

    //Criar uma lista L com as arestas
    minhaAresta *lista_arestas = new minhaAresta[numArestas];

    //Vetor com id dos Vertices
    int vetoridNos[V];

    //Vetor aux com subarvores de um no
    int subarvores[V];

    //Ponteiro para andar entre os nos
    Node *p = subgrafo->getFirstNode();

    //Ponteiro para andar entre as arestas
    Edge *a = p->getFirstEdge();

    //variavel auxiliar para armazenar peso
    int auxPeso;

    int i = 0;

    //percorre o this induzido preenchendo as informações das arestas

    //Percorre no subgrafo
    while (p != nullptr)
    {
        a = p->getFirstEdge();

        while (a != nullptr)
        {
            //verifica se no ja foi visitado
            if (!verificaNo(lista_arestas, p->getId(), a->getTargetId(), i))
            {
                lista_arestas[i].origem = p->getId();
                lista_arestas[i].destino = a->getTargetId();
                lista_arestas[i].peso = a->getWeight();
                i++;
            }
            a = a->getNextEdge();
        }
        p = p->getNextNode();
    }
    //showVet(lista_arestas, numArestas);

    //ordenar em ordem crescente de pesos.
    //Algoritmo de quicksorte escolhido

    quickSort(lista_arestas, 0, numArestas - 1);

    //showVet(lista_arestas, numArestas);

    //vetor com as arestas da solucao
    minhaAresta *solucao = new minhaAresta[numArestas];

    //pecorre toda a lista de arestas colocando cada uma no grafo para verificação de ciclos
    //caso o grafo possua ciclo, a aresta eh removida e nao sera colocada na solução

    //contador de numero de arestas na solucao
    int numSolucao = 0;

    //indice para solucao
    int atual = 0;

    //vetor com tamanho de Arestas
    int arvore[numArestas];

    //inicia o vetor arvore de 0 a numArestas
    for (int i = 0; i < numArestas; i++)
    {
        arvore[i] = i;
    }

    //percorre as arestas adicionando-as no vetor arvore e na solução
    int c = 0;
    while (c < numArestas)
    {
        int u = lista_arestas[c].origem;
        int v = lista_arestas[c].destino;

        if (arvore[u] != arvore[v])
        {
            solucao[atual] = lista_arestas[c];
            atual++;
            numSolucao++;
            int verticeantigo = arvore[u];
            int verticenovo = arvore[v];
            for (int j = 0; j < numArestas; j++)
            {
                if (arvore[j] == verticeantigo)
                {
                    arvore[j] = verticenovo;
                }
            }
        }
        c++;
    }
    cout<< "veio ate aqui" << endl;
    //Imprime Solução
    imprimeKruskal(arquivo_saida, solucao, numSolucao, subgrafo->getOrder());

    //desaloca
    delete[] lista_arestas;
    delete[] solucao;
}
Node *Graph::arestaMenorPeso()
{
    Node *p = this->getFirstNode();
    Node *NoMenorPeso = nullptr;
    Edge *a = p->getFirstEdge();

    int auxpeso = 0;
    int menorpeso = INT_MAX;

    //Percorre Nos
    while (p != nullptr)
    {
        //Percorre Arestas
        while (a != nullptr)
        {
            auxpeso = a->getWeight();
            if (auxpeso < menorpeso)
            {
                menorpeso = auxpeso;
                NoMenorPeso = p;
            }
            a = a->getNextEdge();
        }
        p = p->getNextNode();
    }
    return NoMenorPeso;
}

int Graph::arestaPesoDoisNos(Node *n, Node *m)
{
    //se n=m retorna 0
    if (n == m)
    {
        return 0;
    }
    //se sao adjacentes retorna peso aresta
    Node *p = n->getNextNode();
    while (p != nullptr)
    {
        if (p == m)
        {
            return p->getFirstEdge()->getWeight();
        }
        p = p->getNextNode();
    }

    //senao retorna INT_MAX
    return INT_MAX;
}

//Uma função de utilidade para encontrar o vertice com
//valor-chave mínimo, do conjunto de vértices
//ainda não incluido na AGM
int minKey(int key[], bool mstSet[], int tam)
{
    // Initialize min value
    int min = INT_MAX, min_index;

    for (int v = 0; v < tam; v++)
        if (mstSet[v] == false && key[v] < min)
            min = key[v], min_index = v;
}

//Graph *agmPrim()
void Graph::agmPrim(ofstream &output_file)
{
    output_file << "---------AGM Prim---------" << endl;
    output_file << "No -- No  |  Peso" << endl;
    output_file << "--------------------------" << endl;

    //guarda os nos com (ids) e os pesos
    int **graph;
    //guarda os menores custos
    int *mincustos = new int[this->getOrder()];
    //preenche com os vertices adjacentes
    int *maisProximo = new int[this->getOrder()];
    //para marcar os vertices visitados
    bool *visitados = new bool[this->getOrder()];

    graph = new int *[this->getOrder()];

    //preenche a matriz de adjacências com o valor INT_MAX
    for (int i = 0; i < this->getOrder(); i++)
    {
        graph[i] = new int[this->getOrder()];
        for (int j = 0; j < this->getOrder(); j++)
        {
            graph[i][j] = INT_MAX;
        }
    }

    //preenche a matriz de adjacências com o peso
    //TODO: fazer debug aqui no for -> nao esta preenchedo a matriz com os pesos, corretamente
    for (int i = 0; i < getOrder(); i++)
    {

        for (Node *p = this->getFirstNode(); p != nullptr; p = p->getNextNode())
        {
            for (Edge *a = p->getFirstEdge(); a != nullptr; a = a->getNextEdge())
            {

                cout << "a-> no destino:" << a->getTargetId() << endl;

                graph[i][a->getTargetId()] = a->getWeight();
                graph[a->getTargetId()][i] = a->getWeight();
            }
        }
    }
    cout<< "preenchi matriz graph" << endl;
    for(int i = 0; i < getOrder(); i++)
    {
        for (int j = 0; j < getOrder(); j++)
        {
            cout << "Matriz:" << endl;
            cout << "\t " << graph[i][j] << "\t ";
        }
    }

    visitados[0] = true;
    //preenche o vetor de menores custos com os menores custos da matriz de adjacências
    for (int i = 1; i < this->getOrder(); i++)
    {
        mincustos[i] = graph[0][i];
        maisProximo[i] = 0;
        visitados[i] = false;
    }

    int peso = 0;
    int atualArestas = 0;
    int verticeAnterior = 0;

    //para o tamanho do grafo
    for (int i = 0; i < this->getOrder(); i++)
    {
        int min = INT_MAX;
        int indice = 1;

        // percorre o vetor de menores custos atualizando-o de acordo com os nós já visitados
        for (int j = 0; j < this->getOrder(); j++)
        {
            if (mincustos[j] < min && !visitados[j])
            {
                min = mincustos[j];
                indice = j;
            }
        }

        //caso o indice seja 1 e o minimo sejá INT_MAX, break
        if (indice == 1 && min == INT_MAX)
        {
            break;
        }
        else
        {
            peso += min;
        }

        if (verticeAnterior == 0)
        {
            output_file << this->getOrder() << " -- " << indice << " | " << min << endl;
        }
        else if (indice == 0)
        {
            output_file << verticeAnterior << " -- " << this->getOrder() << " | " << min << endl;
        }
        else
        {
            output_file << verticeAnterior << " -- " << indice << " | " << min << endl;
        }

        verticeAnterior = indice;
        visitados[indice] = true;
        atualArestas++;
        for (int j = 1; j < this->getOrder(); j++)
        {

            if ((graph[indice][j] < mincustos[j]) && (!visitados[j]))
            {
                //mincustos representa o peso minimo requerido para ir de um ponto a outro em uma árvore
                mincustos[j] = graph[indice][j];
                maisProximo[j] = indice;
            }
        }
    }

    output_file << "--------------------------------------------------------------------------------------------------------" << endl;
    output_file << "Peso Total: " << peso << endl;
    output_file << "Numero de arestas: " << atualArestas << endl;
    output_file << "--------------------------------------------------------------------------------------------------------" << endl
                << endl;
    for (int i = 0; i < this->getOrder(); i++)
    {
        delete[] graph[i];
    }
    delete[] graph;
}

void Graph::profundidade(ofstream &arquivo_saida, int id, list<minhaAresta> &arestasArvore, list<minhaAresta> &arestasRetorno){

    list<int> visitado;
    //Graph *arvore_profundidade = new Graph(this->getOrder(),false, false, false);
    profundidadeRecursiva(id, arestasArvore, arestasRetorno, visitado);
    geraSaidaProfundidade(arquivo_saida, arestasArvore, arestasRetorno);
}

void Graph::geraSaidaProfundidade(ofstream &arquivo_saida, list<minhaAresta> arestasArvore, list<minhaAresta> arestasRetorno){
    arquivo_saida.clear();
    arquivo_saida << "graph {" << endl;
    list<minhaAresta>::iterator it;
    for(it = arestasArvore.begin(); it != arestasArvore.end(); it++){
        arquivo_saida << (*it).origem << "--"<< (*it).destino << endl;
    }
    for(it = arestasRetorno.begin(); it != arestasRetorno.end(); it++){
        arquivo_saida << (*it).origem << "--"<< (*it).destino <<  "[style=dotted]" << endl;
    }
    arquivo_saida << "}"<< endl;
}

void Graph::profundidadeRecursiva(int id, list<minhaAresta> &arestasArvore, list<minhaAresta> &arestasRetorno, list<int> &visitado){
    for(Node *aux = this->getFirstNode();aux != nullptr; aux = aux->getNextNode()){
        if(aux->getId() == id){
            visitado.push_back(id);
            for(Edge *adj = aux->getFirstEdge(); adj != nullptr; adj = adj->getNextEdge()){
                minhaAresta aresta = {id, adj->getTargetId(), 0};
                if(find(visitado.begin(), visitado.end(), adj->getTargetId()) == visitado.end()){
                    arestasArvore.push_back(aresta);
                    profundidadeRecursiva(adj->getTargetId(), arestasArvore, arestasRetorno, visitado);
                }
                else{
                    arestasRetorno.push_back(aresta);
                }
            }
            break;
        }
    }
}

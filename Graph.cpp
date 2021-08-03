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
#define INT_MAX 1000000000

using namespace std;

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
Graph *getVertexInduced(int *listIdNodes)
{
}

//Criar uma struct origem, destino, peso
/**
 * Classe que define uma aresta simples auxiliar ao algoritmo de Kruskal
 */
struct ArestaK
{
public:
    int origem;
    int destino;
    int peso;
};

bool verificaNo(ArestaK nos_visitados[], int id_no, int id_destino, int tam)
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
void swap(int *a, int *b)
{
    int t = *a;
    *a = *b;
    *b = t;
}

/* This function takes last element as pivot, places
   the pivot element at its correct position in sorted
    array, and places all smaller (smaller than pivot)
   to left of pivot and all greater elements to right
   of pivot */
int partition(ArestaK arr[], int low, int high)
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
            swap(&arr[i].peso, &arr[j].peso);
        }
    }
    swap(&arr[i + 1].peso, &arr[high].peso);
    return (i + 1);
}

void quickSort(ArestaK arr[], int low, int high)
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
/**
 * árvore geradora mínima gerado pelo algoritmo de Kruskal
 * @param arquivo_saida de saida de dados
 */
void Graph::AGMKruskal(ofstream &arquivo_saida)
{
    //Gera this induzido com subconjunto X de vertices

    //Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
    //Graph *g = new Graph(tam, 0, 1, 0);

    cout << "Entrou no algoritmo"<< endl;
    //Numero de Arestas
    int numArestas = this->getNumberEdges();

    cout << "numArestas:"<< numArestas <<endl;

    //Numero de Nos
    int V = this->getOrder();

     cout << "Ordem:"<< V <<endl;

    //Criar uma lista L com as arestas
    cout << "Criou lista arestas"<<endl;
    ArestaK *lista_arestas = new ArestaK[numArestas];

    // Isso armazenara a AGM resultante
    //Edge *result[numArestas];

    //Vetor com id dos Vertices
    int vetoridNos[V];

    //Vetor aux com subarvores de um no
    int subarvores[V];
    cout << "Ponteiros..."<<endl;
    //Ponteiro para andar entre os nos
    Node *p = this->getFirstNode();
    Edge *a = p->getFirstEdge();
    //No *p = &listaAdj[0];
    //Ponteiro para andar entre as arestas
    //Edge *a = p->getFirstEdge();

    int auxPeso;

    int contador;

    int i = 1;

    //percorre o this induzido preenchendo as informações das arestas
    cout << "Ira percorrer"<< endl;
    //percorre nos do this induzido
    for (int j = 0; j < V; j++)
    {
        //Percorre No Grafo "original"
        while (p != nullptr)
        {

            while(a != nullptr){
            //verifica se no ja foi visitado
            if (!verificaNo(lista_arestas, j, a->getTargetId(), i))
            {
                lista_arestas[i].origem = j;
                lista_arestas[i].destino = a->getTargetId();
                lista_arestas[i].peso = a->getWeight();
                i++;
            }
            a = a->getNextEdge();
            }
        }
        p = p->getNextNode();
    }
    cout << "Saiu while"<< endl;

    //ordenar em ordem crescente de pesos.

    //Algoritmo de quicksorte escolhido
    quickSort(lista_arestas, 0, numArestas - 1);

    //vetor com as arestas da solucao
    ArestaK *solucao = new ArestaK[numArestas];

    //pecorre toda a lista de arestas colocando cada uma no grafo para verificação de ciclos
    //caso o grafo possua ciclo, a aresta é removida e não será colocada na solução

    //contador de numero de arestas na solucao
    int numSolucao = 0;
    int atual = 0;
    int arvore[numArestas];

    //inicia o vetor arvore
    for (int i = 0; i < numArestas; i++)
    {
        arvore[i] = i;
    }

    //percorre as arestas adicionando-as no vetor arvore e na solução
    for (int i = 0; i < numArestas; i++)
    {
        if (arvore[lista_arestas[i].origem] != arvore[lista_arestas[i].destino])
        {
            solucao[atual] = lista_arestas[i];
            atual++;
            numSolucao++;
            int verticeAntigo = arvore[lista_arestas[i].origem];
            int novoVertice = arvore[lista_arestas[i].destino];
            for (int j = 0; j < numArestas; j++)
            {
                if (arvore[j] == verticeAntigo)
                    arvore[j] = novoVertice;
            }
        }
    }

    //Imprime Solução
    unsigned long long int somatorioPesos = 0;
    arquivo_saida << "---------AGM KRUSKAL---------" << endl;
    arquivo_saida << "[No_Origem -- No_Destino] - Peso" << endl;
    arquivo_saida << "-----------------------------" << endl;
    for (int l = 0; l < numSolucao; l++)
    {

        if (solucao[l].origem == 0)
        {
            arquivo_saida << "[" << this->getOrder() << " -> " << solucao[l].destino << "] - " << solucao[l].peso << endl;
        }
        else if (solucao[l].destino == 0)
        {
            arquivo_saida << "[" << solucao[l].origem << " -> " << this->getOrder() << "] - " << solucao[l].peso << endl;
        }
        else
        {
            arquivo_saida << "[" << solucao[l].origem << " -> " << solucao[l].destino << "] - " << solucao[l].peso << endl;
        }

        somatorioPesos += solucao[l].peso;
    }
    arquivo_saida << "Somatorio dos Pesos: " << somatorioPesos << endl;
    arquivo_saida << "Quantidade de arestas: " << numSolucao << endl;
    arquivo_saida << "--------------------------------------------------------------------------------------------------------" << endl
                  << endl;
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
            //TODO: so tem metodo primeira aresta? sera a aresta que conecta a n?
            return p->getFirstEdge()->getWeight();
        }
        p = p->getNextNode();
    }

    //senao retorna o que? inf? ou null? INFINITO 22.07
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
void agmPrim(int subVertices[], int tam)
{

    //Gera subgrafo induzido com subconjunto X de vertices

    //Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
    Graph *g = new Graph(tam, 0, 1, 0);

    int graph[tam][tam];

    //Vetor para armazenar AGM construida
    int agm[tam];

    //Valores-chave usados ​​para escolher a borda de peso mínimo no corte
    int chaves[tam];

    // Para representar o conjunto de vértices incluidos no AGM
    bool mstSet[tam];

    //Inicializar todas as chaves como INFINITE
    for (int i = 0; i < tam; i++)
        chaves[i] = INT_MAX, mstSet[i] = false;

    //Incluir o primeiro primeiro vertice na AGM.
    //Chave 0 para que primeiro vertice seja escolhido como o primeiro.
    chaves[0] = 0;
    agm[0] = -1; // O primeiro nó é sempre a raiz do AGM

    for (int i = 0; i < tam - 1; i++)
    {
        //Escolha o vértice chave mínimo do
        //conjunto de vértices ainda não incluídos na AGM
        int u = minKey(chaves, mstSet, tam);

        //Adicione o vertice escolhido ao conjunto MST
        mstSet[u] = true;

        //Atualizamos o valor da chave e o indice do
        //vértices adjacentes do vértice escolhido.
        //Consideramos apenas os vertices que não são
        //ainda incluído na AGM
        for (int v = 0; v < tam; v++)
        {

            //grafo[u][v] eh diferente de zero apenas para vertices adjacentes de m
            //mstSet[v] eh falso para vértices ainda não incluídos no MST
            //Atualize a chave apenas se o grafo[u] [v] for menor que a chave [v]
            if (graph[u][v] && mstSet[v] == false && graph[u][v] < chaves[v])
                agm[v] = u, chaves[v] = graph[u][v];
        }

    }

    //imprime a arvore AGM (armazenado em agm)
    cout<<"Aresta \tPeso\n";
    for (int i = 1; i < tam; i++)
        cout<<agm[i]<<" - "<<i<<" \t"<<graph[i][agm[i]]<<" \n";
}

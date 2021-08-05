/**************************************************************************************************
 * Implementation of the TAD Graph
**************************************************************************************************/

#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include "Node.h"
#include <fstream>
#include <stack>
#include <list>

using namespace std;

class Graph{

    //Atributes
    private:
        int order;
        int number_edges;
        bool directed;
        bool weighted_edge;
        bool weighted_node;
        Node* first_node;
        Node* last_node;
        list <int> directedTransitiveClosureRec(list <int> &closureD, int id);
        list <int> indirectedTransitiveClosureRec(list <int> &closureI, int id);

    public:
        //Constructor
        Graph(int order, bool directed, bool weighted_edge, bool weighted_node);
        //Destructor
        ~Graph();
        //Getters
        int getOrder();
        int getNumberEdges();
        bool getDirected();
        bool getWeightedEdge();
        bool getWeightedNode();
        Node* getFirstNode();
        Node* getLastNode();
        // Setters
        void setFirstNode(Node* node);
        void setLastNode(Node* node);
        //Other methods
        void insertNode(int id);
        void insertEdge(int id, int target_id, float weight);
        void removeNode(int id);
        bool searchNode(int id);
        Node* getNode(int id);
        void cleanVisited();

        //methods phase1
        list <int> directedTransitiveClosure(int id);
        list <int> indirectedTransitiveClosure(int id);
        void topologicalSorting();
        void breadthFirstSearch(ofstream& output_file);
        Graph* getVertexInduced(int* listIdNodes);
        void AGMKruskal(ofstream &arquivo_saida);
        Graph* agmKuskal();
        Node* arestaMenorPeso();
        int arestaPesoDoisNos(Node *n, Node *m);
        Graph *getVertInduz();
        Graph* agmPrim();
        void agmPrim(ofstream &arquivo_saida);
        float floydMarshall(int idSource, int idTarget);
        float dijkstra(int idSource, int idTarget);
       

        //methods phase1
        float greed();
        float greedRandom();
        float greedRactiveRandom();
    private:
        //Auxiliar methods

};

#endif // GRAPH_H_INCLUDED

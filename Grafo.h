#ifndef GRAFO_H_INCLUDED
#define GRAFO_H_INCLUDED

/** Classe Grafo
 *  Atributos
 *  ----------------
 *  @attr ordem: numero de vertices do grafo
 *  @attr grau: grau maximo entre todos os graus dentro do grafo
 *  @attr direcionado: se eh ou nao direcionado
 *  @attr direcionado: se eh ou nao direcionado
 *  @attr pondNo: se eh ou nao ponderado no noh
 *  @attr pondAresta: se eh ou nao ponderado na Aresta
 * */

using namespace std;

class Grafo {

    //Atributos
    int ordem;
    int grau;
    bool direcionado;
    bool ponderadoNo;
    bool ponderadoAresta;
    bool simples;

    //TODO: Metodos (?)
};


#endif // GRAFO_H_INCLUDED

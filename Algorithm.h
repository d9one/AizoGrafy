#ifndef AIZOGRAFY_ALGORITHM_H
#define AIZOGRAFY_ALGORITHM_H
#include "UndirectedGraph.h"


class Algorithm {
public:
    UndirectedGraph graph;

    // Konstruktor
    explicit Algorithm(UndirectedGraph graph);

    // Metoda liczaca algorytmem Prima na liscie
    list<pair<int, int>>* primList(list<pair<int, int>> *adj_list, int V);

    // Metoda liczaca algorytmem Prima na macierzy
    UndirectedGraph matrixPrim();
};


#endif //AIZOGRAFY_ALGORITHM_H

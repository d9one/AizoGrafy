#ifndef AIZOGRAFY_ALGORITHM_H
#define AIZOGRAFY_ALGORITHM_H
#include "UndirectedGraph.h"


class Algorithm {
public:
    UndirectedGraph graph;

    // Konstruktor
    Algorithm(UndirectedGraph &graph);

    // Metoda liczaca algorytmem Prima na liscie
    int primList();

    // Metoda liczaca algorytmem Prima na macierzy
    int matrixPrim();

    // Metoda liczaca algorytmem Kruskala na liscie
    int kruskList();

    // Metoda liczaca algorytmem Kruskala na macierzy
    int matrixKrusk();

    // Dekonstruktor
    ~Algorithm() = default;

};


#endif //AIZOGRAFY_ALGORITHM_H

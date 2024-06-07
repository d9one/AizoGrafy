#ifndef AIZOGRAFY_ALGORITHM_H
#define AIZOGRAFY_ALGORITHM_H
#include "Graph.h"


class Algorithm {
public:
    Graph& graph;

    // Konstruktor
    Algorithm(Graph &graph);

    // Metoda sluzaca do wyswietalnia listy
    void displayList(list<pair<int, int>>* x);

    // Metoda sluzaca do wyswietalnia macierzy
    void displayMatrix(int** x);

    // Metoda liczaca algorytmem Prima na liscie
    double primList();

    // Metoda liczaca algorytmem Prima na macierzy
    double matrixPrim();

    // Metoda liczaca algorytmem Kruskala na liscie
    double kruskList();

    // Metoda liczaca algorytmem Kruskala na macierzy
    double matrixKrusk();

    // Metoda liczaca algorytmem Dijsktry na liscie
    double dijkstraList(int start, int end);

    // Metoda liczaca alogrytmem Dijsktry na macierzy
    double dijkstraMatrix(int start, int end);

    // Metoda liczaca algorytmem Bellmana-Forda na liscie
    double bellmanFordList(int start, int end);

    // Metoda liczaca algorytmem Bellmana-Forda na matrix
    double bellmanFordMatrix(int start, int end);

    // Dekonstruktor
    ~Algorithm() = default;

};


#endif //AIZOGRAFY_ALGORITHM_H

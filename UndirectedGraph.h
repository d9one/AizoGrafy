#ifndef AIZOGRAFY_UNDIRECTEDGRAPH_H
#define AIZOGRAFY_UNDIRECTEDGRAPH_H

#include <vector>

using namespace std;

class UndirectedGraph {
public:
    int n, m;
    short int ** matrix;
    vector<vector<pair<int,int>>> list;

    // Konstruktor domyślny
    UndirectedGraph();

    // Metoda do inicjalizacji macierzy
    void initializeMatrix(int n, int m);

    // Metoda do inicjalizacji listy
    void initializeList(int m);

    // Metoda dodajaca do listy
    void addList(int v1, int v2, int weight);

    // Dekonstruktor
    ~UndirectedGraph();

};


#endif //AIZOGRAFY_UNDIRECTEDGRAPH_H

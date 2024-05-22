#ifndef AIZOGRAFY_EDGES_H
#define AIZOGRAFY_EDGES_H
#include <vector>
#include <list>

using namespace std;

class Edges {
public:
    vector<vector<pair<int, int>>> edgeList;

    // Konstruktor domyślny
    Edges() = default;

    // Inicjalizacja krawedzi;
    void initilaizeEdges(int m);

    // Metoda dodajaca krawedz
    void addEdge(int position, int v1, int v2);

    // Metoda usuwajaca krawdz
    void removeEdge(int position);

    // Metoda wyswietlajaca edges
    void displayEdges(int n, float density);


};

#endif //AIZOGRAFY_EDGES_H

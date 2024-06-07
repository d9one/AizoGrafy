#ifndef AIZOGRAFY_UNDIRECTEDGRAPH_H
#define AIZOGRAFY_UNDIRECTEDGRAPH_H

#include <vector>
#include <list>
#include <string>
#include "Edges.h"

using namespace std;

class Graph {
public:
    int n, m;
    int ** matrix;
    bool isDirected;
    list<pair<int, int>> *adj_list;
    Edges edges;

    Graph() = default;

    // Konstruktor domyślny
    Graph(int n, int m, bool isDirected);

    // Konstruktor generatora
    Graph(int n, bool isDirected);

    // Metoda do inicjalizacji macierzy
    void initializeMatrix();

    // Metoda do inicjalizacji listy
    void initializeList();

    // Metoda dodajaca do listy
    void addList(int v1, int v2, int weight=1);

    // Metoda dodajaca do macierzy incydencji
    void addMatrix(int v, int u, int position, int weight);

    // Metoda usuwajaca z listy
    void removeList(int position);

    // Metoda usuwajaca z macierzy
    void removeMatrix(int position);

    // Metoda wyswietlająca graf w postaci listy sąsiedztwa
    void displayList();

    // Metoda wyswietlajca graf w postaci macierzy incydentcji
    void displayMatrix();

    // Metoda wczytujaca graf z pliku
    static Graph loadFromFile(string filename, bool isDirected);

    // Metoda generujaca bazowe drzewo rozpinajace
    void generateGraph(bool isDirected, double density, int weight_range);

    // Metoda generująca graf o gęstości 99%
    void generateGraph99(bool isDirected, int weight_range);

    // Dekonstruktor
    ~Graph();

};


#endif //AIZOGRAFY_UNDIRECTEDGRAPH_H

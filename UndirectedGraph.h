#ifndef AIZOGRAFY_UNDIRECTEDGRAPH_H
#define AIZOGRAFY_UNDIRECTEDGRAPH_H

#include <vector>
#include <list>
#include <string>

using namespace std;

class UndirectedGraph {
public:
    int n, m;
    short int ** matrix;
    list<pair<int, int>> *adj_list;

    // Konstruktor domyślny
    UndirectedGraph(int n, int m);

    // Konstruktor generatora
    UndirectedGraph(int n, double density);

    // Metoda do inicjalizacji macierzy
    void initializeMatrix();

    // Metoda do inicjalizacji listy
    void initializeList();

    // Metoda dodajaca do listy
    void addList(int v1, int v2, int weight=1);

    // Metoda dodajaca do macierzy incydencji
    void addMatrix(int v, int position, int weight);

    // Metoda wyswietlająca graf w postaci listy sąsiedztwa
    void displayList();

    // Metoda wyswietlajca graf w postaci macierzy incydentcji
    void displayMatrix();

    // Metoda wczytujaca graf z pliku
    static UndirectedGraph loadFromFile(string filename);

    // Metoda generujaca bazowe drzewo rozpinajace
    void generateGraph();

    // Metoda generująca graf o gęstości 99%
    void generateGraph99();

    // Dekonstruktor
    ~UndirectedGraph();

};


#endif //AIZOGRAFY_UNDIRECTEDGRAPH_H

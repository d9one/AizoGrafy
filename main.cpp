#include <iostream>
#include <filesystem>
#include "UndirectedGraph.h"
#include "Algorithm.h"

using namespace std;
namespace fs = filesystem;

int main() {
    srand(time(nullptr));
//    string filename = fs::current_path().string() + "\\Files" + "\\" + "g1.txt";
//    cout << filename;
//    UndirectedGraph graph = UndirectedGraph::loadFromFile(filename);
//    UndirectedGraph graph(4, 4);
//    graph.addList(0, 1 );
//    graph.addList(0, 2 );
//    graph.addList(1, 2);
//    graph.addList(2, 3);
//    graph.addMatrix(0, 1, 1);
//    graph.addMatrix(0, 2, 2);
//    graph.addMatrix(1, 2, 3);
//    graph.addMatrix(2, 3, 4);
    UndirectedGraph graph(15, 0.99);
    graph.generateGraph99();

    graph.edges.displayEdges(15, 0.99);



    graph.displayList();
    graph.displayMatrix();

    Algorithm algorithm(graph);
    list<pair<int, int>>* MST = algorithm.primList(graph.adj_list,graph.n);
    cout << "Minimalne drzewo rozpinające:" << endl;
    for (int u = 0; u < 15; ++u) {
        cout << "Wierzchołek " << u << ": ";
        for (const auto &neighbor : MST[u]) {
            cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
        }
        cout << endl;
    }

    return 0;
}

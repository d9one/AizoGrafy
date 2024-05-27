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

    UndirectedGraph graph(8, 0.99);
    graph.generateGraph99();

    graph.displayList();
    graph.displayMatrix();

    Algorithm algorithm(graph);
    cout << algorithm.primList() << "\n";

    cout << algorithm.matrixPrim() << "\n";

    cout << algorithm.kruskList() << "\n";

    cout << algorithm.matrixKrusk() << "\n";

    return 0;
}

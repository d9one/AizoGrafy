#include "Graph.h"
#include "Menu.h"
#include "Simulation.h"
#include <filesystem>

using namespace std;
namespace fs = filesystem;

int main() {
    srand(time(nullptr));
//    string filename = fs::current_path().string() + "//Files" + "//" + "g1.txt";
//    Graph graph = Graph::loadFromFile(filename, 0);
//
    Graph graph(40, 1);
    graph.generateGraph99(1, 999);

    graph.displayList();
    graph.displayMatrix();

    Algorithm algorithm(graph);
//    cout << algorithm.primList() << " μs\n";
//
//    cout << algorithm.matrixPrim() << " μs\n";
//
//    cout << algorithm.kruskList() << " μs\n";
//
//    cout << algorithm.matrixKrusk() << " μs\n";
//
//
    cout << algorithm.dijkstraList(5, 13) << " μs\n";
    cout << algorithm.dijkstraMatrix(5, 13) << " μs\n";
    cout << algorithm.bellmanFordList(5, 13) << " μs\n";
    cout << algorithm.bellmanFordMatrix(5, 13) << " μs\n";
//    Menu::menu();
//    Simulation::simulation();

    return 0;
}

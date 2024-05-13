#include <iostream>
#include <filesystem>
#include "UndirectedGraph.h"
using namespace std;
namespace fs = filesystem;

int main() {
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
    UndirectedGraph graph(16, 0.5);
    graph.generateGraph();


    graph.displayList();
    graph.displayMatrix();
    return 0;
}

#include "UndirectedGraph.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

UndirectedGraph::UndirectedGraph(int n, int m) : n(n), m(m), adj_list(nullptr), matrix(nullptr) {
    initializeList();
    initializeMatrix();
}

UndirectedGraph::UndirectedGraph(int n, double density) : n(n), m( density * ((n *(n-1))/2)) {
    initializeList();
    initializeMatrix();
}

void UndirectedGraph::initializeMatrix(){
    matrix = new short int * [n];
    for(int i=0; i<n; i++){
        matrix[i] = new short int [m];
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            matrix[i][j]=0;
        }
    }
}

void UndirectedGraph::initializeList(){
    adj_list = new list<pair<int, int>>[n];
}

void UndirectedGraph::addList(int v1, int v2, int weight){
    adj_list[v1].emplace_back(v2, weight);
    adj_list[v2].emplace_back(v1, weight);
}

void UndirectedGraph::addMatrix(int v, int position, int weight){
    matrix[v][position] = weight;
}
void UndirectedGraph::displayList(){
    cout << "Lista sasiedztwa:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        for (const auto& edge : adj_list[i]) {
            cout << edge.first << " (" << edge.second << ") ";
        }
        cout << endl;
    }
}
void UndirectedGraph::displayMatrix(){
    cout << "Macierz incydentcji:" << endl;
    cout << "   ";
    for(int j = 0; j < m; j++){
//        cout << j << " ";
        printf("%2d ", j);
    }
    for(int i = 0; i < n; i++){
        cout << endl;
        printf("%2d ", i);
//        cout << endl << i << "  ";
        for(int j = 0; j < m; j++){
            printf(" %d ", matrix[i][j]);
//            cout << matrix[i][j] << " ";
        }
    }
}

UndirectedGraph UndirectedGraph::loadFromFile(string filename){
    ifstream file(filename);
    if(!file.is_open()){
        cerr << "Nie mozna otworzyc pliku "<< filename << endl;
        throw runtime_error("Nie mozna otworzyc pliku");
    }
    string firstLine;
    int n, m, position = 0;
    getline(file, firstLine);
    istringstream iss(firstLine);
    iss >> n >> m;
    UndirectedGraph graph(n, m);

    string line;
    while(getline(file, line)){
        int v1, v2, weight;
        istringstream iss2(line);
        iss2 >> v1 >> v2 >> weight;
        graph.addMatrix(v1, position, weight);
        graph.addMatrix(v2, position, weight);
        graph.addList(v1, v2, weight);
        position++;
    }
    file.close();
    return graph;
}

void UndirectedGraph::generateGraph(){
    for(int i=0; i<n-1; i++){
        int random = rand() % 10;
        addList(i, i+1, random);
        addMatrix(i, i, random);
        addMatrix(i+1, i, random);
    }
    int position = n;
    int counter = m -n;
    while(counter>0){
        int random1 = rand() % 10;
        int random2 = rand() % 10;
        int weight = rand() % 10 + 1;
        bool contains = false;

        for (const auto& pair : adj_list[random1]) {
            if (pair.first == random2) {
                contains = true;
                break;
            }
        }
        if(!contains){
            addList(random1, random2, weight);
            addMatrix(random1,position, weight);
            addMatrix(random2, position, weight);
            position++;
            counter--;
        }
    }
}

void UndirectedGraph::generateGraph99() {
    int toRemove = 0.99 * m;
    int position = 0;
    for(int i = 0; i< n; i++){
        for(int j = 0; j< n; j++){
            int weight = rand() % 10 + 1;
            addList(i, j, weight);
            addMatrix(i, position, weight);
            addMatrix(j, position, weight);
            position++;
        }
    }

}

UndirectedGraph::~UndirectedGraph(){
    if (matrix != nullptr) {
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
    if(adj_list != nullptr){
        delete[] adj_list;
    }
}

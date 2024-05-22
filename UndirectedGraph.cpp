#include "UndirectedGraph.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include "Edges.h"

using namespace std;

UndirectedGraph::UndirectedGraph(int n, int m) : n(n), m(m), adj_list(nullptr), matrix(nullptr), edges() {
    initializeList();
    initializeMatrix();
    edges.initilaizeEdges(m);
}

UndirectedGraph::UndirectedGraph(int n, double density) : n(n), m( density * ((n *(n-1))/2)),adj_list(nullptr), matrix(nullptr), edges(){
    initializeList();
    initializeMatrix();
    edges.initilaizeEdges(m);
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

void UndirectedGraph::removeList(int position) {
    int v1 = edges.edgeList[position].front().first;
    int v2 = edges.edgeList[position].front().second;

    adj_list[v1].remove_if([v2](const pair<int, int>& p) { return p.first == v2; });
    adj_list[v2].remove_if([v1](const pair<int, int>& p) { return p.first == v1; });
}

void UndirectedGraph::removeMatrix(int position) {
    int v1 = edges.edgeList[position].front().first;
    int v2 = edges.edgeList[position].front().second;

    matrix[v1][position] = 0;
    matrix[v2][position] = 0;
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
        graph.edges.addEdge(position, v1, v2);
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
        edges.addEdge(i, i, i+1);

    }
    int position = n-1;
    int counter = m - n + 1;
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
            edges.addEdge(position, random1, random2);
            position++;
            counter--;
        }
    }
}

void UndirectedGraph::generateGraph99() {
    int toRemove = 0.01 * m;
    int position = 0;
    for(int i = 0; i< n-2; ++i){
        for(int j = i+1; j< n; ++j){
            if(position == m){
                break;
            }
            int weight = rand() % 10 + 1;
            addList(i, j, weight);
            addMatrix(i, position, weight);
            addMatrix(j, position, weight);
            edges.addEdge(position, i, j);
            cout << i << " " << j<<endl;
            position++;
        }
    }

    for(int i = 0 ; i < toRemove; i++){
        int remove = 30;
//                rand() % position;
        if(edges.edgeList[remove].front().first == -1){
            i--;
        }
        else{
            removeList(remove);
            removeMatrix(remove);
            edges.removeEdge(remove);
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

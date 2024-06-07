#include "Graph.h"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <random>
#include "Edges.h"

using namespace std;

Graph::Graph(int n, int m, bool isDirected) : n(n), m(m), isDirected(isDirected), adj_list(nullptr), matrix(nullptr), edges() {
    if(isDirected){
        this->m = 2 * m;
    }
    initializeList();
    initializeMatrix();
    edges.initilaizeEdges(this->m);
}

Graph::Graph(int n, bool isDirected) : n(n), m(((n * (n - 1)) / 2)), isDirected(isDirected), adj_list(nullptr), matrix(nullptr), edges(){
    if(isDirected){
        this->m = 2 * m;
    }
    initializeList();
    initializeMatrix();
    edges.initilaizeEdges(m);
}

void Graph::initializeMatrix(){
    matrix = new int * [n];
    for(int i=0; i<n; i++){
        matrix[i] = new int [m];
    }
    for(int i=0; i<n; i++){
        for(int j=0; j<m; j++){
            matrix[i][j]=0;
        }
    }
}


void Graph::initializeList(){
    adj_list = new list<pair<int, int>>[n];
}

void Graph::addList(int v1, int v2, int weight){
    if(isDirected){
        adj_list[v1].emplace_back(v2, weight);
    }
    else{
        adj_list[v1].emplace_back(v2, weight);
        adj_list[v2].emplace_back(v1, weight);
    }

}

void Graph::addMatrix(int v, int u, int position, int weight){
    if(isDirected){
        matrix[v][position] = -1 * weight;
        matrix[u][position] = weight;
    }
    else{
        matrix[v][position] = weight;
        matrix[u][position] = weight;
    }
}

void Graph::removeList(int position) {
    int v1 = edges.edgeList[position].front().first;
    int v2 = edges.edgeList[position].front().second;

    adj_list[v1].remove_if([v2](const pair<int, int>& p) { return p.first == v2; });
    adj_list[v2].remove_if([v1](const pair<int, int>& p) { return p.first == v1; });
}

void Graph::removeMatrix(int position) {
    int v1 = edges.edgeList[position].front().first;
    int v2 = edges.edgeList[position].front().second;

    matrix[v1][position] = 0;
    matrix[v2][position] = 0;
}

void Graph::displayList(){
    cout << "Lista sasiedztwa:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << i << ": ";
        for (const auto& edge : adj_list[i]) {
            cout << edge.first << " (" << edge.second << ") ";
        }
        cout << endl;
    }
}
void Graph::displayMatrix(){
    cout << "Macierz incydentcji:" << endl;
    cout << "       ";
    for(int j = 0; j < m; j++){
        printf(" |%3d|" , j);
    }
    for(int i = 0; i < n; i++){
        cout << endl;
        printf("|%4d| ", i);
        for(int j = 0; j < m; j++){
            printf(" %4d ", matrix[i][j]);
        }
    }
    cout << endl;
}

Graph Graph::loadFromFile(string filename, bool isDirected){
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
    Graph graph(n, m, isDirected);

    string line;
    while(getline(file, line)){
        int v1, v2, weight;
        istringstream iss2(line);
        iss2 >> v1 >> v2 >> weight;
        graph.addMatrix(v1, v2, position, weight);
        graph.addList(v1, v2, weight);
        graph.edges.addEdge(position, v1, v2);
        position++;
    }
    file.close();
    return graph;
}

void Graph::generateGraph(bool isDirected, double density, int weight_range){

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, weight_range);
    uniform_int_distribution<> vertex_dist(0, n - 1);

    int position = 0;
    for(int i=0; i<n-1; i++){
        int random = dist(gen);
        addList(i, i+1, random);
        addMatrix(i, i+1,  position, random);
        edges.addEdge(position, i, i+1);
        position++;
    }
    if(isDirected){
        int weight = dist(gen);
        addList(n-1, 0, weight);
        addMatrix(n-1, 0, position, weight);
        edges.addEdge(position, n-1, 0);
        position++;
    }
    int counter = static_cast<int>(density * m) - n;
    while(counter > 0){
        int random1 = vertex_dist(gen);
        int random2 = vertex_dist(gen);
        int weight = dist(gen);
        bool contains = false;

        for (const auto& pair : adj_list[random1]) {
            if (pair.first == random2) {
                contains = true;
                break;
            }
        }
        if(random1 != random2 && !contains){
            addList(random1, random2, weight);
            addMatrix(random1, random2, position, weight);
            edges.addEdge(position, random1, random2);
            position++;
            counter--;
        }
    }
}

void Graph::generateGraph99(bool isDirected, int weight_range) {

    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(1, weight_range);
    uniform_int_distribution<> remove_dist(0, m - 1);

    int toRemove = static_cast<int>(0.01 * m);
    int position = 0;
    for(int i = 0; i < n-1; i++){
        for(int j = i+1; j < n; j++){
            if(position == m){
                break;
            }
            int weight = dist(gen);
            addList(i, j, weight);
            addMatrix(i, j, position, weight);
            edges.addEdge(position, i, j);
            position++;
            if(isDirected){
                int weight = dist(gen);
                addList(j, i, weight);
                addMatrix(j, i, position, weight);
                edges.addEdge(position, j, i);
                position++;
            }
        }
    }

    for(int i = 0 ; i < toRemove; i++){
        int remove = remove_dist(gen);
        if(edges.edgeList[remove].front().first == -1){
            i--;
        } else {
            removeList(remove);
            removeMatrix(remove);
            edges.removeEdge(remove);
        }
    }
}

Graph::~Graph(){
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

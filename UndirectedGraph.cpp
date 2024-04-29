#include "UndirectedGraph.h"
#include <vector>
using namespace std;

UndirectedGraph::UndirectedGraph() : n(0), m(0), matrix(nullptr) {
}

void UndirectedGraph::initializeMatrix(int n, int m){
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

void UndirectedGraph::initializeList(int n){
    list.resize(n);
}

void UndirectedGraph::addList(int v1, int v2, int weight){
    list[v1].push_back(make_pair(v2, weight));
    list[v2].push_back(make_pair(v1, weight));
}

UndirectedGraph::~UndirectedGraph(){
    if (matrix != nullptr) {
        for (int i = 0; i < n; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }
}

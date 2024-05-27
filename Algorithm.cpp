#include <queue>
#include <iostream>
#include "Algorithm.h"

using namespace std;

struct Edge{
    int u, v, weight;
};

struct CompareEdge {
    bool operator()(Edge const& e1, Edge const& e2) {
        return e1.weight > e2.weight;
    }
};

struct CompareEdgeKrusk {
    bool operator()(Edge const& e1, Edge const& e2) {
        return e1.weight < e2.weight;
    }
};

Algorithm::Algorithm(UndirectedGraph &graph){
    this->graph = graph;
}

int Algorithm::primList() {
    list<pair<int, int>>* mst = new list<pair<int, int>>[graph.n];
    bool * visited = new bool [graph.n];
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    Edge e;
    int v = 0;
    int total_weight = 0;

    for(int i = 0; i < graph.n; i++){
        visited[i] = false;
    }

    visited[v] = true;

int last = v;
    for (int i = 0; i < graph.n-1; i++) {
        for (const auto& neighbor : graph.adj_list[last]) {
            if(!visited[neighbor.first]){
                e.u = last;
                e.v = neighbor.first;
                e.weight = neighbor.second;
                pq.push(e);
            }
        }
        do{
            if(pq.empty()){
                break;
            }
            e = pq.top();
            pq.pop();
        }
        while(visited[e.v]);
        mst[e.u].emplace_back(e.v, e.weight);
        mst[e.v].emplace_back(e.u, e.weight);
        total_weight += e.weight;
        visited[e.v] = true;
        last = e.v;
    }
    cout << "Prim list:" << endl;
    for (int i = 0; i < graph.n; i++) {
        cout << i << ": ";
        for (const auto& edge : mst[i]) {
            cout << edge.first << " (" << edge.second << ") ";
        }
        cout << endl;
    }

    delete[] visited;

    return total_weight;
}

int Algorithm::matrixPrim(){
    int** mst;

    mst = new int * [graph.n];
    for(int i=0; i<graph.n; i++){
        mst[i] = new int [graph.n-1];
    }
    for(int i=0; i<graph.n; i++){
        for(int j=0; j<graph.n-1; j++){
            mst[i][j]=0;
        }
    }

    bool* visited = new bool[graph.n];
    for (int i = 0; i < graph.n; i++) {
        visited[i] = false;
    }

    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    int v = 0;
    visited[v] = true;
    int last = v;
    int counter = 0;
    int total_weight = 0;
    Edge e;

    for (int i = 0; i < graph.n-1; i++) {
        for (int j = 0; j < graph.m; j++) {
            if (graph.matrix[last][j] != 0) {
                for(int k = 0; k < graph.n; k++){
                    if(graph.matrix[k][j]==graph.matrix[last][j] && k!=last){
                        e = {last, k, graph.matrix[last][j]};
                        pq.push(e);
                    }
                }

            }
        }
        do {
            if (pq.empty()) {
                break;
            }
            e = pq.top();
            pq.pop();
        } while (visited[e.v]);
        mst[e.u][counter] = e.weight;
        mst[e.v][counter] = e.weight;
        total_weight += e.weight;
        counter++;
        visited[e.v] = true;
        last = e.v;
    }

    cout << "Prim matrix:" << endl;
    cout << "   ";
    for(int j = 0; j < graph.n-1; j++){
        printf("%2d ", j);
    }
    for(int i = 0; i < graph.n; i++){
        cout << endl;
        printf("%2d ", i);
        for(int j = 0; j < graph.n-1; j++){
            printf(" %d ", mst[i][j]);
        }
    }
    cout << endl;

    delete[] visited;
    for(int i=0; i<graph.n; i++){
        delete[] mst[i];
    }
    delete[] mst;

    return total_weight;
}

struct KruskalNode{
    int parent, weight;
    KruskalNode() = default;

    int appendNode(KruskalNode &x){
        if(x.weight > this->weight){
            this->parent = x.parent;
            x.weight += this->weight;
            return x.weight;
        } else{
            x.parent = this->parent;
            this->weight += x.weight;
            return this->weight;
        }
    }

    void setBasic(int x){
        this->parent = x;
        this->weight = 1;
    }

};
//ostream &operator<<(ostream &x, KruskalNode node){
//    x << node.parent << "\t" << node.weight;
//}

int Algorithm::kruskList(){
    list<pair<int, int>>* mst = new list<pair<int, int>>[graph.n];
    vector<Edge> edges;
    KruskalNode array[graph.n];

    int total_weight = 0;

    for (int i = 0; i < graph.n; i++) {
        array[i].setBasic(i);
    }

    for (int i = 0; i < graph.n; i++) {
        for (const auto& neighbor : graph.adj_list[i]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (i < v) {
                edges.push_back({i, v, weight});
            }
        }
    }

    sort(edges.begin(), edges.end(), CompareEdgeKrusk());

    for (const auto& edge : edges) {
        int p1 = edge.u, p2 = edge.v;
        while(array[p1].parent != p1){
            p1 = array[p1].parent;
        }
        while(array[p2].parent != p2){
            p2 = array[p2].parent;
        }
        if(p1 != p2){
            mst[edge.u].emplace_back(edge.v, edge.weight);
            mst[edge.v].emplace_back(edge.u, edge.weight);
            total_weight += edge.weight;
            if(array[p1].appendNode(array[p2]) == graph.n){
                break;
            }
        }
    }
//
//    for(int i=0 ; i< graph.n; i++){
//        cout << array[i] << "\n";
//    }

    cout << "Kruskal list:" << endl;
    for (int i = 0; i < graph.n; i++) {
        cout << i << ": ";
        for (const auto& edge : mst[i]) {
            cout << edge.first << " (" << edge.second << ") ";
        }
        cout << endl;
    }

    return total_weight;
}

int Algorithm::matrixKrusk(){
    int** mst;

    mst = new int * [graph.n];
    for(int i=0; i<graph.n; i++){
        mst[i] = new int [graph.n-1];
    }
    for(int i=0; i<graph.n; i++){
        for(int j=0; j<graph.n-1; j++){
            mst[i][j]=0;
        }
    }

    vector<Edge> edges;
    KruskalNode array[graph.n];
    int counter = 0;
    int total_weight = 0;

    for (int i = 0; i < graph.n; ++i) {
        array[i].setBasic(i);
    }

    for (int i = 0; i < graph.n; i++) {
        for (int j = 0; j < graph.m; j++) {
            if(graph.matrix[i][j]!=0){
                for(int k = 0; k < graph.n; k++){
                    if(graph.matrix[i][j]==graph.matrix[k][j] && i!=k && i<k){
                        edges.push_back({i, k, graph.matrix[i][j]});
                    }
                }
            }
        }
    }

    sort(edges.begin(), edges.end(), CompareEdgeKrusk());

    for (const auto& edge : edges) {
        int p1 = edge.u, p2 = edge.v;
        while(array[p1].parent != p1){
            p1 = array[p1].parent;
        }
        while(array[p2].parent != p2){
            p2 = array[p2].parent;
        }
        if(p1 != p2){
            mst[edge.u][counter] = edge.weight;
            mst[edge.v][counter] = edge.weight;
            counter++;
            total_weight += edge.weight;
            if(array[p1].appendNode(array[p2]) == graph.n){
                break;
            }
        }
    }
    cout << "Kruskal matrix:" << endl;
    cout << "   ";
    for(int j = 0; j < graph.n-1; j++){
        printf("%2d ", j);
    }
    for(int i = 0; i < graph.n; i++){
        cout << endl;
        printf("%2d ", i);
        for(int j = 0; j < graph.n-1; j++){
            printf(" %d ", mst[i][j]);
        }
    }
    cout << endl;
    for(int i=0; i<graph.n; i++){
        delete[] mst[i];
    }
    delete[] mst;

    return total_weight;
}

#include <queue>
#include <iostream>
#include "Algorithm.h"
#include <algorithm>

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

Algorithm::Algorithm(Graph &graph) : graph(graph) {
}

void Algorithm::displayList(list<pair<int, int>>* x){
    for (int i = 0; i < graph.n; i++) {
        cout << i << ": ";
        for (const auto& edge : x[i]) {
            cout << edge.first << " (" << edge.second << ") ";
        }
        cout << endl;
    }
}

void Algorithm::displayMatrix(int** x) {
    cout << "   ";
    for(int j = 0; j < graph.n-1; j++){
        printf("%2d ", j);
    }
    for(int i = 0; i < graph.n; i++){
        cout << endl;
        printf("%2d ", i);
        for(int j = 0; j < graph.n-1; j++){
            printf(" %d ", x[i][j]);
        }
    }
    cout << endl;
}

double Algorithm::primList() {
    auto start = chrono::high_resolution_clock::now();

    // Inicializacja listy mst, tablicy visited, kolejki priorytetowej i zmiennych pomocnicznych
    list<pair<int, int>>* mst = new list<pair<int, int>>[graph.n];
    bool * visited = new bool [graph.n];
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    Edge e;
    int v = 0;
    int total_weight = 0;

    // Inicializacja visited wartosciami false
    for(int i = 0; i < graph.n; i++){
        visited[i] = false;
    }

    // Pierwszy wierzcholek visited
    visited[v] = true;

    int last = v;
    // Algorytm prima
    for (int i = 0; i < graph.n-1; i++) {
        for (const auto& neighbor : graph.adj_list[last]) {
            if(!visited[neighbor.first]){               // Dodanie krawedzi do kolejki priorytetowej dla wiercholka last
                e.u = last;
                e.v = neighbor.first;
                e.weight = neighbor.second;
                pq.push(e);
            }
        }
        do{
            if(pq.empty()){             // Sprawdzenie czy kolejka jest pusta
                break;
            }
            e = pq.top();               // Sciagniecie krawedzi o najmniejszej wadz
            pq.pop();
        }
        while(visited[e.v]);            // Dodanie krawedzi do mst
        mst[e.u].emplace_back(e.v, e.weight);
        mst[e.v].emplace_back(e.u, e.weight);
        total_weight += e.weight;
        visited[e.v] = true;
        last = e.v;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> elapsed = end - start;

    cout << "Prim list:" << endl;
    displayList(mst);

    cout << "Suma MST: " << total_weight << endl;

    delete[] visited;           // Zwolnienie pamieci

    return elapsed.count();
}

double Algorithm::matrixPrim(){
    auto start = chrono::high_resolution_clock::now();

    // Iniciajlizacja macierzy mst
    int** mst;

    // Wypelnienie macierzy wartosciami 0
    mst = new int * [graph.n];
    for(int i=0; i<graph.n; i++){
        mst[i] = new int [graph.n-1];
    }
    for(int i=0; i<graph.n; i++){
        for(int j=0; j<graph.n-1; j++){
            mst[i][j]=0;
        }
    }

    // Inicjalizacja tablicy visisted wartosciami false
    bool* visited = new bool[graph.n];
    for (int i = 0; i < graph.n; i++) {
        visited[i] = false;
    }

    // Inicjalizacja kolejki priorytetowej i zmiennych pomocniczych
    priority_queue<Edge, vector<Edge>, CompareEdge> pq;
    int v = 0;
    visited[v] = true;
    int last = v;
    int counter = 0;
    int total_weight = 0;
    Edge e;

    // Algorytm Prima
    for (int i = 0; i < graph.n-1; i++) {
        for (int j = 0; j < graph.m; j++) {
            if (graph.matrix[last][j] != 0) {
                for(int k = 0; k < graph.n; k++){
                    if(graph.matrix[k][j]==graph.matrix[last][j] && k!=last){   // Znalezienie krawedzi z macierzy incydencji
                        e = {last, k, graph.matrix[last][j]};
                        pq.push(e);
                    }
                }

            }
        }
        do {
            if (pq.empty()) {                   // Sprawdzenie czy kolejka jest pusta
                break;
            }
            e = pq.top();                       // Sciagniecie krawedzi o najmniejszej wadz
            pq.pop();
        } while (visited[e.v]);                 // Dodanie krawedzi do mst
        mst[e.u][counter] = e.weight;
        mst[e.v][counter] = e.weight;
        total_weight += e.weight;
        counter++;
        visited[e.v] = true;
        last = e.v;
    }
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> elapsed = end - start;

    cout << "Prim matrix:" << endl;
    displayMatrix(mst);
    cout << "Suma MST: " << total_weight << endl;

    delete[] visited;                           // Zwolnienie pamieci
    for(int i=0; i<graph.n; i++){
        delete[] mst[i];
    }
    delete[] mst;

    return elapsed.count();
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

double Algorithm::kruskList(){
    auto start = chrono::high_resolution_clock::now();

    // Inicjalizacja listy mst, vectora z krawedziami oraz tablicy KruskalNode
    list<pair<int, int>>* mst = new list<pair<int, int>>[graph.n];
    vector<Edge> edges;
    KruskalNode array[graph.n];

    int total_weight = 0;

    // Ustawienie w KruskalNode wartosci poczatkowych
    for (int i = 0; i < graph.n; i++) {
        array[i].setBasic(i);
    }

    // Dodanie krawedzi do listy krawedzi
    for (int i = 0; i < graph.n; i++) {
        for (const auto& neighbor : graph.adj_list[i]) {
            int v = neighbor.first;
            int weight = neighbor.second;
            if (i < v) {
                edges.push_back({i, v, weight});
            }
        }
    }

    // Sortowanie listy krawedzi
    sort(edges.begin(), edges.end(), CompareEdgeKrusk());

    // Dodawanie krawedzi do mst z sprawdzeniem czy dodanie nie uworzy cyklu
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
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> elapsed = end - start;

    cout << "Kruskal list:" << endl;
    displayList(mst);
    cout << "Suma MST: " << total_weight << endl;

    return elapsed.count();
}

double Algorithm::matrixKrusk(){
    auto start = chrono::high_resolution_clock::now();

    // Inicjalizacja macierzy mst
    int** mst;

    // Wypelneinie macierzy wartosciami 0
    mst = new int * [graph.n];
    for(int i=0; i<graph.n; i++){
        mst[i] = new int [graph.n-1];
    }
    for(int i=0; i<graph.n; i++){
        for(int j=0; j<graph.n-1; j++){
            mst[i][j]=0;
        }
    }

    // Inicjalizacja wektora krawedzi, tablicy KruskalNode oraz zmiennych pomocniczych
    vector<Edge> edges;
    KruskalNode array[graph.n];
    int counter = 0;
    int total_weight = 0;

    // Ustawienie w KruskalNode wartosci poczatkowych
    for (int i = 0; i < graph.n; ++i) {
        array[i].setBasic(i);
    }

    // Dodanie krawedzi na podstawie macierzy incydencji
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

    // Sortowanie wektora krawedzi
    sort(edges.begin(), edges.end(), CompareEdgeKrusk());

    // Dodanie krawedzi do mst z sprawdzeniem czy dodanie nie utworzy cyklu
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
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> elapsed = end - start;

    cout << "Kruskal matrix:" << endl;
    displayMatrix(mst);
    cout << "Suam MST: " << total_weight << endl;

    for(int i=0; i<graph.n; i++){       // Zwolnienie pamieci
        delete[] mst[i];
    }
    delete[] mst;

    return elapsed.count();
}

double Algorithm::dijkstraList(int start, int end) {
    auto start1 = chrono::high_resolution_clock::now();

    // Inicializacja wektorow wartosciami startowymi
    vector<int> distances(graph.n, numeric_limits<int>::max());
    vector<int> previous(graph.n, -1);
    distances[start] = 0;

    // Inicjalizacja kolejki priorytetowej
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<>> pq;
    pq.push({0, start});

    // Algorytm dijkstry
    while (!pq.empty()) {
        int distance = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (u == end) break;

        if (distance > distances[u]) continue;

        for (const auto &neighbor : graph.adj_list[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (distances[u] + weight < distances[v]) {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push({distances[v], v});
            }
        }
    }
    // Konstruowanie ścieżki do wierzchołka końcowego
    vector<int> path;
    for (int i = end; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());

    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> elapsed = end1 - start1;

    // Wypisanie drogi i jej kosztu
    if (distances[end] == numeric_limits<int>::max()) {
        cout << "Brak sciezki z " << start << " do " << end << endl;
    } else {
        cout << "Sciezka z " << start << " do " << end << ": ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Koszt sciezki: " << distances[end] << endl;
    }

    return elapsed.count();
}

double Algorithm::dijkstraMatrix(int start, int end) {
    auto start1 = chrono::high_resolution_clock::now();

    // Inicializacja wektorow wartosciami startowymi
    vector<int> distances(graph.n, numeric_limits<int>::max());
    vector<int> previous(graph.n, -1);
    distances[start] = 0;

    // Inicjalizacja kolejki priorytetowej
    using pii = pair<int, int>;
    priority_queue<pii, vector<pii>, greater<>> pq;
    pq.push({0, start});


    // Algorytm dijkstry
    while (!pq.empty()) {
        int distance = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (u == end) break;

        if (distance > distances[u]) continue;

        for (int i = 0; i < graph.m; i++) {
            int weight = graph.matrix[u][i];

            if (weight < 0) {
                int v = -1;
                for (int j = 0; j < graph.n; j++) {
                    if (graph.matrix[j][i] == -weight) {
                        v = j;
                        break;
                    }
                }

                if (v != -1 && distances[u] - weight < distances[v]) {
                    distances[v] = distances[u] - weight;
                    previous[v] = u;
                    pq.push({distances[v], v});
                }
            }
        }
    }

    // Konstruowanie ścieżki do wierzchołka końcowego
    vector<int> path;
    for (int i = end; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());

    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> elapsed = end1 - start1;

    // Wypisanie drogi i jej kosztu
    if (distances[end] == numeric_limits<int>::max()) {
        cout << "Brak sciezki z " << start << " do " << end << endl;
    } else {
        cout << "Sciezka z " << start << " do " << end << ": ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Koszt sciezki: " << distances[end] << endl;
    }

    return elapsed.count();
}

double Algorithm::bellmanFordList(int start, int end) {
    auto start1 = chrono::high_resolution_clock::now();

    // Inicializacja wektorow wartosciami startowymi
    vector<int> distances(graph.n, numeric_limits<int>::max());
    vector<int> previous(graph.n, -1);
    distances[start] = 0;

    // Relaksacja wszystkich krawędzi n-1 razy
    for (int i = 0; i < graph.n - 1; i++) {
        for (int j = 0; j < graph.n; j++) {
            for (const auto &neighbor : graph.adj_list[j]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (distances[j] != numeric_limits<int>::max() && distances[j] + weight < distances[v]) {
                    distances[v] = distances[j] + weight;
                    previous[v] = j;
                }
            }
        }
    }

    // Konstruowanie ścieżki do wierzchołka końcowego
    vector<int> path;
    for (int i = end; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());

    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> elapsed = end1 - start1;

    // Wypisanie drogi i jej kosztu
    if (distances[end] == numeric_limits<int>::max()) {
        cout << "Brak sciezki z " << start << " do " << end << endl;
    } else {
        cout << "Sciezka z " << start << " do " << end << ": ";
        for (int i = 0; i < path.size(); i++) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Koszt sciezki: " << distances[end] << endl;
    }

    return elapsed.count();
}

double Algorithm::bellmanFordMatrix(int start, int end) {
    auto start1 = chrono::high_resolution_clock::now();

    int n = graph.n; // liczba wierzchołków
    int m = graph.m; // liczba krawędzi

    // Inicializacja wektorów wartościami startowymi
    vector<int> distances(n, numeric_limits<int>::max());
    vector<int> previous(n, -1);
    distances[start] = 0;

    // Relaksacja wszystkich krawędzi n-1 razy
    for (int i = 0; i < n - 1; i++) {
        for (int k = 0; k < m; k++) {
            int u = -1, v = -1;
            int weight = 0;

            // Znalezienie wierzchołków u i v dla krawędzi k oraz wagi krawędzi
            for (int j = 0; j < n; j++) {
                if (graph.matrix[j][k] != 0) {
                    if (u == -1) {
                        u = j;
                        weight = graph.matrix[j][k];
                    } else {
                        v = j;
                        break;
                    }
                }
            }

            // Upewnij się, że krawędź istnieje
            if (u != -1 && v != -1) {
                if (weight > 0) { // Jeśli waga jest ujemna, zamień kierunek krawędzi
                    swap(u, v);

                }
                if(weight < 0){
                    weight = - weight;
                }
                if (distances[u] != numeric_limits<int>::max() && distances[u] + weight < distances[v]) {
                    distances[v] = distances[u] + weight;
                    previous[v] = u;
                }
            }
        }
    }

    // Konstruowanie ścieżki do wierzchołka końcowego
    vector<int> path;
    for (int i = end; i != -1; i = previous[i]) {
        path.push_back(i);
    }
    reverse(path.begin(), path.end());

    auto end1 = chrono::high_resolution_clock::now();
    chrono::duration<double, micro> elapsed = end1 - start1;

    // Wypisanie drogi i jej kosztu
    if (distances[end] == numeric_limits<int>::max()) {
        cout << "Brak sciezki z " << start << " do " << end << endl;
    } else {
        cout << "Sciezka z " << start << " do " << end << ": ";
        for (size_t i = 0; i < path.size(); ++i) {
            cout << path[i];
            if (i < path.size() - 1) {
                cout << " -> ";
            }
        }
        cout << endl;
        cout << "Koszt sciezki: " << distances[end] << endl;
    }
    return elapsed.count();
}
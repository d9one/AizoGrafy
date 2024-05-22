#include <iostream>
#include "Edges.h"

using namespace std;

void Edges::initilaizeEdges(int m) {
    edgeList.resize(m);
}

void Edges::addEdge(int position, int v1, int v2) {
    edgeList[position].push_back(make_pair(v1, v2));

}

void Edges::removeEdge(int position) {
    edgeList[position].front().first = -1;
    edgeList[position].front().second = -1;
}

void Edges::displayEdges(int n, float density) {
    int m = density * ((n *(n-1))/2);
    for (int i = 0; i < m; ++i) {
        cout << "Pozycja " << i << ":";
        for (auto &edge : edgeList[i]) {
            cout << " (" << edge.first << ", " << edge.second << ")";
        }
        cout << endl;
    }
}

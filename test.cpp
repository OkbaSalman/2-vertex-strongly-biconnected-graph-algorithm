#include <iostream>
#include <vector>
#include <stack>
using namespace std;

class Graph{
    private:
    int V; // number of vertices
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) : V(V) {
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    int numberOfVertices(){
        return V;
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
    }

    bool hasEdge(int u, int v) {
        return adjMatrix[u][v] != 0;
    }

    void removeEdge(int u, int v) {
        adjMatrix[u][v] = 0;
    }

    void printAdjacencyMatrix() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }
};


int main(){

return 0;
}
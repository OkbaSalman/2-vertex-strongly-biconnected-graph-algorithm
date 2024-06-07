#include <iostream>
#include <vector>
#include <stack>
#include <algorithm>

using namespace std;

class Graph {
private:
    int V; // number of vertices
    vector<vector<int>> adjMatrix;

public:
    Graph(int V) : V(V) {
        adjMatrix.resize(V, vector<int>(V, 0));
    }

    int numberOfVertices() {
        return V;
    }

    void addEdge(int u, int v) {
        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    bool hasEdge(int u, int v) {
        return adjMatrix[u][v] != 0;
    }

    void removeEdge(int u, int v) {
        adjMatrix[u][v] = 0;
        adjMatrix[v][u] = 0;
    }

    void printAdjacencyMatrix() {
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                cout << adjMatrix[i][j] << " ";
            }
            cout << endl;
        }
    }

    void DFS(int v, vector<bool>& visited, vector<int>& parent, vector<int>& low, vector<int>& disc, int& time, vector<int>& ap, vector<pair<int, int>>& bridges) {
        visited[v] = true;
        disc[v] = low[v] = ++time;
        int children = 0;

        for (int u = 0; u < V; ++u) {
            if (adjMatrix[v][u]) {
                if (!visited[u]) {
                    children++;
                    parent[u] = v;
                    DFS(u, visited, parent, low, disc, time, ap, bridges);

                    low[v] = min(low[v], low[u]);

                    if (parent[v] == -1 && children > 1) ap[v] = true;
                    if (parent[v] != -1 && low[u] >= disc[v]) ap[v] = true;
                    if (low[u] > disc[v]) bridges.push_back({v, u});
                } else if (u != parent[v]) {
                    low[v] = min(low[v], disc[u]);
                }
            }
        }
    }

    bool allFalse(vector<int> ap){
        for (int i = 0; i < V; i++) {
        if (ap[i]) {
            return false;
        }
    }
    return true;
    }

    void findAPAndBridges() {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        vector<int> low(V, -1);
        vector<int> disc(V, -1);
        vector<int> ap(V, false);
        vector<pair<int, int>> bridges;
        int time = 0;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                DFS(i, visited, parent, low, disc, time, ap, bridges);
            }
        }

      if (!allFalse(ap)){
          cout << "Articulation Points: ";
        for (int i = 0; i < V; i++) {
            if (ap[i]) {
                cout << i << " ";
            }
        }
        cout << endl;
      }else{
        cout << "The Graph is 2-Connected." << endl;
      }

        if(!bridges.empty()){
            cout << "Bridges: ";
        for (auto bridge : bridges) {
            cout << "(" << bridge.first << ", " << bridge.second << ") ";
        }
        cout << endl;
        }else{
            cout << "The Graph is 2-Edge-Connected." << endl;
        }
    }

};

int main() {
    int V = 5; // Number of vertices
    Graph g(V);

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 0);


    g.printAdjacencyMatrix();
    g.findAPAndBridges();

    return 0;
}

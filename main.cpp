#include <iostream>
#include <vector>
#include <stack>
#include <map>

using namespace std;

struct Vertex
{
  int dfsNumber = -1;
  int finishNumber = -1;
  vector<int> neighbors; // The vertices that connected with this vertex
  int comp = -1; // The representative vertex of the component to which this vertex belongs
  vector<int> SCC; // Strongly Connected Components
  char state = 'n'; // 'n' for new; 'a' for active; 'f' for finish
};

class Graph {
private:
    int V; // number of vertices
    vector<vector<int>> adjMatrix;
    vector<vector<int>> originalAdjMatrix;
    vector<vector<int>> newAdj;
    vector<int>big,newVertx;
    int dfsCounter = 0;      
    int finishCounter = 0;   
    vector<Vertex> vertices; 
    stack<int> Rstack;       
    stack<int> Ostack;


     // check if a vertex in OStack 
  bool inOStack(int v)
  {
    stack<int> o = Ostack;
    while (!o.empty() && o.top() != v)
      o.pop();
    return !o.empty();
  }

  // main dfs function 
  void gabowDFS(int v)
  {
    vertices[v].state = 'a';
    vertices[v].dfsNumber = dfsCounter;
    dfsCounter++;
    Ostack.push(v);
    Rstack.push(v);
    for (int neighbor : vertices[v].neighbors)
    {
      if (this->vertices[neighbor].state == 'n')
        gabowDFS(neighbor);
      else if (inOStack(neighbor))
        while (vertices[neighbor].dfsNumber < vertices[Rstack.top()].dfsNumber)
          Rstack.pop();
    }
    vertices[v].state = 'f';
    vertices[v].finishNumber = finishCounter;
    finishCounter++;
    if (v == Rstack.top())
    {
      Rstack.pop();
      for (int i = 0; i < numberOfVertices(); i++)
      {
        int temp = Ostack.top();
        vertices[v].SCC.push_back(temp);
        Ostack.pop();
        vertices[temp].comp = v;
        if (temp == v)
          break;
      }
    }
  }

  // initialize the vertex.neighbors
  void verticesNeighbors()
  {
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++)
        if (hasEdge(i, j))
          vertices[i].neighbors.push_back(j);
  }



  //----------------------------------

      void JenDFS(int v, vector<bool>& visited, vector<int>& parent, vector<int>& low, vector<int>& disc, int& time, vector<int>& ap, vector<pair<int, int>>& bridges) {
        visited[v] = true;
        disc[v] = low[v] = ++time;
        int children = 0;

        for (int u = 0; u < V; ++u) {
            if (adjMatrix[v][u]) {
                if (!visited[u]) {
                    children++;
                    parent[u] = v;
                    JenDFS(u, visited, parent, low, disc, time, ap, bridges);

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


// main cmg function
  void CMG()
  {
    verticesNeighbors();
    for (int i = 0; i < vertices.size(); i++)
      if (vertices[i].state == 'n')
        gabowDFS(i);
  }


public:
    Graph(int V) : V(V) {
        adjMatrix.resize(V, vector<int>(V, 0));
        vertices.resize(V); 
        newVertx.resize(V);
    }

    int numberOfVertices() {
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

    void saveCurrentGraph() {
        originalAdjMatrix = adjMatrix;
    }

    void convertToUndirected() {
        cout<<"Making the graph undirected..."<<endl;
        for (int i = 0; i < V; ++i) {
            for (int j = 0; j < V; ++j) {
                if (adjMatrix[i][j] == 1) {
                    adjMatrix[j][i] = 1;
                }
            }
        }
    }

    void revertToDirected() {
        cout<<"Reverting the graph to directed..."<<endl;
        adjMatrix = originalAdjMatrix;
    }


    void findArticulationPointsAndBridges() {
        vector<bool> visited(V, false);
        vector<int> parent(V, -1);
        vector<int> low(V, -1);
        vector<int> disc(V, -1);
        vector<int> ap(V, false);
        vector<pair<int, int>> bridges;
        int time = 0;

        for (int i = 0; i < V; i++) {
            if (!visited[i]) {
                JenDFS(i, visited, parent, low, disc, time, ap, bridges);
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

    // print each vertex details 
  
void getTheBiggestStronglyConnectedComponent() {
    int now=0;
    CMG();
    for (int i = 0; i < V; i++) {
        if (!vertices[i].SCC.empty()) {
            int sizeV = vertices[i].SCC.size();
            if (sizeV > now) {
                now = sizeV;
                big.clear();
                for (int j = 0; j < sizeV; j++) {
                    big.push_back(vertices[i].SCC[j]);
                }
            }
        }
    }
    for (int v : big) {
        newVertx[v] = 1;
    }
}
  
  void printTheBiggestStronglyConnectedComponent(){
    if(V==big.size()){
        cout<<"All graph is strongly connected"<<endl;
    }else{
        cout<<"This is the biggest strongly connected component in this graph : {";
            for (int i = 0; i < big.size(); i++)
    {
        cout<<big[i]<<", ";
    }
    cout<<"}"<<endl;
    }

  }
  // Get new adjMatrix
 
void MakeTheBiggestStronglyConnectedComponentTheMainGraph() {
    cout<<"Making the biggest strongly connected component the main graph..."<<endl;
    int n = big.size();
    newAdj.resize(n, vector<int>(n, 0));
    map<int, int> indexMap;  // Map to keep track of new indices

    // Create index mapping for the vertices in the biggest SCC
    int newIndex = 0;
    for (int i = 0; i < V; ++i) {
        if (newVertx[i]) {
            indexMap[i] = newIndex++;
        }
    }

    // Populate the new adjacency matrix using the index mapping
    for (int i = 0; i < V; ++i) {
        if (newVertx[i]) {
            for (int j = 0; j < V; ++j) {
                if (adjMatrix[i][j] == 1 && newVertx[j] == 1) {
                    newAdj[indexMap[i]][indexMap[j]] = 1;
                }
            }
        }
    }

    // Update the main adjacency matrix and vertex count
    adjMatrix = newAdj;
    V = n;
}


};

int main() {
    int V = 8; // Number of vertices
    Graph g(V);

    g.addEdge(0, 2);
    g.addEdge(1, 0);
    g.addEdge(2, 1);
    g.addEdge(2, 3);
    g.addEdge(3, 4);
    g.addEdge(4, 5);
    g.addEdge(5, 6);
    g.addEdge(6, 7);
    g.addEdge(7, 4);


    g.printAdjacencyMatrix();
    g.getTheBiggestStronglyConnectedComponent();
    g.printTheBiggestStronglyConnectedComponent();
    g.MakeTheBiggestStronglyConnectedComponentTheMainGraph();
    g.printAdjacencyMatrix();
    g.saveCurrentGraph();
    g.convertToUndirected();
    g.findArticulationPointsAndBridges();
    g.revertToDirected();

    return 0;
}

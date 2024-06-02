#include <iostream>
#include <vector>
#include <stack>

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

class Graph
{
private:
  int V;
  vector<vector<int>> adjMatrix;
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
  void dfs(int v)
  {
    vertices[v].state = 'a';
    vertices[v].dfsNumber = dfsCounter;
    dfsCounter++;
    Ostack.push(v);
    Rstack.push(v);
    for (int neighbor : vertices[v].neighbors)
    {
      if (this->vertices[neighbor].state == 'n')
        dfs(neighbor);
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

public:
  Graph(int V) : V(V)
  {
    adjMatrix.resize(V, vector<int>(V, 0));
    vertices.resize(V); 
  }

  int numberOfVertices()
  {
    return V;
  }

  void addEdge(int u, int v)
  {
    adjMatrix[u][v] = 1;
  }

  bool hasEdge(int u, int v)
  {
    return adjMatrix[u][v] != 0;
  }

  void removeEdge(int u, int v)
  {
    adjMatrix[u][v] = 0;
  }

  void printAdjacencyMatrix()
  {
    for (int i = 0; i < V; ++i)
    {
      for (int j = 0; j < V; ++j)
      {
        cout << adjMatrix[i][j] << " ";
      }
      cout << endl;
    }
  }

  // print each vertex details 
  void printDetails()
  {
    for (int i = 0; i < V; i++)
    {
      cout << "Vertex ID : " << i << endl
           << "Vertex Component : " << vertices[i].comp << endl
           << "Vertex State : " << vertices[i].state << endl
           << "Vertex DFS Number : " << vertices[i].dfsNumber << endl
           << "Vertex Finish Number : " << vertices[i].finishNumber << endl
           << "Vertex Neighbors ID List : ";
      if (!vertices[i].neighbors.empty())
      {
        cout << "[";
        for (int j = 0; j < vertices[i].neighbors.size(); j++)
        {
          if (j == vertices[i].neighbors.size() - 1)
            cout << vertices[i].neighbors[j] << "]";
          else
            cout << vertices[i].neighbors[j] << ",";
        }
      }
      else
        cout << "No out-edges from this vertex.";
      cout << endl;
      cout << "Strongly Connected Component : ";
      if (!vertices[i].SCC.empty())
      {
        cout << "[";
        for (int j = 0; j < vertices[i].SCC.size(); j++)
        {
          if (j == vertices[i].SCC.size() - 1)
            cout << vertices[i].SCC[j] << "]";
          else
            cout << vertices[i].SCC[j] << ",";
        }
      }
      else
        cout << "This vertex isn't the special representative of the component.";
      cout << endl;
      cout << "================================\n";
    }
  }

  // main cmg function
  void CMG()
  {
    verticesNeighbors();
    for (int i = 0; i < vertices.size(); i++)
      if (vertices[i].state == 'n')
        dfs(i);
  }
};

int main()
{
  // Test 1
  Graph g = Graph(7);
  g.addEdge(6, 2);
  g.addEdge(5, 6);
  g.addEdge(5, 3);
  g.addEdge(5, 2);
  g.addEdge(4, 3);
  g.addEdge(4, 2);
  g.addEdge(3, 2);
  g.addEdge(1, 4);
  g.addEdge(1, 3);
  g.addEdge(1, 0);
  g.addEdge(0, 4);
  g.addEdge(0, 2);
  g.addEdge(0, 1);

  // Test2
  // Graph g = Graph(5);
  // g.addEdge(4, 3);
  // g.addEdge(3, 4);
  // g.addEdge(2, 3);
  // g.addEdge(2, 0);
  // g.addEdge(1, 2);
  // g.addEdge(0, 4);
  // g.addEdge(0, 1);

  g.printAdjacencyMatrix();
  g.CMG();
  g.printDetails();

  return 0;
}

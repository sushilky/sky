#include <iostream>
#include <vector>
#include <map>
#include <stack>
#include <algorithm>

using namespace std;

//Union By Rank UnionFind Data Structure
class UnionFind{
  vector<int> parent;
  vector<int> rank;

  public:
  UnionFind(int size):parent(size+1),rank(size+1) {
    for (int i = 0; i < parent.size(); i++) {
      parent[i] = i;
      rank[i] = 0;
    }
  }

  //Path Compression
  int Find(int i){
    int root;
    int base = i;
    while( i != parent[i]){
      i = parent[i];
    }
    root = i;

    while (parent[base] != root){
      i = parent[base];
      parent[base] = root;
      base = i;
    }
    return root;
  }

  // All Node a, Node b
  // O(n)
  void Union(int a, int b){
    int s1 = Find(a);
    int s2 = Find(b);
    if(rank[s1] > rank[s2]){
      parent[s2] = s1;
    }
    else if(rank[s2] > rank[s1]){
      parent[s1] = s2;
    }
    else {
      parent[s1] = s2;
      rank[s2] += 1;
    }
  }
};

typedef map<unsigned int, unsigned int> VerticesMap;

class Graph {
  UnionFind uf;
  int V, E;
  VerticesMap vertices;

  public:
  Graph(int num_nodes): uf(num_nodes),V(num_nodes){ }

  void AddVertex(int u){
    vertices[u] = u;
  }
  void Kruskal(){
    cout << "Nothing!" << endl;
    for (VerticesMap::iterator iter = vertices.begin(); iter != vertices.end(); ++iter) {
      cout << iter->first << " => " << iter->second << endl;
    }

  }
};

void ReadInput(Graph **Gptr_ptr){
  int V,B;
  cin >> V >> B;

  *Gptr_ptr = new Graph(V);
  Graph &G = **Gptr_ptr;

  unsigned int vertex;
  unsigned int bit ;
  for (int v = 1; v <= V; v++) {
    vertex = vertex & 0x00000000;
    bit = 0;
    for (int b = B; b > 0; b--) {
      cin >> bit;
      vertex = vertex | bit<<B;
    }
    G.AddVertex(vertex);

  }
}

int main(int argc, char const* argv[])
{
  Graph *G;
  ReadInput(&G);
  G->Kruskal();
  return 0;
}



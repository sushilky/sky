#include <iostream>
#include <vector>
#include <map>
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
struct Edge{
  int u;
  int v;
  int w;

  Edge(int x,int y, int z): u(x),v(y),w(z){ }
};

inline bool f_cmp_edge_cost(const Edge &e1, const Edge &e2){
  return e1.w < e2.w;

}
class Graph {
  UnionFind uf;
  int V, E;
  int **adj_matrix;
  vector<Edge> edges;

  public:
  Graph(int num_nodes, int num_edges ):
    uf(num_nodes),V(num_nodes), E(num_edges){
      adj_matrix = new int*[V+1];
      for (int v = 1; v <= V; v++) {
        adj_matrix[v] = new int[V+1];
      }
  }

  ~Graph(){
      for (int v = 1; v <= V; v++) {
         delete[] adj_matrix[v];
      }
      delete[] adj_matrix;
  }

  inline void AddEdge(int u,int v,int w){
    adj_matrix[u][v] = w;
    adj_matrix[v][u] = w;
    edges.push_back(Edge(u,v,w));
  }

  void Kruskal(){
    sort(edges.begin(),edges.end(),f_cmp_edge_cost);
    vector<Edge> mst;
    int max_dist = 0;

    for (vector<Edge>::const_iterator e = edges.begin(); e != edges.end(); ++e) {
      if(uf.Find(e->u) != uf.Find(e->v)){
        if(mst.size() == V-4) {
          max_dist = e->w;
          break;
        }
        mst.push_back(*e);
        uf.Union(e->u,e->v);
      }
    }

    cout << "MST Size = " << mst.size() << "Max Dist = " << max_dist << endl;
    for (vector<Edge>::const_iterator e = mst.begin(); e != mst.end(); ++e) {
      cout << "(" << e->u << "," << e->v << "," << e->w << ") ";
    }
    cout << endl;
  }
};

Graph ReadInput(){

}

int main(int argc, char const* argv[])
{
  int V, E;
  cin >> V;
  E = V*(V-1)/2;

  Graph G(V,E);
  int u,v,w;
  for (int e = 1; e <= E; e++) {
    cin >> u >> v >> w;
    G.AddEdge(u,v,w);
  }
  G.Kruskal();
  return 0;
}



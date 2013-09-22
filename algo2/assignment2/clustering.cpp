#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;

//Simple Union Find Data Structure
class UnionFind{
  vector<int> grp;

  public:
  UnionFind(int size):grp(size+1) {
    for (int i = 0; i < grp.size(); i++) {
      grp[i] = i;
    }
  }

  //O(1)
  int Find(int i){
    return grp[i];
  }

  // All a ==> b
  // O(n)
  void Union(int a, int b){
    for (vector<int>::iterator it = grp.begin(); it != grp.end(); ++it) {
      if(*it == a){
        *it = b;
      }
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

    for (vector<Edge>::const_iterator e = edges.begin(); e != edges.end(); ++e) {
      if(uf.Find(e->u) != uf.Find(e->v)){
        mst.push_back(*e);
        uf.Union(uf.Find(e->u),uf.Find(e->v));
      }
    }

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



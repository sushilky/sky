#include <iostream>
#include <fstream>
#include <cassert>

#include <map>
#include <set>
#include <vector>

using namespace std;

class Vdata{
  public:
    bool explored;
    std::set<int> outEdges;
    std::set<int> inEdges;

    Vdata():explored(false){ }
};

class DirectedGraph {
  std::map<int,Vdata > adjacencyList;

  public:
    void addEdge(int u,int v) {
      //Add u->v edge to the adjacency list implementation
      //cout << "Adding Edge("<< u << "," << v << ")" << endl;
      adjacencyList[u].outEdges.insert(v);
      adjacencyList[v].inEdges.insert(u);
    }

    void print() {
      //Add u->v edge to the adjacency list implementation
      for (auto v: adjacencyList) {
        cout << "V[" << v.first << "]= OUT{";
        for (auto s : v.second.outEdges) {
          cout<<s<<",";
        }
        cout<<"\b}" << endl;

        cout << "V[" << v.first << "]= IN{";
        for (auto s : v.second.inEdges) {
          cout<<s<<",";
        }
        cout<<"\b}" << endl;
      }
    }
};

int main(int argc, char const* argv[])
{
  DirectedGraph G;
  if (argc > 1) {
    ifstream ist;
    ist.open(argv[1]);
    int u,v;
    while (ist >> u >> v) {
      G.addEdge(u,v);
    }
    ist.close();
  }

  G.print();
  return 0;
}

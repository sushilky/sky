//Finding the strongly connected components (SCC) withing a graph
#include <iostream>
#include <fstream>
#include <sstream>
#include <cassert>

#include <map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;


class Vdata{
  public:
    std::set<int> outEdges;
    std::set<int> inEdges;

    Vdata(){ }
};

class DirectedGraph {
  typedef pair<int,int> EdgeKey;
  std::map<int,Vdata > nodes;
  std::map<EdgeKey,int > edges;
  public:

  void addEdge(int u,int v,int w) {
    //Add u->v edge to the adjacency list implementation
    //cout << "Adding Edge("<< u << "," << v << ")" << endl;
    nodes[u].outEdges.insert(v);
    nodes[v].inEdges.insert(u);
    edges[make_pair(u,v)] = w;
  }

  void print() {
    //Add u->v edge to the adjacency list implementation
    for (auto v: nodes) {
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

    for (auto e: edges) {
      cout << " E[" << e.first.first << "," << e.first.second << "]= " << e.second ;
    }
    cout << endl;
  }

  map<int,int> dijkstra(int s){
    map<int,int> shortest_paths;
    set<int> X; //Set of points that are processed so far
    set<int> V; //Set of all vertices in the Graph

    //Initialize the variables
    for(auto v: nodes) {
      V.insert(v.first);
      shortest_paths[v.first]=1000000;
    }
    shortest_paths[s]=0;
    X.insert(s);

    while (X != V){
      pair<int,int> min_edge;
      int short_path = 1000000;

      for(auto e: edges){
        if(X.find(e.first.first) != X.end()
            && X.find(e.first.second) == X.end() ) {
          if(shortest_paths[e.first.first] + e.second < short_path) {
            min_edge.first = e.first.first;
            min_edge.second = e.first.second;
            short_path = shortest_paths[e.first.first] + e.second;
          }
        }
      }
      assert(short_path < 1000000);
      X.insert(min_edge.second);
      shortest_paths[min_edge.second] = short_path;
    }

    return shortest_paths;
  }
};

template<typename X,typename Y>
ostream& operator<<(ostream &os, std::pair<X,Y> pair) {
  os << "(" << pair.first << "," << pair.second << ")";
  return os;
}

template <typename ValueType>
void print_set(set<ValueType> S){
  cout << "Set = {";
  for(auto s: S){
    cout << s << ",";
  }
  cout << "\b" << endl;
}

template <typename KeyType,typename ValueType>
void print_map(map<KeyType,ValueType> m){
  for(auto k: m){
    cout << "Map[" << k.first << "]\t=\t"<< k.second << endl;
  }
}


int main(int argc, char const* argv[])
{
  DirectedGraph G;
  if (argc > 1) {
    ifstream ist;
    ist.open(argv[1]);

    string line;
    int u,v,w;
    while (getline(ist,line,'\n')) {
      istringstream ss(line);
      ss >> u;
      char dummy;
      while(ss >> v >> dummy >> w ) {
        G.addEdge(u,v,w);
      }
    }
    ist.close();

  }
  //G.print();
  map<int,int> shortest_distances;
  shortest_distances = G.dijkstra(1);

  print_map(shortest_distances);
  int nodes[10]= {7,37,59,82,99,115,133,165,188,197};
  for(auto i: nodes) {
    cout << shortest_distances[i] << ",";
  }
  cout << endl;

  return 0;
}


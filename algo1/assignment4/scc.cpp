//Finding the strongly connected components (SCC) withing a graph
#include <iostream>
#include <fstream>
#include <cassert>

#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <algorithm>

using namespace std;


class Vdata{
  public:
    bool time_explored;
    bool leader_explored;
    std::set<int> outEdges;
    std::set<int> inEdges;

    int finish_time;
    int leader;

    Vdata(): time_explored(false), leader_explored(false), finish_time(0){ }
};

class DirectedGraph {
  std::tr1::unordered_map<int,Vdata > adjacencyList;
  std::vector<int> finished_array;
  int total_nodes;
  //Globals
  int t; //Tracking finish time for the first pass
  int s; //Tracking Leader

  std::map<int,int> sccmap;
  //Depth First Search (DFS) Algorithms
  // Input: node i

  void DFS_First(int i){

    adjacencyList[i].time_explored = true;

    for (auto j : adjacencyList[i].inEdges ) {
      if(adjacencyList[j].time_explored == false){
        DFS_First(j);
      }
    }
    t++;
    adjacencyList[i].finish_time = t;
    finished_array.push_back(i);
    //cout << "(iter = " << i << ", time = " << t << ")";
    //print_finished_array();
  }

  void print_finished_array(){

    cout << "Finish Array[" << finished_array.size() << "] = ";
    for (auto a : finished_array) {
      cout << a << " ";
    }
    cout << endl;
  }
  //Depth First Search (DFS) Algorithms
  // Input: node i

  void DFS_Second(int i){

    adjacencyList[i].leader_explored = true;
    adjacencyList[i].leader   = s;
    //cout << "DFS_Second(i=" << i << " s=" << s << ")" << endl;

    for (auto j : adjacencyList[i].outEdges ) {
      if(adjacencyList[j].leader_explored == false){
        DFS_Second(j);
      }
    }
  }

  public:
  DirectedGraph():total_nodes(0),t(0),s(0) {
    //Nothing to do
  }

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

  //DFS_Loop First Pass
  void DFS_Loop_First(){
    t = 0;
    for (int i = adjacencyList.size(); i >=1; i--) {
      if(adjacencyList[i].time_explored == false){
        DFS_First(i);
      }
    }
  }

  //DFS_Loop Second Pass
  void DFS_Loop_Second(){

    s = 0;

    for (auto v = finished_array.rbegin();v!= finished_array.rend() ; v++){
      if(adjacencyList[*v].leader_explored == false){
        s = *v;
        DFS_Second(*v);
      }
    }
  }

  void CountSCCs(){
    for (auto v: adjacencyList) {
      if(sccmap.find(v.second.leader) != sccmap.end()){
        sccmap[v.second.leader]++;
      }
      else{
        sccmap[v.second.leader] = 1;
      }
    }
  }

  void PrintSCCs(){
    vector<int> scc;
    for (auto s: sccmap) {
      //cout << "SCC["<< s.first <<"] = " << s.second << endl;
      scc.push_back(s.second);
    }

    sort(scc.begin(),scc.end(),greater<int>());
    //sort(scc.rbegin(),scc.rend());
    int counter = 1;
    for (auto s: scc) {
      cout << s << "," ;
      if (counter++ == 10) break;

    }
    cout << "\b" << endl;
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

  G.DFS_Loop_First();
  G.DFS_Loop_Second();

  G.CountSCCs();
  G.PrintSCCs();

  return 0;
}


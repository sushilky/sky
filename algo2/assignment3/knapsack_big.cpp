#include <iostream>
#include <climits>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

struct item{
  int v;
  int w;
};

vector<item> items;
typedef std::pair<int,int> KSKey;
typedef std::map<KSKey,unsigned long long int> Knapsack;
Knapsack K;

unsigned long long int GetKnapsack(int i,int x){
  if (i<1 || x<1) return 0;

  KSKey kix(i,x);
  Knapsack::iterator it= K.find(kix);
  if(it != K.end()){
    return it->second;
  }
  KSKey ki1x(i-1,x),ki1x_w(i-1,x-items[i].w);
  unsigned long long int A = GetKnapsack(i-1,x);
  if(x-items[i].w > 0){
  unsigned long long int B = GetKnapsack(ki1x_w.first,ki1x_w.second);
    K[kix] = max(A,B+items[i].v);
  }
  else {
    K[kix] = A;
  }
  return K[kix];

}

void print_map(){
  for (Knapsack::const_iterator iter = K.begin(); iter != K.end(); ++iter) {
    cout << "K(" << iter->first.first << "," << iter->first.second << ") = " << iter->second << endl;
  }
}
int main(int argc, char const* argv[])
{
  int W,N;
  cin >> W >> N;

  items.resize(N+1);
  items[0].v = items[0].w = 0;
  for (int i = 1; i <= N; i++) {
    cin >> items[i].v >> items[i].w;
  }

  cout << "Stolen Value W=" << W << " N=" << N << "= " << GetKnapsack(N,W) << endl;
  //print_map();
  return 0;
}

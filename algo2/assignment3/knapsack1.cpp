#include <iostream>
#include <climits>
#include <iomanip>
#include <cstdio>
#include <vector>
#include <map>

using namespace std;

long long A[20][20] = {{0.0}};

struct item{
  int v;
  int w;
};

typedef std::pair<int,int> KSKey;
typedef std::map<KSKey,unsigned long long int> Knapsack;

int main(int argc, char const* argv[])
{
  int W,N;
  cin >> W >> N;
  Knapsack K;

  vector<item> items(N+1);
  for (int i = 1; i <= N; i++) {
    cin >> items[i].v >> items[i].w;
  }

  for (int x = 0; x <= W; x++) {
    K[KSKey(0,x)] = 0;
  }

  for (int i = 1; i <= N; i++) {
    for (int x = 0; x <= W; x++) {
      if( x-items[i].w < 0){
        K[KSKey(i,x)] = K[KSKey(i-1,x)];
      } else {
        K[KSKey(i,x)] = max(K[KSKey(i-1,x)],items[i].v + K[KSKey(i-1,x-items[i].w)]);
      }
    }
  }

  cout << "Stolen Value W=" << W << " N=" << N << "= " << K[KSKey(N,W)] << endl;
  return 0;
}

#include <iostream>
#include <climits>
#include <iomanip>
#include <cstdio>

using namespace std;

float A[20][20] = {{0.0}};

void print_matrix(){
  for (int i = 1; i <= 7; i++) {
    for (int j = 1; j <= 7; j++) {
      printf("  %-2.2f",A[i][j]);
    }
    cout << endl;
  }
  cout << endl;
}

float get_A(int i,int j){
  if(i>j || i<1 || j<1 || i>7 || j>7) return 0;
  return A[i][j];
}

int main(int argc, char const* argv[])
{
  int N = 7;
  float P[8] = {0.0,.05,.4,.08,.04,.1,.1,.23};
  for (int j = 0; j <= N; j++) {
    A[j][j] = P[j];
  }
  print_matrix();

  float min;
  for (int s = 0; s <= N-1; s++) {
    for (int i = 1; i <= N; i++) {
      float sum = 0.0;
      for (int k = i; k <= i+s; k++) {
        sum +=  P[k];
      }
      min = 10000;
      for (int r = i; r <= i+s; r++) {
        if(min > sum + get_A(i,r-1) + get_A(r+1,i+s))
          min = sum + get_A(i,r-1) + get_A(r+1,i+s);
      }
      A[i][i+s] = min;
    }
  }
  cout << "Optimal BST = " << A[1][N] << endl;
  print_matrix();
  return 0;
}

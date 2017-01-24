#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_N 100000

char path[MAX_N+1];

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  int n, a, b;
  scanf( "%*d %d %d\n%s", &a, &b, path );
  printf( "%d", (path[a-1] == path[b-1]) ? 0 : 1 );
}

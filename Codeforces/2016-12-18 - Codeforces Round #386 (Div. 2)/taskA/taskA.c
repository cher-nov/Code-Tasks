#include <stdlib.h>
#include <stdio.h>

int min3( int aa, int bb, int cc ) {
  int r = (aa < bb) ? aa : bb;
  return (cc < r) ? cc : r;
}

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  int a, b, c;
  scanf( "%d\n%d\n%d", &a, &b, &c );

  int n = min3( a, b/2, c/4 );
  printf( "%d", n+(n*2)+(n*4) );
}

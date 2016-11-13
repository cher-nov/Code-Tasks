#include <stdlib.h>
#include <stdio.h>

int min3( int a, int b, int c ) {
  int r = (a < b) ? a : b;
  if (c < r) { r = c; }
  return r;
}

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  int c3=0, c2=0, c5=0, c6=0;
  scanf( "%d %d %d %d", &c2, &c3, &c5, &c6 );

  int m256 = min3( c2, c5, c6 );
  c2 -= m256;
  int m32 = (c3 < c2) ? c3 : c2;

  printf( "%d", 256 * m256 + 32 * m32 );
}

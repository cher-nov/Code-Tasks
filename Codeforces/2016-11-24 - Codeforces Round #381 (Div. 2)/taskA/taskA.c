#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

uint64_t min3( uint64_t a, uint64_t b, uint64_t c ) {
  uint64_t r = (a < b) ? a : b;
  if (c < r) {r = c;}
  return r;
}

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  uint64_t n, a1, b2, c3;
  scanf( "%I64u %I64u %I64u %I64u", &n, &a1, &b2, &c3 );

  uint64_t cost;
  switch (n % 4) {
    case 3: cost = min3( a1, b2+c3, 3*c3 ); break;
    case 2: cost = min3( 2*a1, b2, 2*c3 ); break;
    case 1: cost = min3( 3*a1, a1+b2, c3 ); break;
    case 0: cost = 0; break;
  }

  printf( "%I64u", cost );
  return 0;
}

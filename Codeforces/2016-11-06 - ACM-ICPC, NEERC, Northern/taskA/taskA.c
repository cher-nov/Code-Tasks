#include <stdlib.h>
#include <stdio.h>

int main() {
  freopen( "anniversary.in", "r", stdin );
  #ifdef ONLINE_JUDGE
  freopen( "anniversary.out", "w", stdout );
  #endif

  int w, h, ax, ay, bx, by;
  scanf( "%d %d %d %d %d %d", &w, &h, &ax, &ay, &bx, &by );

  int sx, sy, ex, ey;
  if (ax == bx) {
    sx = 0;
    sy = ay;
    ex = w;
    ey = by;
  } else {
    sx = ax;
    sy = 0;
    ex = bx;
    ey = h;
  }

  printf( "%d %d %d %d", sx, sy, ex, ey );
  return EXIT_SUCCESS;
}

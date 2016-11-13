#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

int dd, mm, yy;

bool check( int d1, int m1, int y1 ) {
  const int leap_days[] = {31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

  if (m1 > 12) { return false; }
  if (d1 > leap_days[m1-1]) { return false; }
  if ( (m1 == 2) && (y1 % 4 != 0) && (d1 > 28) ) { return false; }

  int diff = yy - y1;
  if (diff == 18) {
    if (m1 == mm) { return (d1 <= dd); }
    return (m1 < mm);
  }

  return (diff > 18);
}

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  int bd, bm, by;
  scanf( "%d.%d.%d\n%d.%d.%d", &dd, &mm, &yy, &bd, &bm, &by );

  bool result = (
    check(bd, bm, by) || check(bd, by, bm) ||
    check(bm, by, bd) || check(bm, bd, by) ||
    check(by, bd, bm) || check(by, bm, bd)
  );

  printf( result ? "YES" : "NO" );
}

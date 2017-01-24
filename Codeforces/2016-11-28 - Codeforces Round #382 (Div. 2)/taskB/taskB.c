#include <stdlib.h>
#include <stdio.h>
#include <inttypes.h>

#define MAX_CITIZENS 100000

int citizens[MAX_CITIZENS];

int cmp_sort( const void* a, const void* b ) {
  // a - b : ascending sort
  // b - a : descending sort
  return (*(int*)b) - (*(int*)a);
}

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  int n, n1, n2;
  scanf( "%d %d %d\n", &n, &n1, &n2 );
  for( int i = 0; i < n; ++i ) {
    scanf( "%d", &citizens[i] );
  }

  qsort( citizens, n, sizeof(int), &cmp_sort );

  int nmax, nmin;
  if (n1 < n2) {
    nmin = n1;
    nmax = n2;
  } else {
    nmin = n2;
    nmax = n1;
  }

  uint64_t sum1min = 0, sum2max = 0;
  for( int i = 0; i < nmin; ++i ) {
    sum1min += citizens[i];
  }
  for( int i = nmin; i < nmin+nmax; ++i ) {
    sum2max += citizens[i];
  }

  float max_average = ((float)sum1min / nmin) + ((float)sum2max / nmax);
  printf( "%f", max_average );
}

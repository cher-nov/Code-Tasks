#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

int hall_n, hall_m; //height, width

int cmp_int( const void* a, const void* b ) {
  return ( *(int*)a - *(int*)b );
}

bool place( bool hall[hall_n][hall_m], int queue[], int qlen, bool rightscan ) {
  for( int k = 0; k < qlen; ++k ) {
    int hor, ver;

    if (queue[k] < 2) { return false; }

    queue[k] -= 2;
    hor = queue[k] - hall_n + 2;
    bool placed = false;

    if (hor < 1) {
      hor = 1;
      ver = queue[k] + 1;
    } else {
      ver = hall_n;
    }

    while ( (ver > 0) && (!placed) ) {
      for( int j = 0; j < hor; ++j ) {
        int col = rightscan ? (hall_m-j-1) : j;
        if (!hall[ver-1][col]) {
          hall[ver-1][col] = true;
          placed = true;
          break;
        }
      }
      --ver;
      if (hor < hall_m) {++hor;}
    }

    if (!placed) {
      return false;
    }
  }

  return true;
}

int main() {

  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  scanf( "%d %d\n", &hall_n, &hall_m );

  bool hall[hall_n][hall_m];
  memset( hall, 0, sizeof(hall) );

  int q1_len;
  scanf( "%d", &q1_len );
  int queue1[q1_len];
  for( int k = 0; k < q1_len; ++k ) {
    scanf( "%d", &queue1[k] );
  }

  int q2_len;
  scanf( "\n%d", &q2_len );
  int queue2[q2_len];
  for( int k = 0; k < q2_len; ++k ) {
    scanf( "%d", &queue2[k] );
  }

  qsort( queue1, q1_len, sizeof(int), &cmp_int );
  if ( !place( hall, queue1, q1_len, false ) ) {
    printf("NO");
    return 0;
  }

  qsort( queue2, q2_len, sizeof(int), &cmp_int );
  if ( !place( hall, queue2, q2_len, true ) ) {
    printf("NO");
    return 0;
  }

  #ifndef ONLINE_JUDGE
  for( int i = 0; i < hall_n; ++i ) {
    for( int j = 0; j < hall_m; ++j ) {
      printf("%d ", hall[i][j]);
    }
    puts("");
  }
  #endif

  printf("YES");
  //while (1);
  return 0;
}

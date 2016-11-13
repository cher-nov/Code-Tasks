#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#define NOT_A_PLANET (-1)
#define MAX_FUEL_TYPE 300000

int next_planet[MAX_FUEL_TYPE] = {[0 ... MAX_FUEL_TYPE-1] = NOT_A_PLANET};
int fuel_pl[MAX_FUEL_TYPE] = {[0 ... MAX_FUEL_TYPE-1] = NOT_A_PLANET};

int main() {
  FILE* fin = fopen( "expedition.in", "r" );
  int n;
  fscanf( fin, "%d", &n );

  for(int i = 0; i < n; ++i) {
    int fuel;
    fscanf( fin, "%d", &fuel );
    fuel -= 1;
    if ( fuel_pl[fuel] != NOT_A_PLANET ) {
      next_planet[ fuel_pl[fuel] ] = i;
    }
    fuel_pl[fuel] = i;
  }

  fclose( fin );

  int result[n];
  result[0] = 0;
  int out_cnt = 1;

  int start, new_result;
  int max_last = 0;
  int max_next = next_planet[0];

  while ( (max_next != NOT_A_PLANET) && (max_next != n-1) ) {
    start = max_last+1;
    max_last = max_next;
    max_next = NOT_A_PLANET;
    for( int i = start; i <= max_last; ++i ) {
      if ( next_planet[i] > max_next ) {
        max_next = next_planet[i];
        new_result = i;
      }
    }
    result[out_cnt] = new_result;
    out_cnt++;
  }

  FILE* fout = fopen( "expedition.out", "w" );
  if ( max_next == NOT_A_PLANET ) {
    fprintf( fout, "0" );
  } else {
    fprintf( fout, "%d\n", out_cnt );
    for( int i = 0; i < out_cnt; ++i ) {
      fprintf( fout, "%d ", result[i]+1 );
    }
  }

  fclose( fout );
  return EXIT_SUCCESS;
}


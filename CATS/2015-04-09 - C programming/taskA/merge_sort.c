#include <stdlib.h>
#include <stdio.h>

int* merge_sort( int* buf, unsigned int len )
{
  int* result = malloc( len * sizeof(int) );
  if (len == 1) {
    result[0] = buf[0];
    return result;
  }

  unsigned int mid = len / 2;
  int* leftbuf = merge_sort( buf, mid );
  int* rightbuf = merge_sort( buf+mid, len-mid );

  unsigned int lpos = 0, rpos = 0;
  while ( (lpos < mid) || (rpos < len-mid) ) {
    if (lpos == mid) {
      result[lpos+rpos] = rightbuf[rpos];
      rpos++;
    } else if (rpos == len-mid) {
      result[lpos+rpos] = leftbuf[lpos];
      lpos++;
    } else {
      if ( leftbuf[lpos] < rightbuf[rpos] ) {
        result[lpos+rpos] = leftbuf[lpos];
        lpos++;
      } else {
        result[lpos+rpos] = rightbuf[rpos];
        rpos++;        
      }
    }
  }

  free( leftbuf );
  free( rightbuf );
  return result;
}

int main() {
  int n, i;

  FILE* infile = fopen( "input.txt", "r" );
  fscanf( infile, "%d", &n );
  
  int numbers[n];
  
  for( i = 0; i < n; ++i ) {
    fscanf( infile, "%d", &numbers[i] );
  }

  fclose( infile );
  int* numsort = merge_sort( numbers, n );

  FILE* outfile = fopen( "output.txt", "w" );

  for( i = 0; i < n; ++i ) {
    fprintf( outfile, "%d ", numsort[i] );
  }

  fclose( outfile );
}

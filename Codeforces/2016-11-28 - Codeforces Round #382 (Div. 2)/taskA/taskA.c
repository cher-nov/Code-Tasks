#include <stdlib.h>
#include <stdio.h>

#define MAX_PATH_LEN 100

char path[MAX_PATH_LEN];

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  int nlen, gstep; // n, k
  scanf( "%d %d\n", &nlen, &gstep );

  int readp = 0;
  int gpos = -1, tpos = -1; // g, t

  while ( (readp < nlen) && ((gpos == -1) || (tpos == -1)) ) {
    scanf( "%c", &path[readp] );
    switch (path[readp]) {
      case 'G': gpos = readp; break;
      case 'T': tpos = readp; break;
    }
    ++readp;
  }

  if (gpos > tpos) {
    int swap = gpos;
    gpos = tpos;
    tpos = swap;
  }

  int i = gpos;
  while ( (path[i] != '#') && (i < tpos) ) {
    i += gstep;
  }

  char* answer;
  puts( (i == tpos) ? "YES" : "NO" );
}

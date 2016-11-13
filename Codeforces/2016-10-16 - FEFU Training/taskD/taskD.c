// C99, I love you.

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <memory.h>

#define MAX_ROWS 1000
#define MAX_COLS 1000
//#define MAX_COMP (MAX_ROWS*MAX_COLS / 2 + MAX_ROWS*MAX_COLS % 2)
#define MAX_COMP (MAX_ROWS*MAX_COLS / 2 + 1)

#define MAP_FREE (-1)
#define MAP_WALL (-2)

#define CODEFORCES_TEST

static int rows, cols; //n, m

static int map[MAX_ROWS+2][MAX_COLS+2];

static int comp_cache[MAX_COMP] = {0};
static int comp_used[4];

/* ========================================================================== */

int scan( int map[][MAX_COLS+2], int ii, int jj, int cache_id ) {
  //if ( map[ii][jj] != MAP_FREE ) { return 0; }

  int size = 1;
  map[ii][jj] = cache_id;

  #define DFS_STEP(r,c) \
    if ( map[r][c] == MAP_FREE ) { \
      size += scan( map, r, c, cache_id ); \
    }

  DFS_STEP( ii-1, jj );
  DFS_STEP( ii, jj-1 );
  DFS_STEP( ii+1, jj );
  DFS_STEP( ii, jj+1 );

  #undef DFS_STEP

  return size;
}

/* ========================================================================== */

int main() {

  #ifndef CODEFORCES_TEST
  freopen( "input.txt", "r", stdin );
  //freopen( "output.txt", "w", stdout );
  #endif

  scanf( "%d %d\n", &rows, &cols );

  for( int i = 0; i <= rows+1; ++i )
    map[i][0] = map[i][cols+1] = MAP_WALL;
  for( int i = 0; i <= cols+1; ++i )
    map[0][i] = map[rows+1][i] = MAP_WALL;

  for( int i = 1; i <= rows; ++i ) {
    char rdline[cols+1];
    scanf( "%s\n", rdline );
    for( int j = 1; j <= cols; ++j ) {
      map[i][j] = (rdline[j-1] == '.') ? MAP_FREE : MAP_WALL;
    }
  }

  int comp_num = 0, used_pos = 1;

  for( int iw = 1; iw <= rows; ++iw ) {
    char outline[cols+1];
    for( int jw = 1; jw <= cols; ++jw ) {

      if ( map[iw][jw] != MAP_WALL ) {
        outline[jw-1] = '.';
        continue;
      }

      int c_id, result = 1;
      bool used;

      if (used_pos > 0) {
        comp_used[0] = -1;
        comp_used[1] = -1;
        comp_used[2] = -1;
        comp_used[3] = -1;
        used_pos = 0;
      }

      #define SCAN_CACHED(r,c) \
        c_id = map[r][c]; \
        used = false; \
        if ( c_id >= 0 ) { \
          for( int k = 0; k < used_pos; ++k ) { \
            if (comp_used[k] == c_id) { \
              used = true; \
              break; \
            } \
          } \
          if (!used) { \
            result += comp_cache[c_id]; \
            comp_used[used_pos++] = c_id; \
          } \
        } else if ( map[r][c] == MAP_FREE ) { \
          int sr = scan( map, r, c, comp_num ); \
          comp_cache[comp_num] = sr; \
          comp_used[used_pos++] = comp_num; \
          ++comp_num; \
          result += sr; \
        } \

      SCAN_CACHED( iw-1, jw );
      SCAN_CACHED( iw, jw-1 );
      SCAN_CACHED( iw+1, jw );
      SCAN_CACHED( iw, jw+1 );

      #undef SCAN_CACHED
      outline[jw-1] = result % 10 + 48;
    }

    outline[cols] = '\0';
    puts( outline );
  }
}

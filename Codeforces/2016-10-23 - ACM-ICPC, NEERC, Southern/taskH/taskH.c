#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_FN_NUM 100
#define MAX_FN_LEN 100

char fntable[MAX_FN_NUM][MAX_FN_LEN+1] = {0};

int build( int del_list[], int del_num, char pattern[] ) {
  int pat_len = 0;

  for( int i = 0; i < MAX_FN_LEN; ++i ) {
    bool distinct = false;
    char cbase = fntable[del_list[0]][i];
    for( int k = 1; k < del_num; ++k ) {
      char cnext = fntable[del_list[k]][i];
      if ( cbase != cnext ) {
        if ( (cbase == '\0') || (cnext == '\0') ) {
          return 0;
        }
        distinct = true;
        break;
      }
    }
    pattern[i] = distinct ? '?' : cbase;
    if (cbase == '\0') { break; }
    ++pat_len;
  }

  pattern[pat_len] = '\0';
  return pat_len;
}

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  int num_all, num_del; // n, m
  scanf( "%d %d\n", &num_all, &num_del );
  bool del_mask[num_all];

  for( int k = 0; k < num_all; ++k ) {
    scanf( "%s\n", &fntable[k][0] );
    del_mask[k] = false;
  }

  int list_del[num_del];
  for( int k = 0; k < num_del; ++k ) {
    scanf( "%d", &list_del[k] );
    --list_del[k];
    del_mask[list_del[k]] = true;
  }

  int list_keep[num_all-num_del];
  int num_keep = 0;
  for( int k = 0; k < num_all; ++k ) {
    if (!del_mask[k]) { list_keep[num_keep++] = k; }
  }

  #ifndef ONLINE_JUDGE
  for( int k = 0; k < num_all; ++k ) {
    printf( "%s\n", &fntable[k][0] );
  }
  #endif

  char patt_del[MAX_FN_LEN];
  int pdel_len = build( list_del, num_del, patt_del );
  if (pdel_len == 0) {
    printf("No");
    return 0;
  }

  for( int k = 0; k < num_keep; ++k ) {
    bool affect = true;
    for( int i = 0; i < pdel_len; ++i ) {
      if ( //if we found a different char
        ( (fntable[list_keep[k]][i] != patt_del[i]) && (patt_del[i] != '?') )
        || //or filename is shorter than pattern
        ( fntable[list_keep[k]][i] == '\0' )
      ) {
        affect = false;
        break;
      }
    }
    //if pattern matches filename that must be kept and filename is not longer
    if ( (affect) && (fntable[list_keep[k]][pdel_len] == '\0') ) {
      printf("No");
      return 0;
    }
  }

  printf( "Yes\n%s", &patt_del[0] );
  return 0;
}

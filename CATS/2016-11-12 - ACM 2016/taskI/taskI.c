#include <stdlib.h>
#include <stdio.h>

#define MAX_PROG_LEN 100000

char prog[MAX_PROG_LEN+1];

int main() {
  freopen( "input.txt", "r", stdin );
  freopen( "output.txt", "w", stdout );

  scanf( "%s", prog );

  unsigned long long result = 0;
  unsigned long long jump_add = 0;

  size_t i = 0;
  do {
    if (prog[i] == 'i') {
      ++result;
      ++jump_add;
    } else if (prog[i] == 'j') {
      result += jump_add;
    }
  } while( prog[++i] != '\0' );

  printf( "%llu", result );
  return 0;
}

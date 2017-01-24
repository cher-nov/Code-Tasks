#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#define MAX_WORD_LEN 2000

char encword[MAX_WORD_LEN+1];
char decword[MAX_WORD_LEN+1];

int sgn(int x) {
  if (x > 0) return 1;
  if (x < 0) return (-1);
  return 0;
}

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  int word_len;
  scanf( "%d\n%s", &word_len, encword );
  decword[word_len] = '\0';

  int decpos = (word_len / 2) - ((word_len+1) % 2);
  int shift = (word_len % 2 == 0) ? 1 : -1;
  for( int i = 0; i < word_len; ++i ) {
    decword[decpos] = encword[i];
    decpos += shift;
    shift = (shift + sgn(shift)) * -1;
  }

  puts( decword );
}

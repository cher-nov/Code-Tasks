#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_NUMBER_LEN 100

#define write_num(x) \
  if (x[0] == '0') { printf("1"); } \
  printf( "%s\n", x )

char number[MAX_NUMBER_LEN+1];
int num_l;

void add_one( char result[], char max_base_digit ) {
  for( int i = num_l-1; i >= 0; --i ) {
    if (number[i] == max_base_digit) {
      result[i] = '0';
    } else {
      result[i] = (number[i] == '9') ? 'A' : (number[i] + 1);
      strncpy( result, number, i );
      break;
    }
  }

  result[num_l] = '\0';
}

int main() {
  freopen( "input.txt", "r", stdin );
  freopen( "output.txt", "w", stdout );

  scanf( "%s", number );
  char max_digit = '\0';
  for( int i = 0; i <= MAX_NUMBER_LEN; ++i ) {
    if ( number[i] == '\0' ) {
      num_l = i;
      break;
    }
    if ( number[i] > max_digit ) {
      max_digit = number[i];
    }
  }

  char out1[num_l+1]; out1[0] = '\0';
  char out2[num_l+1]; out2[0] = '\0';

  if ( (max_digit != '0') && (number[num_l-1] == max_digit) ) {
    add_one( out1, max_digit );
  }
  if (number[num_l-1] != 'Z') {
    add_one( out2, max_digit+1 );
  }

  if (out1[0] < out2[0]) {
    if (out1[0] != '\0') { write_num( out1 ); }
    if (out2[0] != '\0') { write_num( out2 ); }
  } else {
    if (out2[0] != '\0') { write_num( out2 ); }
    if (out1[0] != '\0') { write_num( out1 ); }
  }

  return EXIT_SUCCESS;
}

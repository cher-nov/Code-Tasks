#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_LEN 101

int main() {
  char num1[MAX_LEN+1], num2[MAX_LEN+1];
  scanf( "%s %s", num1, num2 );
  printf( "%s", ( strcmp(num1, num2) == 0 ) ? num1 : "1" );
}

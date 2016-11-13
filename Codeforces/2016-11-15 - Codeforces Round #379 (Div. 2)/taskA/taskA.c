#include <stdlib.h>
#include <stdio.h>

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  int n;
  scanf( "%d\n", &n );

  int over = 0;

  for( int i = 0; i < n; ++i ) {
    char winner;
    scanf( "%c", &winner );
    over += (winner == 'A') ? 1 : -1;
  }

  if (over > 0) {
    puts("Anton");
  } else if (over < 0) {
    puts("Danik");
  } else {
    puts("Friendship");
  }
}

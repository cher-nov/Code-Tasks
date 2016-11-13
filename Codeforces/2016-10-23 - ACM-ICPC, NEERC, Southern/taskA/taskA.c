#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

#define MAX_FRIENDS 100
#define MAX_ROUNDS 10000
#define MIN_TEAM_SIZE 2
#define MAX_TEAM_SIZE 5

#define in_range_ne(x,l,h) ( (x > l) && (x < h) )

char rounds[MAX_ROUNDS][MAX_FRIENDS+1] = {0};
int round_num = 0;

typedef struct {
  int position;
  int rating;
} friend_t, *friend_ptr_t;

int cmp_friends( const void* a, const void* b ) {
  // a - b : ascending sort
  // b - a : descending sort
  return ((friend_ptr_t)b)->rating - ((friend_ptr_t)a)->rating;
}

int main() {
  #ifndef ONLINE_JUDGE
  freopen( "input.txt", "r", stdin );
  #endif

  int friends_num;
  scanf( "%d\n", &friends_num );

  friend_t friends[friends_num];
  for( int k = 0; k < friends_num; ++k ) {
    scanf( "%d", &friends[k].rating );
    friends[k].position = k;
  }

  bool equal;
  do {
    qsort( friends, friends_num, sizeof(friend_t), &cmp_friends );
    int team = 1;
    equal = true;

    do {
      if ( friends[0].rating != friends[team].rating ) {
        equal = false;
      } else {
        ++team;
      }
    } while ( (team < friends_num) && (equal) );

    if (!equal) {
      if (team < MIN_TEAM_SIZE) { team = MIN_TEAM_SIZE; }

      // split team into blocks, if it has more members than MAX_TEAM_SIZE
      do {
        int block;
        if (in_range_ne( team, MAX_TEAM_SIZE, MAX_TEAM_SIZE + MIN_TEAM_SIZE )) {
          block = team - MIN_TEAM_SIZE;
        } else {
          block = (team < MAX_TEAM_SIZE) ? team : MAX_TEAM_SIZE;
        }
        for( int k = 0; k < friends_num; ++k ) {
          rounds[round_num][friends[k].position] = (k < block) ? '1' : '0';
          if ( (k < block) && (friends[k].rating > 0) ) { --friends[k].rating; }
        }
        qsort( friends, team, sizeof(friend_t), &cmp_friends ); // reorder team
        team -= block;
        ++round_num;
      } while (team > 0);
    }
  } while (!equal);

  printf( "%d\n%d\n", friends[0].rating, round_num );
  for( int k = 0; k < round_num; ++k ) {
    printf( "%s\n", rounds[k] );
  }
}

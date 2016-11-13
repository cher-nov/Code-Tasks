#include <stdio.h>
#include <stdlib.h>
#include "linear_sequence.h"

#define SEQ0 10
#define SEQ1 15
#define SEQ2 20
#define SEQ3 25
#define SEQ4 30
#define SEQ5 35
#define SEQC 50

int main()
{
  LSQ_HandleT list;
  LSQ_IteratorT i;

  printf( "Our sequence: %d, %d, %d, %d, %d, %d and %d in center.\n",
          SEQ5, SEQ3, SEQ1, SEQ0, SEQ2, SEQ4, SEQC );

/* ---------------------------------------------------------------- */
  puts( "\nTEST 1: creating list and deleting it immediately" );
  list = LSQ_CreateSequence(); printf( "created "  );
  LSQ_DestroySequence(list);   printf( "deleted\n" );

/* ---------------------------------------------------------------- */

  list = LSQ_CreateSequence();

  puts( "\nCRUSHTEST: LSQ_GetFrontElement() must return end boundary on empty list" );
  i = LSQ_GetFrontElement(list);
  if ( LSQ_IsIteratorPastRear(i) ) { puts( "PASSED" ); } else { puts( "FAILED! ;'(" ); }
  LSQ_DestroyIterator(i);

  puts( "\nCRUSHTEST: previous, but for LSQ_GetElementByIndex(list, 0)" );
  i = LSQ_GetElementByIndex(list, 0);
  if ( LSQ_IsIteratorPastRear(i) ) { puts( "PASSED" ); } else { puts( "FAILED! ;'(" ); }
  LSQ_DestroyIterator(i);

  puts( "\nCRUSHTEST: ability to set iterator to end boundary by LSQ_SetPosition()" );
  i = LSQ_GetFrontElement(list);
  LSQ_SetPosition( i, LSQ_GetSize(list) );
  if ( LSQ_IsIteratorPastRear(i) ) { puts( "PASSED" ); } else { puts( "FAILED! ;'(" ); }
  LSQ_DestroyIterator(i);

  puts( "\nCRUSHTEST: ability to set iterator to end boundary by LSQ_ShiftPosition()" );
  i = LSQ_GetFrontElement(list);
  LSQ_ShiftPosition( i, LSQ_GetSize(list) );
  if ( LSQ_IsIteratorPastRear(i) ) { puts( "PASSED" ); } else { puts( "FAILED! ;'(" ); }
  LSQ_DestroyIterator(i);

  puts( "\nCRUSHTEST: trying to add element before start boundary" );
  i = LSQ_GetFrontElement(list);
  LSQ_RewindOneElement(i);
  LSQ_InsertElementBeforeGiven(i, 13);
  if ( (LSQ_GetSize(list) == 0) && (LSQ_IsIteratorBeforeFirst(i)) ) {
    puts( "PASSED" );
  } else {
    puts( "FAILED! ;'(" );
  }
  LSQ_DestroyIterator(i);

/* ================================================================ */
  puts( "\nTEST 2: adding elements" );

  i = LSQ_GetPastRearElement(list);
  LSQ_InsertElementBeforeGiven(i, SEQ0);
  LSQ_DestroyIterator(i);

  i = LSQ_GetFrontElement(list);
  LSQ_InsertElementBeforeGiven(i, SEQ1);
  LSQ_DestroyIterator(i);

  LSQ_InsertRearElement(list, SEQ2);
  LSQ_InsertFrontElement(list, SEQ3);
  LSQ_InsertRearElement(list, SEQ4);
  LSQ_InsertFrontElement(list, SEQ5);

  i = LSQ_GetElementByIndex(list, 3);
  LSQ_InsertElementBeforeGiven(i, SEQC);
  LSQ_DestroyIterator(i);

  printf( "List size: %d\n", LSQ_GetSize(list) );

/* ---------------------------------------------------------------- */
  puts( "\nTEST 3.1: writing elements in front-to-rear order" );
  for( i = LSQ_GetFrontElement(list);
       LSQ_IsIteratorDereferencable(i);
       LSQ_AdvanceOneElement(i) )
     { printf( "%d ", *LSQ_DereferenceIterator(i) ); }

  LSQ_DestroyIterator(i);

/* ---------------------------------------------------------------- */
  puts( "\nTEST 3.2: writing elements in rear-to-front order" );
  i = LSQ_GetPastRearElement(list);
  for( LSQ_RewindOneElement(i);
       LSQ_IsIteratorDereferencable(i);
       LSQ_RewindOneElement(i) )
     { printf( "%d ", *LSQ_DereferenceIterator(i) ); }

  LSQ_DestroyIterator(i);

/* ---------------------------------------------------------------- */
  puts( "\nTEST 3.3: writing elements in bound-to-bound order by shifting" );
  i = LSQ_GetFrontElement(list);
  printf( "(0) %d", *LSQ_DereferenceIterator(i) );
  for( int shift = LSQ_GetSize(list)-1;
       shift != 0;
       shift = (shift > 0) ? -shift +1 : -shift -1 )
     { LSQ_ShiftPosition( i, shift );
       printf( " (%d) %d", shift, *LSQ_DereferenceIterator(i) ); }

  LSQ_DestroyIterator(i);

/* ---------------------------------------------------------------- */
  puts( "\n\nTEST 4.1: elements indexation from start by LSQ_GetElementByIndex()" );
  for( int index = 0; index < LSQ_GetSize(list); ++index ) {
    i = LSQ_GetElementByIndex(list, index);
    printf( "(%d) %d ", index, *LSQ_DereferenceIterator(i) );
    LSQ_DestroyIterator(i);
  }

/* ---------------------------------------------------------------- */
  puts( "\nTEST 4.2: elements indexation from start by LSQ_SetPosition()" );
  i = LSQ_GetFrontElement(list);
  for( int index = 0; index < LSQ_GetSize(list); ++index ) {
    LSQ_SetPosition(i, index);
    printf( "(%d) %d ", index, *LSQ_DereferenceIterator(i) );
  }

  LSQ_DestroyIterator(i);

/* ---------------------------------------------------------------- */
  puts( "\nTEST 4.3: elements indexation from end by LSQ_GetElementByIndex()" );
  for( int index = LSQ_GetSize(list)-1; index >= 0; --index ) {
    i = LSQ_GetElementByIndex(list, index);
    printf( "(%d) %d ", index, *LSQ_DereferenceIterator(i) );
    LSQ_DestroyIterator(i);
  }

/* ---------------------------------------------------------------- */
  puts( "\nTEST 4.4: elements indexation from end by LSQ_SetPosition()" );
  i = LSQ_GetFrontElement(list);
  for( int index = LSQ_GetSize(list)-1; index >= 0; --index ) {
    LSQ_SetPosition(i, index);
    printf( "(%d) %d ", index, *LSQ_DereferenceIterator(i) );
  }

  LSQ_DestroyIterator(i);

/* ---------------------------------------------------------------- */
  puts( "\n\nTEST 5: deleting elements" );
  for( i = LSQ_GetFrontElement(list);
       LSQ_IsIteratorDereferencable(i);
       LSQ_DeleteGivenElement(i) )
     { printf( "%d ", *LSQ_DereferenceIterator(i) ); }

  LSQ_DestroyIterator(i);
  printf( "\nList size: %d", LSQ_GetSize(list) );

/* ---------------------------------------------------------------- */
  LSQ_DestroySequence(list);
  puts( "\n\nTHAT'S ALL FOLKS!" );
  system("pause");
}

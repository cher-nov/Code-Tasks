#include "linear_sequence.h"

#define new(type) (type*)( malloc( sizeof(type) ) )

/* ================================================================ */

typedef struct item* pListItem;
typedef struct item {
  LSQ_BaseTypeT value;
  pListItem prev;
  pListItem next;
} ListItem;

typedef struct list* pLinkedList;
typedef struct list {
  //first and last elements aren't actually list elements, they're boudaries
  pListItem first;
  pListItem last;
  unsigned int count;
} LinkedList;

typedef struct iterator* pListIterator;
typedef struct iterator {
  pListItem item;
  pLinkedList list;
} ListIterator;

/* ================================================================ */

static pListItem create_item( pListItem prev, pListItem next, LSQ_BaseTypeT value )
{
  pListItem new_item = new(ListItem);
  new_item->value = value;
  new_item->prev  = prev;
  new_item->next  = next;
  return new_item;
}

static pListItem get_item( pLinkedList list, unsigned int index )
{
  if ( ( index > list->count ) || ( index < 0 ) ) { return NULL; }

  pListItem item;
  for( item = list->first->next;
       index > 0;
       item = item->next ) { --index; }

  return item;
}

static LSQ_IteratorT create_iterator( pListItem item, pLinkedList list )
{
  pListIterator new_iterator = new(ListIterator);
  new_iterator->item = item;
  new_iterator->list = list;
  return (LSQ_IteratorT)new_iterator;
}

static pListItem add_item( pLinkedList list, pListItem current, LSQ_BaseTypeT value )
{
  pListItem new_item = create_item( current->prev, current, value );
  current->prev->next = new_item;
  current->prev = new_item;
  list->count++;
  return new_item;
}

static pListItem delete_item( pLinkedList list, pListItem item )
{
  if ( list->count == 0 ) { return item; }

  pListItem next = item->next;
  item->prev->next = next;
  item->next->prev = item->prev;

  free( item );
  list->count--;
  return next;
}

/* ================================================================ */

LSQ_HandleT LSQ_CreateSequence(void)
{
  pLinkedList new_list = new(LinkedList);

  new_list->first = create_item( NULL, NULL, 0 );
  new_list->last  = create_item( new_list->first, NULL, 0 );
  new_list->first->next = new_list->last;

  new_list->count = 0;

  return (LSQ_HandleT)new_list;
}

void LSQ_DestroySequence(LSQ_HandleT handle)
{
  if ( handle != LSQ_HandleInvalid ) {
    pLinkedList list = (pLinkedList)handle;

    //free all items, including boundaries
    pListItem curr = list->first, next;
    while (curr != NULL) {
      next = curr->next;
      free( curr );
      curr = next;
    }

    free( list );
  }
}

LSQ_IntegerIndexT LSQ_GetSize(LSQ_HandleT handle)
{
  if ( handle != LSQ_HandleInvalid ) {
    return ( (pLinkedList)handle )->count;
  } else {
    return 0;
  }
}

/* ---------------------------------------------------------------- */

int LSQ_IsIteratorDereferencable(LSQ_IteratorT iterator)
{
  return !( LSQ_IsIteratorPastRear(iterator) || LSQ_IsIteratorBeforeFirst(iterator) );
}

int LSQ_IsIteratorPastRear(LSQ_IteratorT iterator)
{
  return ( (pListIterator)iterator )->item->next == NULL;
}

int LSQ_IsIteratorBeforeFirst(LSQ_IteratorT iterator)
{
  return ( (pListIterator)iterator )->item->prev == NULL;
}

LSQ_BaseTypeT* LSQ_DereferenceIterator(LSQ_IteratorT iterator)
{
  if ( LSQ_IsIteratorDereferencable(iterator) ) {
    return &( ((pListIterator)iterator)->item->value );
  }

  return NULL;
}

/* ---------------------------------------------------------------- */

LSQ_IteratorT LSQ_GetElementByIndex(LSQ_HandleT handle, LSQ_IntegerIndexT index)
{
  if ( handle == LSQ_HandleInvalid ) { return NULL; }

  pListItem item = get_item( (pLinkedList)handle, index );
  if (item == NULL) { return NULL; }

  return create_iterator( item, (pLinkedList)handle );
}

LSQ_IteratorT LSQ_GetFrontElement(LSQ_HandleT handle)
{
  return LSQ_GetElementByIndex( handle, 0 );
}

LSQ_IteratorT LSQ_GetPastRearElement(LSQ_HandleT handle)
{
  if ( handle == LSQ_HandleInvalid ) { return NULL; }
  return create_iterator( ((pLinkedList)handle)->last, (pLinkedList)handle );
}

void LSQ_DestroyIterator(LSQ_IteratorT iterator)
{
  if ( iterator != NULL ) { free( iterator ); }
}

/* ---------------------------------------------------------------- */

void LSQ_AdvanceOneElement(LSQ_IteratorT iterator)
{
  LSQ_ShiftPosition( iterator, 1 );
}

void LSQ_RewindOneElement(LSQ_IteratorT iterator)
{
  LSQ_ShiftPosition( iterator, -1 );
}

void LSQ_ShiftPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT shift)
{
  pListIterator itercast = (pListIterator)iterator;
  while ( shift != 0 )
  {
    if (shift > 0) { if ( LSQ_IsIteratorPastRear(iterator) ) { break; }
                     itercast->item = itercast->item->next;
                     --shift; }
              else { if ( LSQ_IsIteratorBeforeFirst(iterator) ) { break; }
                     itercast->item = itercast->item->prev;
                     ++shift; }
  }
}

void LSQ_SetPosition(LSQ_IteratorT iterator, LSQ_IntegerIndexT pos)
{
  pListIterator itercast = (pListIterator)iterator;
  pListItem item = get_item( itercast->list, pos );
  if (item != NULL) { itercast->item = item; }
}

/* ---------------------------------------------------------------- */

void LSQ_InsertFrontElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
  if ( handle != LSQ_HandleInvalid ) {
    add_item( (pLinkedList)handle, ((pLinkedList)handle)->first->next, element );
  }
}

void LSQ_InsertRearElement(LSQ_HandleT handle, LSQ_BaseTypeT element)
{
  if ( handle != LSQ_HandleInvalid ) {
    add_item( (pLinkedList)handle, ((pLinkedList)handle)->last, element );
  }
}

void LSQ_InsertElementBeforeGiven(LSQ_IteratorT iterator, LSQ_BaseTypeT newElement)
{
  if ( iterator == NULL ) { return; }
  if ( !LSQ_IsIteratorBeforeFirst(iterator) ) {
    pListIterator itercast = (pListIterator)iterator;
    itercast->item = add_item( itercast->list, itercast->item, newElement );
  }
}

/* ---------------------------------------------------------------- */

void LSQ_DeleteFrontElement(LSQ_HandleT handle)
{
  if ( handle != LSQ_HandleInvalid ) {
    delete_item( (pLinkedList)handle, ((pLinkedList)handle)->first->next );
  }
}

void LSQ_DeleteRearElement(LSQ_HandleT handle)
{
  if ( handle != LSQ_HandleInvalid ) {
    delete_item( (pLinkedList)handle, ((pLinkedList)handle)->last->prev );
  }
}

void LSQ_DeleteGivenElement(LSQ_IteratorT iterator)
{
  if ( LSQ_IsIteratorDereferencable(iterator) ) {
    pListIterator itercast = (pListIterator)iterator;
    itercast->item = delete_item( itercast->list, itercast->item );
  }
}

//
// Implement the List class
//

#include <stdio.h>
#include "List.h"

//
// Inserts a new element with value "val" in
// ascending order.
//
void
List::insertSorted( int val )
{
  // Complete procedure 
  ListNode *node = new ListNode, *temp, *ins;
  node->_value = val;;
  node->_next = NULL;
  if( _head == NULL || val < _head->_value )
  {
    node->_next = _head;
    _head = node;
    return ; 
  }
  temp = _head;
  while( val > temp->_value )
  {
    temp = temp->_next;
    if( temp == NULL )
      break;
  }
  if( temp == NULL )
  {
    for( temp = _head; temp->_next != NULL; temp = temp->_next );
    temp->_next = node;
    return ;
  }
  else
  {
    ins = temp;
    for( temp = _head; temp != NULL; temp = temp->_next )
      if( temp->_next == ins )
        break;
    node->_next = temp->_next;
    temp->_next = node;
  }
}

//
// Inserts a new element with value "val" at
// the end of the list.
//
void
List::append( int val )
{
  // Complete procedure
  ListNode *node = new ListNode;
  node->_value = val;
  node->_next = NULL;
  if( _head == NULL )
    List::prepend(val);
  else
  {
    ListNode *temp;
    for( temp = _head; temp->_next != NULL; temp = temp->_next );
    temp->_next = node;
    node->_next = NULL;
  } 
}

//
// Inserts a new element with value "val" at
// the beginning of the list.
//
void
List::prepend( int val )
{
  // Complete procedure 
  ListNode *node = new ListNode;
  node->_value = val;
  node->_next = NULL;
  node->_next = _head;
  _head = node;
}

// Removes an element with value "val" from List
// Returns 0 if succeeds or -1 if it fails
int 
List:: remove( int val )
{
  // Complete procedure
  if( _head == NULL )
    return -1;
  else if( _head->_value == val )
  {
    ListNode *del = _head;
    _head = _head->_next;
    delete del;
    return 0;
  }
  ListNode *temp = _head, *ins;
  for( temp = _head; temp != NULL; temp = temp->_next )
    if( temp->_value == val )
      break;
  ins = temp;
  if( ins == NULL )
    return -1;
  if( temp->_next == NULL )
  {
    for( temp = _head; temp->_next->_next != NULL; temp = temp->_next );
    ListNode *del = temp->_next;
    temp->_next = NULL;
    delete del;
    return 0;
  }
  else 
  {
    for( temp = _head; temp != NULL; temp = temp->_next )
      if( temp->_next == ins )
        break;
    if( temp == NULL )
      return -1;
    else
    {
      temp->_next = temp->_next->_next;
      delete ins;
      return 0;
    }
  }
  return -1;
}

// Prints The elements in the list. 
void
List::print()
{
  // Complete procedure
  ListNode *temp;
  for( temp = _head; temp != NULL; temp = temp->_next )
    printf("%d ", temp->_value);
}

//
// Returns 0 if "value" is in the list or -1 otherwise.
//
int
List::lookup(int val)
{
  // Complete procedure 
  ListNode *temp;
  for( temp = _head; temp != NULL; temp = temp->_next )
    if( temp->_value == val )
      return 0;
  return -1;
}

//
// List constructor
//
List::List()
{
  // Complete procedure 
  _head = NULL;
}

//
// List destructor: delete all list elements, if any.
//
List::~List()
{
  // Complete procedure 
  ListNode *temp = _head;
  while( _head != NULL )
  {
    temp = _head;
    _head = _head->_next;
    delete temp;
  }
  if( _head != NULL )
    delete _head;
}


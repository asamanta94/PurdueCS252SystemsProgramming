#include <stdio.h>
#include "Queue.h"

void
Queue::enqueue(int val)
{
	if( _head == NULL )
		List::prepend(val);
	else
		List::append(val);
}

int
Queue::dequeue()
{
	if( _head == NULL )
		return -1;
	else
	{
		ListNode *temp;
		int ret = 0;
		temp = _head;
		_head = _head->_next;
		ret = temp->_value;
		delete temp;
		return ret;
	}
}

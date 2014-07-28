#include <stdio.h>
#include "Stack.h"

void 
Stack::push(int val)
{
	List::prepend(val);
}

int 
Stack::pop()
{
	ListNode *temp;
	int ret = -1;
	if( _head == NULL )
		return ret;
	else
	{
		temp = _head;
		_head = _head->_next;
		ret = temp->_value;
		delete temp;
		return ret;
	}
}

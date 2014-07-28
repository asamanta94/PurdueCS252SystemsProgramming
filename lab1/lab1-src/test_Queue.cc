#include <stdio.h>
#include "Queue.h"

int main( int argc, const char **argv )
{
	Queue q;
	for( int i = 0; i < 10; i++ )
		q.enqueue(i);
	q.print();
	for( int i = 0; i < 10; i++ )
		printf("%d ", q.dequeue());
	return 0;
}

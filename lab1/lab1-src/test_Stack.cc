#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "Stack.h"

int main( int argc, char ** argv )
{
	Stack st;
	int i = 0;
	for( i = 0; i < 10; i++ )
		st.push(i);
	st.print();
	printf("%d\n", st.lookup(10));
	for( i = 0; i < 10; i++ )
		printf("%d ", st.pop());
	return 0;
}

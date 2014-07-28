#include <alloca.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include "mysort.h"
//
// Sort an array of element of any type
// it uses "compFunc" to sort the elements.
// The elements are sorted such as:
//
// if ascending != 0
//   compFunc( array[ i ], array[ i+1 ] ) <= 0
// else
//   compFunc( array[ i ], array[ i+1 ] ) >= 0
//
// See test_sort to see how to use mysort.
//
void mysort( int n,                      // Number of elements
	     int elementSize,            // Size of each element
	     void * array,               // Pointer to an array
	     int ascending,              // 0 -> descending; 1 -> ascending
	     CompareFunction compFunc )  // Comparison function.
{
  // Add your code here. Use any sorting algorithm you want.
	void *temp = (void *)malloc(elementSize);
	int i = 0, j = 0, res = 0;
	for( i = 0; i < n; i++ )
	{
		for( j = 0; j < (n - 1); j++ )
		{
			void *curr = (void *)((char *)array + j*elementSize);
			void *next = (void *)((char *)array + (j + 1)*elementSize);
			res = (*compFunc)(curr, next);
			if( ascending == 1 && res > 0 )
			{
				memcpy(temp, curr, elementSize);
				memcpy(curr, next, elementSize);
				memcpy(next, temp, elementSize);
			}
			else if( ascending == 0 && res < 0 )
			{
				memcpy(temp, curr, elementSize);
				memcpy(curr, next, elementSize);
				memcpy(next, temp, elementSize);	
			}
		}
	}
	free( temp );
}


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Der.h"

int main()
{
	char *s = (char *)malloc(12*sizeof(char));
	s = "Hello World";
	printf("%c\n", *(strstr(s, "Hello")));
	return 0;
}

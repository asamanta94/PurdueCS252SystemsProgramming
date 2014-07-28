#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main()
{
	char *s = (char *)malloc(12*sizeof(char));
	s = "Hello World";
	printf("%c\n", *(strstr(s, " ") + 1));
	printf("%d\n", (int)strlen(""));
	return 0;
}

#include <sys/types.h>
#include <stdlib.h>
/*
 * Implement the following string procedures.
 *
 * Type "man strstr" to find what each of the functions should do.
 *
 * For example, mystrcpy should do the same as strcpy.
 *
 * IMPORTANT: DO NOT use predefined string functions.
 */

char *mystrcpy(char * s1, const char * s2)
{
  /* Complete procedure */
	int i = 0;
    while( *(s2 + i) != '\0'){
        *(s1 + i) = *(s2 + i);
        i++;
      }
    *(s1 + i) = '\0';
}

size_t mystrlen(const char *s)
{
  /* Complete procedure */
	int i = 0;
	for( i = 0; *(s + i) != '\0'; i++ );
	return i;
}

char *mystrdup(const char *s1)
{
  /* Complete procedure */
	char *copy = (char *)malloc(mystrlen(s1)*sizeof(char));
	int i = 0;
	while( *(s1 + i) != '\0' )
		*(copy + i) = *(s1 + i++);
	return copy;
}

char *mystrcat(char * s1, const char * s2)
{
  /* Complete procedure */
	int i = 0;
    while(*(s1 + i) != '\0')
        s1++;
    int k = 0;
    while(*(s2 + k) != '\0')
        *(s1 + i++) = *(s2 + k++);
    *(s1 + i++) = '\0';
}

char *mystrstr(char * s1, const char * s2)
{
  /* Complete procedure */
	if( (s1 == NULL && s2 == NULL) )
	{
		char *ret = s1;
		return ret;
	}
	else if( (mystrlen(s1) < mystrlen(s2)) || (s1 == NULL && s2 != NULL) ||(s2 == NULL && s1 != NULL) )
		return NULL;
	else if( mystrlen(s1) == mystrlen(s2) )
	{
		int i = 0;
		char *ret = s1;
		for( i = 0; *(s1 + i) != '\0'; i++ )
			if( *(s2 + i) != *(s1 + i) )
				return NULL;
		if( *(s1 + i) == '\0' && *(s2 + i) == '\0' )
			return ret;
	}
	else if( mystrlen(s2) == 0 )
		return s1;
	else
	{
		int i = 0, k = 0;
		char *s1_iter = s1, *ret = NULL;
		for( i = 0; *(s1_iter) != '\0'; i++ )
		{
			if( *s1_iter == *s2 )
			{
				k = 0;
				if( mystrlen(s1_iter) < mystrlen(s2) )
					return NULL;
				else
				{
					ret = s1_iter;
					while( *(s2 + k) != '\0' )
					{
						if( *(s1_iter + k) != *(s2 + k) )
							break;
						k++;
					}
					if( *(s2 + k) == '\0')
						return s1_iter;
				}
			}
			s1_iter++;
		}
		return NULL;
	}

}

int mystrcmp(const char *s1, const char *s2) {
  /* Complete procedure */
	int i = 0;
  if( s1 == NULL && s2 != NULL ) 
  	return -1;
  else if( s1 != NULL && s2 == NULL )
  	return 1;
  else if( s1 == NULL && s2 == NULL )
  	return 0;
  else
  {
  	int i = 0;
  	int len_s1 = mystrlen(s1);
  	int len_s2 = mystrlen(s2);
    int diff = 0;
  	for( i = 0; *(s1 + i) != '\0' && *(s2 + i) != '\0'; i++ )
    {
      diff = *(s1 + i) - *(s2 + i);
      if( diff != 0 )
        return diff;
    }
  }
}

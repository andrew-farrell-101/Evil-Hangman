#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
    
	MY_STRING hMy_string1 = my_string_init_c_string("Hi");
	if (hMy_string1 == NULL)
	{
		printf("Failed to allocate space for hMy_string");
		exit(1);
	}

	MY_STRING hMy_string2 = my_string_init_c_string("Hi");
	if (hMy_string2 == NULL)
	{
		printf("Failed to allocate space for hMy_string");
		exit(1);
	}
	printf("The size and capacity of the first string are %d and %d, respectivly.\n" , my_string_get_size(hMy_string1), my_string_get_capacity(hMy_string1));
	printf("The size and capacity of the second string are %d and %d, respectivly.\n", my_string_get_size(hMy_string2), my_string_get_capacity(hMy_string2));
	
	if (my_string_compare(hMy_string1, hMy_string2) > 0)
	{
		printf("The left string is bigger. ( string1 )\n");
	}
	else if (my_string_compare(hMy_string1, hMy_string2) < 0)
	{
		printf("The right string is bigger. ( string2 )\n");
	}
	else
	{
		printf("The two strings are identical.\n");
	}

    my_string_destroy(&hMy_string1);
	my_string_destroy(&hMy_string2);
    return 0;
}

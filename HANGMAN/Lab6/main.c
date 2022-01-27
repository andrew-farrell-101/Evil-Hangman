#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	FILE* fp;
	MY_STRING hMy_string = my_string_init_c_string("Hello");
	MY_STRING hMy_string2 = my_string_init_c_string("Goodbye");// First string
	if (hMy_string == NULL)
	{
		printf("Failed to allocate space for hMy_string");
		exit(1);
	}
	fp = fopen("sample.txt", "r");
	if (fp == NULL)
	{
		exit(-1);
	}
	my_string_concat(hMy_string, hMy_string2);
	my_string_insertion(hMy_string, stdout);
	printf("\n");
        my_string_destroy(&hMy_string);
	my_string_destroy(&hMy_string2);
	hMy_string = my_string_init_default();// Destroy when done.
	my_string_insertion(hMy_string, stdout);
	my_string_push_back(hMy_string, 'A');// show that default strings can print 18
	my_string_insertion(hMy_string, stdout);
	hMy_string2 = my_string_init_c_string(" -- This will force a resize of the string object");
	my_string_concat(hMy_string,hMy_string2); 
	// This will not preserve the null terminator because the 
	//object receiving the string was not originally null terminated.
	my_string_insertion(hMy_string, stdout);
	my_string_destroy(&hMy_string);
	my_string_destroy(&hMy_string2);
	fclose(fp);
    return 0;
}


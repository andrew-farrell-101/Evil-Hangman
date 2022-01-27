#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[]) {
	FILE* fp;
	MY_STRING hMy_string = my_string_init_default(); // First string
	if (hMy_string == NULL)
	{
		printf("Failed to allocate space for hMy_string");
		exit(1);
	}
	fp = fopen("dictionary.txt", "r");
	if (fp == NULL)
	{
		exit(-1);
	}
	while (my_string_extraction(hMy_string, fp))
	{
	  if (my_string_get_size(hMy_string) == 29)
	    {
		my_string_insertion(hMy_string, stdout);
		printf("\n");
		char c = fgetc(fp);
	  	if (c == '\n')
		{
		printf("found a newline after the string\n");
		}
		if(c == ' ')
		{
		printf("found a space after the string\n");
		}
	   
	   }
	   else
	   {
		fgetc(fp);
	   }
	}
        my_string_destroy(&hMy_string); // Destroy when done.
	fclose(fp);
    return 0;
}

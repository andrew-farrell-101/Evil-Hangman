#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"

int main(int argc, char* argv[])
{
	FILE* fp;
	MY_STRING hMy_string = my_string_init_c_string("Hello");
	MY_STRING hMy_string2 = my_string_init_c_string("Goodbye");								// c init
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
	my_string_concat(hMy_string, hMy_string2); 										// concat function
	my_string_insertion(hMy_string, stdout);										//insertion function
	printf("\n");
	printf("The size and capacity of the concatonated c-string is %d and %d respectively.\n", my_string_get_size(hMy_string), my_string_get_capacity(hMy_string)); // size/cap functions
	MY_STRING hMy_string3 = my_string_init_default();
	for (int i = 0; i < 26; i++)
	{
		my_string_push_back(hMy_string3, (char)(i + 97));
	}
	printf("The c-string version of a my non c string is '%s'\n",my_string_c_str(hMy_string3));                             //Convert to c string
	printf("The last letter of the string is %c\n", my_string_at(hMy_string,my_string_get_size(hMy_string)-1)[0]);          //My string at
	my_string_push_back(hMy_string, 'X');											//push back
	my_string_insertion(hMy_string, stdout);
        printf("\n");
	my_string_pop_back(hMy_string);												//pop back
	my_string_insertion(hMy_string, stdout);
	printf("\n");
	my_string_destroy(&hMy_string);
	my_string_destroy(&hMy_string2);											// Destroy
	my_string_destroy(&hMy_string3);
	fclose(fp);
    	return 0;
}

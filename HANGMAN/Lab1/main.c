
#include <stdio.h>
#include <stdlib.h>
int main(int argc, char* argv[])
{
	int* p;
	//Declaration of a pointer variable.
	p = (int*)malloc(sizeof(int) * 20 * 30);
	for (int i = 0; i < 20; i++)
	{
		for (int j = i; j < i + 30; j++)
		{
			printf("%2d ", j);
		}
		printf("\n");
	}
	//First "bookend" allocates space
	//printf("Hello world! I have created a dynamic array of 100 integers!\n");
	free(p);
	//Second "bookend" cleans up the space
	return 0;
}


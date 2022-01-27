#define INT_COUNT 62500000

#include <stdlib.h>
#include <stdio.h>

void set_flag(unsigned int flag_holder[], unsigned int flag_position);
int check_flag(unsigned int flag_holder, int flag_position);

int main(int argc, char* argv[])
{
	unsigned int* flag_holder = (unsigned int*)calloc(INT_COUNT + 1, sizeof(unsigned int));
	int noc;
	unsigned int data = -2;
	while ((noc = scanf("%u\n", &data)) != EOF && data != -1)
	{
		set_flag(flag_holder, data);
	}
	for (int i = 0; i < INT_COUNT + 1; i++)
	{
		for (int j = 0; j < 32; j++)
		{
			if (check_flag(flag_holder[i], j))
			{
				printf("%d\n", (i * 32) + j);
			}
		}
	}
	free(flag_holder);
	return 0;
}


void set_flag(unsigned int flag_holder[], unsigned int flag_position)
{
	int index = flag_position / 32;
	flag_holder[index] |= (unsigned)1 << flag_position;
}

int check_flag(unsigned int flag_holder, int flag_position)
{
	unsigned int one = 1;
	one <<= flag_position;
	if ( flag_holder & one )
	{
		return 1;
	}
	return 0;
}


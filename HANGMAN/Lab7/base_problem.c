
#include <stdio.h>
#include <stdlib.h>
#include "my_string.h"
#include <ctype.h>
#include <math.h>

void clear_keyboard_buffer(void);
void set_min_bases(int* min_left, int* min_right, MY_STRING x, MY_STRING y);
int convert_string_to_base(MY_STRING hMy_string, int base);
void print_outcome(int min_left, int min_right,MY_STRING x, MY_STRING y);

int main(int argc, char* argv[])
{
	MY_STRING x, y;

	x = my_string_init_default();
	y = my_string_init_default();
	while (my_string_extraction(x,stdin) && my_string_extraction(y, stdin))
	{
	int min_left = 1, min_right = 1;
	set_min_bases(&min_left, &min_right, x, y);
	print_outcome(min_left, min_right, x, y);
	}
	my_string_destroy((ITEM*)&x);
	my_string_destroy((ITEM*)&y);

		
	return 0;
}

int convert_string_to_base(MY_STRING hMy_string, int base)
{
	int val = 0;
	int init_size = my_string_get_size(hMy_string);
	for (int i = init_size - 1; i >= 0; i--)
	{
		
		char current_number = my_string_at(hMy_string, i)[0];
		if (isdigit(current_number))
		{
			val += (current_number - '0' ) *  pow(base, init_size - 1 - i); // if the char is a digit, turn it into a number and turn it into a number
		}
		else
			//
		{
			if ((current_number - 55) <= 35 && (current_number - 55) >= 10)
				val += (current_number - 55) * pow(base, init_size - 1 -i); // if the char is a letter, turn it into a number
		}
	}
	return val;
}

void set_min_bases(int* min_left, int* min_right, MY_STRING x, MY_STRING y)
{
	
	for (int i = min_possible_base(x); i <= 36; i++)
	{
		for (int j = min_possible_base(y); j <= 36; j++)
		{
			if (convert_string_to_base(x, i) == convert_string_to_base(y, j)) // loop through all possible combinations (note: I never hand in something like H004A into a base 2 because that is not how that works.)
			{
				*min_left = i;
				*min_right = j;
				return;
			}
		}
	}
}

void clear_keyboard_buffer()
{
	char c;
	int noc;
	noc = scanf("%c", &c);
	while (noc == 1 && c != '\n')
	{
		noc = scanf("%c", &c);
	}
}

int min_possible_base(MY_STRING hMy_string)
{
	int largest = 1;
	for (int i = 0; i < my_string_get_size(hMy_string); i++)
	{

		char current_number = my_string_at(hMy_string, i)[0];
		if (isdigit(current_number))
		{
			if ((current_number - '0') > largest)
				largest = current_number - '0';
		}
		else
			
		{
			if ((current_number - 55) <= 36 && (current_number - 55) >= 10)
				if ((current_number - 55) > largest)
					largest = current_number - 55;
		}
	}
	return (largest + 1);
}

void print_outcome(int min_left, int min_right, MY_STRING x, MY_STRING y)
{
	if (min_left == 1 && min_right == 1)
	{
		printf("%s is not equal to %s in any base 2..36\n", my_string_c_str(x), my_string_c_str(y));
		return;
	}
	printf("%s (base %d) = %s (base %d)\n", my_string_c_str(x), min_left, my_string_c_str(y), min_right);
}

//For the output <"bases.txt">"output.txt"
/*110010 is not equal to 1000 in any base 2..36
10 (base 10) = A (base 11)
12 (base 17) = 34 (base 5)
123 is not equal to 456 in any base 2..36
1 is not equal to 2 in any base 2..36
10 (base 2) = 2 (base 3)
278B705B (base 16) = AZ0123 (base 36)
12 (base 3) = 5 (base 6)
10 (base 10) = A (base 11)
12 (base 17) = 34 (base 5)
123 is not equal to 456 in any base 2..36
1 is not equal to 2 in any base 2..36
10 (base 2) = 2 (base 3)
0 (base 2) = 0 (base 2)
10 (base 27) = 36 (base 7)
35 (base 10) = Z (base 36)
Z (base 36) = 35 (base 10)
1 (base 2) = 1 (base 2)
2 (base 3) = 2 (base 3)
3 (base 4) = 3 (base 4)
4 (base 5) = 4 (base 5)
5 (base 6) = 5 (base 6)
6 (base 7) = 6 (base 7)
7 (base 8) = 7 (base 8)
8 (base 9) = 8 (base 9)
7FR82OGF (base 28) = 7FR82OGF (base 28)
IGW6NFP (base 33) = IGW6NFP (base 33)
I7U4NK1 (base 31) = I7U4NK1 (base 31)
4NTD52X (base 34) = 4NTD52X (base 34)
NMEP0AI (base 26) = NMEP0AI (base 26)
ID9QJFE (base 27) = ID9QJFE (base 27)
IU0TLAO (base 31) = IU0TLAO (base 31)
4CY20XP (base 35) = 4CY20XP (base 35)
2U6OA34 (base 31) = 2U6OA34 (base 31)
2E is not equal to 2 in any base 2..36
153 is not equal to 10 in any base 2..36
N is not equal to 1 in any base 2..36
331 (base 6) = 87 (base 15)
9D (base 21) = 312 (base 8)
86 (base 25) = 5V (base 35)
9 (base 10) = 21 (base 4)
B (base 12) = 14 (base 7)
6 (base 7) = 20 (base 3)
*/
/***********************************************************
Author: Andrew Thomas Farrell

Date: 2/15/20 ( Attempt 1 )

Effort: A while. I'm actually not sure because I started working on
it the day it was assigned and spent time off and on.

Purpose: Use both opaque object design and bitwise operators to make
a object that can hold and modify bits. "Bits" doesn't even look like
a word anymore.

 Interface proposal: It would be useful to print out the entire
 list in a array fashion. Another choice would be to print out
 all of the indexes where a 1 is located. This would achieve the
 same thing as visually printing all the 0's and 1's but it might not
 be as useful depending on the situation.

 

***********************************************************/


#include "bit_flags.h"
#include "status.h"
#include <stdlib.h>

struct bit_struct
{
	unsigned int* bits;
	int size;
	int capacity;
};
typedef struct bit_struct bit_Flags;

const int BITS_IN_INT = sizeof(unsigned int) * 8;

Status resize_struct(bit_Flags* pBits, int flag_position);

BIT_FLAGS bit_flags_init_number_of_bits(int number_of_bits)
{
	
	if (number_of_bits <= 0)
	{
		return NULL;
	}

	
	bit_Flags* pBits = (bit_Flags*)malloc(sizeof(bit_Flags));
	if (pBits != NULL) 
	{
		pBits->size = number_of_bits;
		int i = 0;

		/*
		if (sizeof(int) == 8) // If we are running with 64 bit integers
		{
			while (number_of_bits > 64 * i)
			{
				i++;
			}
			pBits->bits = (int*)malloc(sizeof(int)*i);
			if (pBits == NULL)
			{
				free(pBits);
				return NULL;
			}

			for (int j = i; j < i; i++)
			{
				pBits->bits[i] = 0;
			}

			pBits->capacity = sizeof(int) * 8 * i;
		}
		else if (sizeof(int) == 4) // if we are running with 32 bit integers
		{
		*/

		while (number_of_bits > 32 * i)
		{
			i++;
		}

		pBits->bits = (unsigned int*)malloc(sizeof(unsigned int)*i);
		if (pBits->bits == NULL)
		{
			free(pBits);
			return NULL;
		}

		pBits->capacity = 32 * i;
		for (int j = 0; j < i; j++)
		{
			pBits->bits[j] = (unsigned int)0;
		}
	}
		
	//}
	return (BIT_FLAGS)pBits;
}

Status resize_struct(bit_Flags* pBits, int flag_position)
{
	unsigned int* temp;
	int elements_needed = (flag_position / 32) + 1;
	temp = (unsigned int*)calloc(elements_needed, sizeof(unsigned int));

	if (temp == NULL)
	{
		return FAILURE;
	}

	for (int i = 0; i < (pBits->capacity / 32); i++) // fill the new array with old values
	{
		temp[i] = pBits->bits[i];
	}
	free(pBits->bits); // remove the old array
	pBits->bits = temp; // Use the new Array
	pBits->capacity = elements_needed * 32;
	return SUCCESS;
}

Status bit_flags_set_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	bit_Flags* pBits = (bit_Flags*)hBit_flags;
	
	if (flag_position >= pBits->capacity) // make more room
	{
		resize_struct(pBits, flag_position);
		
	}

	if (flag_position >= pBits->size) // only change the size when 
	{
		pBits->size = flag_position + 1;
	}
	

	//if (sizeof(int) == 4)
	//{
	
	
	
	int index = flag_position / 32;
	unsigned int one = 1;
	flag_position %= 32;
	pBits->bits[index] |= one << flag_position;
	
	return SUCCESS;
	//}
		/*
	else if (sizeof(int) == 8)
	{
		index = flag_position + 1 / 64;
		unsigned int one = 1;
		pBits->bits[index] |= one << (64 - (flag_position + 1) % 64);
	}
	*/
}



Status bit_flags_unset_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	
	bit_Flags* pBits = (bit_Flags*)hBit_flags;

	if (flag_position >= pBits->capacity)
	{
		resize_struct(pBits, flag_position);
	}

	unsigned int one = 1;
	int index;
	//if (sizeof(int) == 4)
	//{
	index = flag_position / 32;
	one <<= flag_position % 32;
	/*}
	else if (sizeof(int) == 8)
	{
		index = flag_position + 1 / 64;
		one <<= flag_position % 64;
	}
	*/
	pBits->bits[index] ^= one;
	if (bit_flags_check_flag(hBit_flags, flag_position))
	{
		bit_flags_unset_flag(hBit_flags, flag_position);
	}
	return SUCCESS;
}

int bit_flags_check_flag(BIT_FLAGS hBit_flags, int flag_position)
{
	bit_Flags* pBits = (bit_Flags*)hBit_flags;
	if (flag_position >= pBits->capacity)
	{
		return -1;
	}
	unsigned int one = 1;
	int index;
	//if (sizeof(int) == 4)
	//{
	index = flag_position / 32;
	one <<= flag_position % 32;
	/*}
	else if (sizeof(int) == 8)
	{
		index = flag_position + 1 / 64;
		one <<= flag_position % 64;
	}
	*/
	if (pBits->bits[index] & one)
	{
		return 1;
	}
	return 0;
}

int bit_flags_get_size(BIT_FLAGS hBit_flags)
{
	return ((bit_Flags*)hBit_flags)->size;
}

int bit_flags_get_capacity(BIT_FLAGS hBit_flags)
{
	return ((bit_Flags*)hBit_flags)->capacity;
}

void bit_flags_destroy(BIT_FLAGS* phBit_flags)
{
	

	bit_Flags* pBits = (bit_Flags*)*phBit_flags;
	free(pBits->bits); 
	pBits->bits = NULL;
	free(pBits);*phBit_flags = NULL;
}

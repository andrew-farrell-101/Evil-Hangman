#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
struct my_string
{
	char* data;
	int capacity;
	int size;
};
typedef struct my_string My_string;

Bool is_c_string(My_string* pMy_string);

Status resize_string(My_string* pMy_string)
{
	
	My_string* temp = (My_string*)malloc(sizeof(My_string));
	if (temp == NULL)
	{
		return FAILURE;
	}
	Bool c_flag = is_c_string(pMy_string);
	temp->data = (char*)malloc((2 * (pMy_string->capacity)) + (int)c_flag);
	temp->capacity = (pMy_string->capacity * 2) + (int)c_flag;
	temp->size = pMy_string->size;

	if (temp->data == NULL)
	{
		free(temp);
		return FAILURE;
	}
	
	for (int i = 0; i < temp->size; i++)
	{
		temp->data[i] = pMy_string->data[i];
	}
	if (pMy_string->data[pMy_string->size] == '\0')
	{
		temp->data[pMy_string->size] = '\0';
	}
	
	
	pMy_string->capacity = temp->capacity;
	pMy_string->size = temp->size;
	free(pMy_string->data);
	pMy_string->data = temp->data;
	free(temp);
	return SUCCESS;
	

}

MY_STRING my_string_init_default(void)
{
	My_string* pmy_string = (My_string*)malloc(sizeof(My_string));
	if (pmy_string != NULL)
	{
		pmy_string->size = 0;
		pmy_string->capacity = 7;
		pmy_string->data = (char*)malloc(sizeof(char) * pmy_string->capacity);
		if (pmy_string->data == NULL)
		{
			free(pmy_string);
			return NULL;
		}
	}
	return (MY_STRING)pmy_string;

}

Status my_string_pop_back(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	if (my_string_empty(hMy_string))
	{
		return FAILURE;
	}
	if (is_c_string(pMy_string))
	{
		pMy_string->data[--(pMy_string->size)] = '\0';
	}
	else
	{
		pMy_string->size--;
	}
	return SUCCESS;
	
}

char* my_string_at(MY_STRING hMy_string, int index)
{
	My_string* pMy_string = (My_string*)hMy_string;
	Bool c_flag = is_c_string(pMy_string);
	if (index >= 0 && (index < pMy_string->size + (int)c_flag))
	{
		return (char*)&(pMy_string->data[index]);
	}
	return NULL;
}

char* my_string_c_str(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	if (!is_c_string(pMy_string))
	{
		if (my_string_get_size(pMy_string) >= my_string_get_capacity(pMy_string))
			pMy_string->data = realloc(pMy_string->data, pMy_string->capacity + 1);
		pMy_string->data[pMy_string->size] = '\0';
	}
	return pMy_string->data;
}

Bool my_string_empty(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	return (Bool)(pMy_string->size == 0);
}

Status my_string_concat(MY_STRING hResult, MY_STRING hAppend)
{
	My_string* pResult = (My_string*)hResult;
	My_string* pAppend = (My_string*)hAppend;
	Bool c_flag = is_c_string(pResult);
	while (pResult->capacity  < pResult->size + (int)c_flag + pAppend->size)
	{
		Status rc = resize_string(pResult);
		if (!rc)
		{
			return FAILURE;
		}
	}
	for (int i = pResult->size, j = 0; i < pResult->size +  pAppend->size; i++, j++)
	{
		pResult->data[i] = pAppend->data[j];
	}
	pResult->size += pAppend->size;
	if (c_flag)
	{
		pResult->data[pResult->size] = '\0';
	}
	return SUCCESS;

}

Bool is_c_string(My_string* pMy_string)
{
	return (Bool)(pMy_string->data[pMy_string->size] == '\0');
}
Status my_string_push_back(MY_STRING hMy_string, char item)
{
	My_string* pMy_string = (My_string*)hMy_string;
	if ((pMy_string->capacity == pMy_string->size) || ((pMy_string->data[pMy_string->capacity - 1] == '\0') && ((pMy_string->size + 1) == pMy_string->capacity)))
	{
		Status rc = resize_string(pMy_string);
		if (!rc)
		{
			return FAILURE;
		}
	}
	

	if (is_c_string(pMy_string))
	{
		pMy_string->data[pMy_string->size++] = item;
		pMy_string->data[pMy_string->size] = '\0';
	}
	else
	{
		pMy_string->data[pMy_string->size++] = item;
	}

	return SUCCESS;
	
}

MY_STRING my_string_init_c_string(const char* c_string)
{
	My_string* pmy_string = (My_string*)malloc(sizeof(My_string));
	if (pmy_string != NULL)
	{
		pmy_string->size = strlen(c_string);
		pmy_string->capacity = strlen(c_string) + 1;
		pmy_string->data = (char*)malloc(pmy_string->capacity);
		if (pmy_string == NULL)
		{
			free(pmy_string);
			return NULL;
		}

		for (int i = 0; i < pmy_string->capacity; i++)
		{
			pmy_string->data[i] = c_string[i];
		}
		pmy_string->data[pmy_string->capacity - 1] = '\0';
	}
	return (MY_STRING)pmy_string;

}


int my_string_get_capacity(MY_STRING hMy_string)
{
	return ((My_string*)hMy_string)->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
	return ((My_string*)hMy_string)->size;
}

//Precondition: current_word_family, new_key and word are all handles to valid
//   MY_STRING opaque objects.  guess is an alphabetical character that can be either
//   upper or lower case.
//Postcondition:  Returns SUCCESS after replacing the string in new_key with the key
//   value formed by considering the current word family, the word and the guess.
//   Returns failure in the case of a resizing problem with the new_key string.
Status get_word_key_value(MY_STRING current_word_family, MY_STRING new_key, MY_STRING word, char guess)
{
	//My_string* pCurrent_word_family = (My_string*)current_word_family;
	//My_string* pNew_key = (My_string*)new_key;
	//My_string* pWord = (My_string*)word;
	for (int i = 0; i < my_string_get_size(word); i++)
	{
		if (my_string_at(word, i)[0] == guess)
		{
			my_string_at(new_key, i)[0] = guess;
		}
		else if (my_string_at(current_word_family, i)[0] != '-')
		{
			my_string_at(new_key, i)[0] = my_string_at(current_word_family, i)[0];
		}
		else
		{
			*my_string_at(new_key, i) = '-';
		}
	}
	return SUCCESS;

}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string* pLeft_string = (My_string*)hLeft_string;
	My_string* pRight_string = (My_string*)hRight_string;
	int size;

	if (pLeft_string->size == 0 || pRight_string->size == 0)
	{
		if (pLeft_string->size == 0 && pRight_string->size == 0)
			return 0;
		if (!pLeft_string->size)
			return -1;
		if (!pRight_string->size)
			return 1;
	}

	if (pLeft_string->size > pRight_string->size)
	{
		size = pRight_string->size;
	}
	else 
	{
		size = pLeft_string->size;
	}

	for (int i = 0; i < size; i++)
	{
		
		//Compare each letter and see if one is greater than the other
		if ((int)(pLeft_string->data[i]) > (int)(pRight_string->data[i]))
		{
			return 1;
		}
		else if ((int)(pLeft_string->data[i]) < (int)(pRight_string->data[i]))
		{
			return -1;
		}
		
		else
		{
			if (i >= size - 1)
			{
				if (pLeft_string->size > pRight_string->size)
				{
					return 1;
				}
				if (pLeft_string->size < pRight_string->size)
				{
					return -1;
				}
			}
			//continue;
		}

		
	}
	
	return 0;
}
MY_STRING my_string_init_default_family(int word_length)
{
	My_string* pMy_string = (My_string*)(my_string_init_c_string(""));
	for (int i = 0; i < word_length; i++)
	{
		my_string_push_back((MY_STRING)pMy_string, '-');
	}
	return ((MY_STRING)pMy_string);
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	pMy_string->size = 0;
	char letter;
	int noc;



	while ((noc = fscanf(fp, "%c", &letter)))
	{
		if (noc == EOF)
			return FAILURE;
		if (isspace(letter))
			continue;
		else
		{
			break;
		}
			
	}

	while (noc == 1 && !isspace(letter))
	{
		/*
		if (feof(fp))
		{
			return FAILURE;
		}
		
		
		if (noc == EOF)
		{
			return FAILURE;
		}
		*/


		if (pMy_string->size >= pMy_string->capacity)//Old box too small
		{
			char* temp;
			temp = (char*)malloc(sizeof(char) * pMy_string->capacity * 2); // Make a bigger box

			if (temp == NULL)
			{
				return FAILURE;
			}
			

			for (int i = 0; i < pMy_string->size; i++) // Copy old stuff into new box
			{
				temp[i] = pMy_string->data[i];
			}
			free(pMy_string->data);
			pMy_string->data = temp; // old box becomes new box
			pMy_string->capacity *= 2;
			
		}
		
		pMy_string->data[pMy_string->size++] = letter;

		noc = fscanf(fp, "%c", &letter);
		if (!isalnum(letter))
			ungetc(letter, fp);
	}
	
	return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	if (fp == NULL)
	{
		return FAILURE;
	}
	for (int i = 0; i < pMy_string->size; i++)
	{
		fprintf(fp, "%c", pMy_string->data[i]);
	}
	return SUCCESS;
}

void my_string_assignment(ITEM* pLeft, ITEM Right)
{
	My_string* pCopy_string = (My_string*)*pLeft;
	My_string* pTemplate_string = (My_string*)Right;
	if (!pCopy_string)
	{
		pCopy_string = (My_string*)malloc(sizeof(My_string));
		pCopy_string->data = NULL;
	}
	pCopy_string->data = realloc(pCopy_string->data, sizeof(char) * pTemplate_string->capacity);
	if (!pCopy_string->data)
	{
		free(pCopy_string); *pLeft = NULL; return;
	}
		
	pCopy_string->capacity = pTemplate_string->capacity;
	pCopy_string->size = pTemplate_string->size;
	int c_flag = (int)(is_c_string(pTemplate_string));
	for (int i = 0; i < pTemplate_string->size + c_flag; i++)
	{
		pCopy_string->data[i] = pTemplate_string->data[i];
	}
	*pLeft = (MY_STRING*)pCopy_string;
}

void my_string_destroy(ITEM* phItem)
{
	My_string* pMy_string = (My_string*)*phItem;
	free((pMy_string)->data);
	pMy_string->data = NULL;
	free(pMy_string);
	*phItem = NULL;
	//printf("Successfully destroyed object.\n");

}

void output_previous_guesses(MY_STRING hGuessed)
{
	int box_length = 5;
	
	//My_string* pMy_string = (My_string*)hGuessed;
	int size = my_string_get_size(hGuessed);
	printf(" ");
	for (int i = 0; i < box_length; i++)
		printf("---");
	printf("\n");
	for (int i = 0; i < size; i++)
	{
		if (i % box_length == 0)
			printf("|");
		printf("%2c ",my_string_at(hGuessed, i)[0]);
		if ((i - (box_length - 1)) % box_length == 0)
			printf("|\n");
		if (i == size - 1)
		{
			while (((i - (box_length - 1)) % box_length) != 0)
			{
				i++;
				printf("   ");

			}
			printf("|");
		}
	}
	printf("\n ");
	for (int i = 0; i < box_length; i++)
		printf("---");
	printf("\n");
	return;
}

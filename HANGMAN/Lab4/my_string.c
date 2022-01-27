#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

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
	temp->data = (char*)malloc((2 * (pMy_string->capacity)) - (int)c_flag);
	temp->capacity = (pMy_string->capacity * 2) - (int)c_flag;
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
		pMy_string->data[pMy_string->size--] = '\0';
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
	if (index >= 0 && index < pMy_string->size)
	{
		return (char*)&(pMy_string->data[index]);
	}
	return NULL;
}

char* my_string_c_str(MY_STRING hMy_string)
{
	My_string* pMy_string = (My_string*)hMy_string;
	if (is_c_string(pMy_string))
	{
		return pMy_string->data;
	}
	else
	{
		pMy_string->data = (char*)realloc(pMy_string->data, ++(pMy_string->capacity));
		pMy_string->data[pMy_string->size] = '\0';
		return pMy_string->data;
	}

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

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string* pLeft_string = (My_string*)hLeft_string;
	My_string* pRight_string = (My_string*)hRight_string;
	int size;
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
		if ((int)(pLeft_string->data[i]) > (int)(pLeft_string->data[i]))
		{
			return 1;
		}
		else if ((int)(pLeft_string->data[i]) < (int)(pLeft_string->data[i]))
		{
			return 1;
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

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	pMy_string->size = 0;
	char letter;
	int noc;


	while ((noc = fscanf(fp, "%c", &letter)))
	{
		if (feof(fp))
		{
			return FAILURE;
		}

		if (noc == EOF || letter == '.')
		{
			if (letter == '.')
			{
				ungetc(letter, fp);
			}
			break;
		}

		if (letter == ' ' || letter == '\n')
		{
			ungetc(letter ,fp);
			break;
		}

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

void my_string_destroy(MY_STRING* phMy_string)
{
	My_string* pmy_string = (My_string*)*phMy_string;
	free(pmy_string->data);
	pmy_string->data = NULL;
	free(pmy_string);
	pmy_string = NULL;
	printf("Successfully destroyed object.\n");

}

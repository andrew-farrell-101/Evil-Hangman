#include "priority_queue.h"
#include <stdlib.h>
#include <stdio.h>

#define SIZE 10

struct pair {
	int priority;
	int value;
};
typedef struct pair Pair;

struct priority_queue
{
	Pair* data;
	int size;
	int capacity;
};

typedef struct priority_queue Priority_queue;
void fix_up(Priority_queue* pPQ, int index);
void fix_down(Priority_queue* pPQ, int index);
void my_pair_swap(Pair* x, Pair* y);
Status resize_queue(Priority_queue* pPQ);

PRIORITY_QUEUE priority_queue_init_default(void)
{
	Priority_queue* pPQ = (Priority_queue*)malloc(sizeof(Priority_queue));
	if (pPQ != NULL)
	{
		pPQ->size = 0;
		pPQ->capacity = 1;
		pPQ->data = (Pair*)malloc(sizeof(Pair));
		if (!pPQ->data)
		{
			printf("Failed to allocate space for initial object...");
			exit(1);

		}
	}
	return (PRIORITY_QUEUE)pPQ;
}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
	Priority_queue* pPQ = (Priority_queue*)hQueue;
	if (pPQ->size >= pPQ->capacity)
	{
		if (!resize_queue(pPQ))
			return FAILURE;
	}
	
	pPQ->data[pPQ->size] = (Pair){ .priority = priority_level, .value = data_item };
	fix_up(pPQ, pPQ->size);
	pPQ->size++;
	return SUCCESS;
	

}

void fix_up(Priority_queue* pPQ, int index)
{
	
	int index_of_parent = (index - 1) / 2;
	//right child 2 * n + 2
	//right child 2 * n + 1

	if (index > 0 && pPQ->data[index].priority > pPQ->data[index_of_parent].priority)
	{
		my_pair_swap(&pPQ->data[index], &pPQ->data[index_of_parent]);
		fix_up(pPQ, index_of_parent);
	}
}

void my_pair_swap(Pair* x, Pair* y)
{
	Pair temp = *x;
	*x = *y;
	*y = temp;
}

void fix_down(Priority_queue* pPQ, int index )
{
	int index_of_right = (index * 2) + 2;
	int index_of_left = (index * 2) + 1;
	int index_of_better_child;

	if (index_of_left < pPQ->size)//at least one
	{
		if (index_of_right >= pPQ->size)//right out of bounds
		{
			index_of_better_child = index_of_left;
		}
		else
		{

			index_of_better_child = (pPQ->data[index_of_left].priority >= pPQ->data[index_of_right].priority) ? index_of_left : index_of_right; // have the two kids brawl over who is superior
		}
	}
	else	//no chillens
		return;
	if (pPQ->data[index_of_better_child].priority > pPQ->data[index].priority)
	{
		my_pair_swap(&pPQ->data[index], &pPQ->data[index_of_better_child]);
		fix_down(pPQ, index_of_better_child);
	}
}

Status resize_queue(Priority_queue* pPQ)
{
	Pair* temp;
	if ((temp = (Pair*)malloc(sizeof(Pair) * (pPQ->capacity) * 2)) == NULL)
		return FAILURE;
	else
	{
		for (int i = 0; i < pPQ->size; i++)
			temp[i] = pPQ->data[i];
		pPQ->capacity *= 2;
		free(pPQ->data);
		pPQ->data = temp;
		return SUCCESS;
	}
}

Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
	Priority_queue* pPQ = (Priority_queue*)hQueue;
	if (pPQ->size <= 0)
	{
		return FAILURE;
	}
	else
	{
		my_pair_swap(&pPQ->data[0], &pPQ->data[pPQ->size - 1]);
		pPQ->size--;
		fix_down(pPQ, 0);
		return SUCCESS;
	}
}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus)
{
	if(priority_queue_is_empty(hQueue))
	{
		if (pStatus)
			*pStatus= FAILURE;
		return -1;
	}
	else
	{
		if (pStatus)
			*pStatus= SUCCESS;
		return ((Priority_queue*)hQueue)->data[0].value;
	}
		
}

Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{
	return ((((Priority_queue*)hQueue)->size <= 0) ? TRUE : FALSE);
}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{
	Priority_queue* pPQ = (Priority_queue*)*phQueue;
	free(pPQ->data);
	free(pPQ); *phQueue = NULL;
}

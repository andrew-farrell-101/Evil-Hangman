/*
#include "priority_queue.h"
#include <stdlib.h>
#include <stdio.h>

struct pair {
	int priority;
	int value;
};
typedef struct pair Pair;

struct node;
typedef struct node Node;
struct node
{
	Node* next;
	Pair data;
};

struct priority_queue
{
	Node* head;
	int size;
};
typedef struct priority_queue PQ;

PRIORITY_QUEUE priority_queue_init_default(void)
{
	PQ* pPQ = (PQ*)malloc(sizeof(PQ));
	if (pPQ != NULL)
	{
		pPQ->size = 0;
		pPQ->head = NULL;
	}
	return (PRIORITY_QUEUE)pPQ;
}

Status priority_queue_insert(PRIORITY_QUEUE hQueue, int priority_level, int data_item)
{
	PQ* pPQ = (PQ*)hQueue;
	Node* temp;
	if ((temp = (Node*)malloc(sizeof(Node))) == NULL)
	{
		printf("Failed to create new node."); return FAILURE;
	}

	temp->data = (Pair){ .priority = priority_level, .value = data_item };
	temp->next = NULL;

	if (pPQ->size == 0) // list of zero
	{
		pPQ->head = temp;

	}
	else if (pPQ->size == 1)//list of one
	{
		if (pPQ->head->data.priority >= temp->data.priority)
			pPQ->head->next = temp;
		else
			temp->next = pPQ->head; pPQ->head = temp;


	}
	else//list of many
	{
		Node* previous = NULL;
		for (int i = 0; i < pPQ->size; i++)
		{
			if (previous == NULL)
			{
				if (pPQ->head->data.priority <= temp->data.priority)
				{
					temp->next = pPQ->head; pPQ->head = temp;
					break;
				}
				else
					previous = pPQ->head;
			}
			else
			{
				if (previous->next->data.priority >= temp->data.priority)
				{
					previous = previous->next;
					break;

				}
				else
				{
					temp->next = previous->next;
					previous->next = temp;
				}
			}

		}

	}
	pPQ->size++;
	return SUCCESS;
}

Status priority_queue_service(PRIORITY_QUEUE hQueue)
{
	PQ* pPQ = (PQ*)hQueue;
	if (pPQ->size >= 1)
	{
		Node* temp = pPQ->head;
		pPQ->head = pPQ->head->next; pPQ->size--;
		free(temp);
		return SUCCESS;
	}
	else
		return FAILURE;

}

int priority_queue_front(PRIORITY_QUEUE hQueue, Status* pStatus)
{
	PQ* pPQ = (PQ*)hQueue;
	if (pStatus != NULL)
		*pStatus = (pPQ->size > 0) ? SUCCESS : FAILURE;
	if (pPQ->size > 0)
		return pPQ->head->data.value;
	else
		return -1;
}

Boolean priority_queue_is_empty(PRIORITY_QUEUE hQueue)
{
	return ((((PQ*)hQueue)->size <= 0) ? FALSE : TRUE);
}

void priority_queue_destroy(PRIORITY_QUEUE* phQueue)
{

	PQ* pPQ = (PQ*)*phQueue;
	while (pPQ->head)
	{
		Node* temp = pPQ->head->next;
		free(pPQ->head);
		pPQ->head = temp;
	}
	free(pPQ); *phQueue = NULL;
}

//debug function
void print_queue(PRIORITY_QUEUE hQueue)
{
	PQ* pPQ = (PQ*)hQueue;
	Node* temp = pPQ->head;
	while (temp)
	{
		printf("Priority: %d\tValue: %d\n", temp->data.priority, temp->data.value);
		temp = temp->next;
	}
	printf("\n");
}
*/
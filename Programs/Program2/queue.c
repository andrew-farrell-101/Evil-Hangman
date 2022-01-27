#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

struct node;
typedef struct node Node;

struct node
{
	int data;
	Node* next;
	Node* previous;
};

typedef struct {
	Node* head;
	Node* tail;
}Queue;

QUEUE init_queue(void)
{
	Queue* pQue = (Queue*)malloc(sizeof(Queue));
	if (pQue != NULL)
	{
		pQue->head = NULL;
		pQue->tail = NULL;
	}
	return (QUEUE)pQue;
}

Status queue_enque(QUEUE hQueue, int number)
{
	Queue* pQue = (Queue*)hQueue;
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp != NULL)
	{

		if (queue_is_empty(hQueue))
		{
			temp->data = number;
			temp->previous = NULL;
			temp->next = NULL;
			pQue->head = temp;
			pQue->tail = temp;
		}
		else
		{
			if (pQue->head == pQue->tail)//One node in the list
			{
				temp->previous = NULL;
				temp->data = number;
				temp->next = pQue->tail;
				pQue->head = temp;
				pQue->tail->previous = pQue->head;
				return SUCCESS;
			}
			//More than one node in the list
			temp->previous = NULL;
			temp->data = number;
			temp->next = pQue->head;
			pQue->head->previous = temp;
			pQue->head = temp;
		}
		return SUCCESS;
	}
	return FAILURE;

}

Status queue_deque(QUEUE hQueue)
{
	Queue * pQue = (Queue*)hQueue;
	if (pQue == NULL)
	{
		return FAILURE;
	}

	if (pQue->tail != NULL)
	{
		if (pQue->tail->previous != NULL)
		{
			Node* temp = pQue->tail;
			pQue->tail = pQue->tail->previous;
			pQue->tail->next = NULL;
			free(temp);
			return SUCCESS;
		}

		free(pQue->tail);
		pQue->tail = NULL;
		pQue->head = NULL;
		return SUCCESS;
	}
	

	return FAILURE;
}

Bool queue_is_empty(QUEUE hQueue)
{
	Queue* pQue = (Queue*)hQueue;
	return (Bool)((pQue->head == NULL) && (pQue->tail == NULL));
}

int queue_tail_value(QUEUE hQueue)
{
	if (!queue_is_empty(hQueue))
	{
		Queue* pQue = (Queue*)hQueue;
		return pQue->tail->data;
	}
	return -8760;
}

void destroy_queue(QUEUE* phQueue)
{
	Queue* pQ = (Queue*)*phQueue;
	while (queue_deque(*phQueue));
	free(pQ);*phQueue = NULL;
}

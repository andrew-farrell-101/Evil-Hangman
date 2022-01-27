#include "stack.h"
#include <stdlib.h>


struct node;
typedef struct node Node;

struct node {
	char data;
	Node* next;
};

typedef struct stack {
	Node* header;
}Stack;

STACK init_default_stack(void)
{
	Stack* pStack = (Stack*)malloc(sizeof(Stack));
	if (pStack != NULL)
	{
		pStack->header = NULL;
	}
	return (STACK)pStack;
}

Status stack_push(STACK hStack, char c)
{
	Stack* pStack = (Stack*)hStack;
	Node* temp = (Node*)malloc(sizeof(Node));
	if (temp == NULL)
	{
		return FAILURE;
	}

	temp->next = pStack->header;
	temp->data = c;
	pStack->header = temp;
	return SUCCESS;
	
}

Status stack_pop(STACK hStack)
{
	if (!stack_is_empty(hStack))
	{
		Stack* pStack = (Stack*)hStack;
		Node* temp = pStack->header;
		pStack->header = pStack->header->next;
		free(temp);
		return SUCCESS;
	}
	return FAILURE;

}

char stack_top(STACK hStack, Status* pStatus)
{
	Stack* pStack = (Stack*)hStack;
	if (stack_is_empty(hStack))
	{
		if (pStatus != NULL)
		{
			*pStatus = FAILURE;
			
		}
		return (char)'0';
	}
	return (char)(pStack->header->data);
}


Bool stack_is_empty(STACK hStack)
{
	Stack* pStack = (Stack*)hStack;
	return (pStack->header == NULL);
}

void stack_destroy(STACK* hStack)
{
	Stack* phStack = (Stack*)*hStack;
	while (phStack->header != NULL)
	{
		Node* temp = phStack->header;
		phStack->header = phStack->header->next;
		free(temp);
	}
	free(phStack); phStack = NULL;
	*hStack = NULL;

}

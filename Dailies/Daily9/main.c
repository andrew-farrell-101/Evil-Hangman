#include <stdio.h>
#include <stdlib.h>
#include "priority_queue.h"

int main(int argc, char* argv[])
{
	PRIORITY_QUEUE hPQ = priority_queue_init_default();
	
	priority_queue_insert(hPQ, 1, 5);
	priority_queue_insert(hPQ, 2, 4);
	priority_queue_insert(hPQ, 10, 10);
	priority_queue_service(hPQ);
	
	//print_queue(hPQ);

	priority_queue_insert(hPQ, 7, 4);
	priority_queue_insert(hPQ, 9, 0);
	priority_queue_insert(hPQ, 21, -1);
	//print_queue(hPQ);

	priority_queue_service(hPQ);
	priority_queue_insert(hPQ, 44, 44);

	if (priority_queue_is_empty(hPQ))
	{
		printf("The queue is empty.");
	}
	else
	{
		printf("The queue is not empty.");
	}
	printf("\n");
	//print_queue(hPQ);
	printf("The front of the queue is %d\n", priority_queue_front(hPQ, NULL));
	priority_queue_destroy(&hPQ);
	return 0;
}

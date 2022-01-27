#ifndef QUEUE_H
#define QUEUE_H

typedef void* QUEUE;
typedef enum{ FAILURE,SUCCESS }Status;
typedef enum { FALSE, TRUE }Bool;

QUEUE init_queue(void);

int queue_tail_value(QUEUE hQueue);

Status queue_enque(QUEUE hQueue, int number);

Status queue_deque(QUEUE hQueue);

Bool queue_is_empty(QUEUE hQueue);

void destroy_queue(QUEUE* hQueue);


#endif // !QUEUE_H

#ifndef STACK_H
#define STACK_H

typedef enum bool { False, True } Bool;
typedef enum status {FAILURE, SUCCESS} Status;
typedef void* STACK;

STACK init_default_stack(void);

Status stack_push(STACK hStack, char c);

Status stack_pop(STACK hStack);

char stack_top(STACK hStack, Status* status);

Bool stack_is_empty(STACK hStack);

void stack_destroy(STACK* hStack);


#endif


/**********************************************************************
	Program: Ferry Problem
	Author: Andrew Farrell
	Date: 2/23/21
	Time spent:	A while
	Purpose: Count how many trips it takes a ferry to transport a set of cars
	from one river bank to another.
***********************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include "queue.h"



typedef enum side {LEFT,RIGHT}Side;

Status set_case_parameters(int* length, int* cars);

int get_trips_across(int length, int cars);

void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{
	int cases;
	scanf("%d ", &cases);

	for (int i = 0; i < cases; i++)
	{
		//we need to scan the ferry length and how many cars there will be
		int ferry_length, cars;
		set_case_parameters(&ferry_length, &cars);
		printf("%d\n", get_trips_across(ferry_length, cars));
	}

	return 0;
}

int get_trips_across(int length, int cars)
{
	char side;
	int car_length;
	int trips = 0;
	QUEUE hLeft_Queue = init_queue();
	QUEUE hRight_Queue = init_queue();
	length *= 100; // convert to centimeters
	for (int i = 0; i < cars; i++)
	{
		int noc = scanf("%d %c", &car_length, &side);
		if (noc != 2)
		{
			return -1;
		}
		clear_keyboard_buffer();

		if (side == 'l')
		{
			queue_enque(hLeft_Queue, car_length);
		}
		else if (side == 'r')
		{
			queue_enque(hRight_Queue, car_length);
		}
		else
		{
			return -1;
		}
	}

	Side current_side = LEFT;
	while (!queue_is_empty(hLeft_Queue) || !queue_is_empty(hRight_Queue))
	{
		int temp_length = length;
		if (current_side == LEFT)
		{
			
			while (!queue_is_empty(hLeft_Queue) && (temp_length - queue_tail_value(hLeft_Queue)) >= 0)
			{
				temp_length -= queue_tail_value(hLeft_Queue);
				queue_deque(hLeft_Queue);
				 
			}
			trips++;
			current_side = RIGHT;
			
		}
		else if (current_side == RIGHT )
		{
			
			while (!queue_is_empty(hRight_Queue) && (temp_length - queue_tail_value(hRight_Queue) >= 0)) //uses short circuit evaluation
			{
				temp_length -= queue_tail_value(hRight_Queue);
				queue_deque(hRight_Queue);
				
			}
			trips++;
			current_side = LEFT;

		}

	}
	destroy_queue(&hLeft_Queue);
	destroy_queue(&hRight_Queue);
	return trips;
}

Status set_case_parameters(int * length, int * cars)
{
	int noc = scanf("%d %d ", length, cars);
	if (noc != 2)
	{
		return FAILURE;
	}
	return SUCCESS;
}

void clear_keyboard_buffer(void)
{
	char c;
	int noc;
	noc = scanf("%c", &c);
	while (noc == 1 && c != '\n')
	{
		noc = scanf("%c", &c);
	}
}

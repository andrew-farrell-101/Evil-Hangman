/**********************************************************************
Program: main.c
Author: Andrew Farrell
Date: 2/18/20
Time spent: ~4 Hours...? Who knows.
Purpose: Take in a string of symbols and check if they are in a particular
matching order. If not, print "No", otherwise, print "Yes".
***********************************************************************/

#include "stack.h"
#include <stdio.h>
#include <stdlib.h>



Bool string_is_valid(void);
void clear_keyboard_buffer(void);

int main(int argc, char* argv[])
{
	int n;
	scanf("%d", &n);
	clear_keyboard_buffer();
	for (int i = 0; i < n; i++)
	{
		if (string_is_valid())
		{
			printf("Yes\n");
		}
		else
		{
			printf("No\n");
		}
	}
	return 0;
}

Bool string_is_valid(void)
{
	char c;
	int noc;
	Bool valid = True;

	STACK hStack = init_default_stack();
	if (hStack == NULL)
	{
		printf("Failed to create stack object.");
		exit(-1);
	}

	noc = scanf("%c", &c);

	while (noc == 1 && c != '\n')
	{
		if (valid == False) /* This will let the loop go through the rest of the test case*/
		{
			noc = scanf("%c", &c);
			continue;

		}

		if (c == '{' || c == '[' || c=='(')
		{
			stack_push(hStack, c);
		}
		else 
			/*It is a closing bracket of some kind. Cannot check the top of the stack if there is nothing on it.
				if the stack is empty and a closing is hit, fail. If a closing is hit and it does not match, fail.*/
		{
		if (stack_is_empty(hStack) || ((c == '}' && (stack_top(hStack, NULL) != '{')) || (c == ']' && stack_top(hStack, NULL) != '[') || (c == ')' && stack_top(hStack, NULL) != '(')))
			{
				valid = False;
			}
			else /* There is a closing but a possiblility the stack is just empty */
			{
				stack_pop(hStack); 
			}
		}
			
			
		/*no matter what, do another scan*/
		noc = scanf("%c", &c); 
	}

	if ((c == '\n' && !stack_is_empty(hStack)) || valid == False) /*if there is anything left on the stack and we reached the end of line, failure*/
	{
		stack_destroy(&hStack);
		return False;
	}

	stack_destroy(&hStack);
	return True;
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

#include <stdlib.h>
#include <stdio.h>
#include "stack.h"

void push_and_pop(stack_T stk);

int main(int argc, char * argv[])
{
	(void)argc, (void)argv;

	// Allocating a new stack
	stack_T stk = stack_new();

	// Testing push and pop
	push_and_pop(stk);

	// Freeing the stack
	stack_free(&stk);

	exit(EXIT_SUCCESS);
}


// Pushes some element on the stack and then pops them.
void push_and_pop(stack_T stk)
{
	printf("Testing push and pop...\n");
	int numElems = 10;
	for(int i = 0 ; i < numElems ; i++)
		stack_push(stk,&i);

	printf("Is stack empty: %d\n",stack_empty(stk));

	for(int i = 0 ; i < numElems ; i++){
		void *data = stack_pop(stk);
		printf("DATA: %d\n",*(int *)data);
	}
	printf("Is stack empty: %d\n",stack_empty(stk));
	printf("\n");
}



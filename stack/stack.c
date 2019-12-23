#include "stack.h"
#include <stdlib.h>
#include <stdio.h>
#include "assert.h"


#define T stack_T


struct T{
	int count; 							// Number of elements in the stack.
	struct stackElem *head; 			// Pointer to the head of the stack.
};

struct stackElem{
	void *data;
	struct stackElem * nxt;
};

// Initialize a new stack and returns the stack element.
T stack_new()
{
	T stack = malloc(sizeof(struct T));
	if (stack == NULL){
		printf("CRE: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	stack->count = 0;
	stack->head = NULL;
	return stack;
}

// Adds a new element to the top of the stack
void stack_push(T stack, void *data)
{
	assert(stack);
	struct stackElem *newElem = malloc(sizeof(struct stackElem));
	newElem->data = data;
	newElem->nxt = stack->head;
	stack->head = newElem;
	stack->count++;
}

// Removes the top element of the stack and returns the item stored.
// Returns NULL if there are no items to return.
void * stack_pop(T stack)
{
	assert(stack);
	void * data;
	struct stackElem *topNode;

	if (stack->head == NULL)
		data = NULL;
	else{
		topNode = stack->head;
		stack->head = stack->head->nxt;
		data = topNode->data;
		free(topNode);
		stack->count--;
	}
	return data;	

}

// Returns the top element of the stack
void * stack_top(T stack)
{
	assert(stack);
	return stack->head->data;
}

// Returns 1 if the stack is empty. 0 otherwise.
int stack_empty(T stack)
{
	assert(stack);
	return stack->count == 0;
}


// Frees the stack
void stack_free(T *stack_p)
{
	assert(stack_p);
	struct stackElem *nxt;
	for( ; (*stack_p)->head ; (*stack_p)->head = nxt){
		nxt = (*stack_p)->head->nxt;
		free((*stack_p)->head);
	}
	free(*stack_p);
}



#undef T






























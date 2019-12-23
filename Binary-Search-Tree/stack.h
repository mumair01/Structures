/*
	Implementation of a generic stack that is able to store pointers.

*/


#ifndef STACK_H_
#define STACK_H_

#define T stack_T
typedef struct T* T;


// Initialize a new stack and returns the stack element.
T stack_new();

// Adds a new element to the top of the stack
void stack_push(T stack, void *data);

// Removes the top element of the stack and returns the item stored.
// Returns NULL if there are no items to return.
void * stack_pop(T stack);

// Returns the top element of the stack
void * stack_top(T stack);

// Returns 1 if the stack is empty. 0 otherwise.
int stack_empty(T stack);

// Frees the stack
void stack_free(T *stack_p);



#undef T
#endif


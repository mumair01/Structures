/*
	Array based implementation of a generic queue.
	FIFO data structure.
*/

#ifndef QUEUE_H_
#define QUEUE_H_

#define T Queue_T 
typedef struct T* T;

// Initialize a new queue.
T queue_new();

// Function that adds an element to the start of the queue
void queue_enqueue(T queue, void * data);

// Function that dequeues the last element in the and returns the ptr.
// Returns NULL if the queue is empty.
void *queue_dequeue(T queue);

// Returns 1 if queue is empty. 0 otherwise.
int queue_isEmpty(T queue);

// Returns a copy of the given Queue
T queue_copy(T queue);

// Returns the number of elements in the queue
int queue_size(T queue);

// Function that frees the queue.
void queue_free(T *queue_p);




#undef T
#endif 



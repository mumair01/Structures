#include <stdlib.h>
#include "queue.h"
#include "string.h"
#include "assert.h"
#include <stdio.h>


/*
	This implementation of an boxed queue using an array underlying
	data structure.
*/

#define T Queue_T 

#define initialSize 10 				// Initial size of the queue.

struct T{
	void ** queueArr; 				// UArray that will act as the queue.
	int tailIndex;					// Index of the last element in the queue.
	int frontIndex;					// Index of the first element in the queue.
	int queueSize;					// Maximum size of the queue.
	size_t elemSize;				// Size of the elements in the queue.
	int currLen;					// Current number of elements in the queue.
};

void queue_init(T q_struct, size_t elemSize, int size)
{
	assert(q_struct);
	assert(elemSize > 0);
	q_struct->queueArr = malloc(sizeof(void*) * size);
	if (q_struct->queueArr == NULL){
		printf("CRE: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	q_struct->tailIndex = 0;
	q_struct->frontIndex = 0;
	q_struct->queueSize = initialSize;
	q_struct->currLen = 0;
	q_struct->elemSize = elemSize;
}

// Initialize a new queue.
T queue_new()
{
	T q_struct = malloc(sizeof(struct T));
	if (q_struct == NULL){
		printf("CRE: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	queue_init(q_struct,sizeof(void *),initialSize);
	return q_struct;
}

// Function that adds an element to the start of the queue
void queue_enqueue(T q_struct , void * data)
{
	assert(q_struct);
	if (q_struct->currLen == q_struct->queueSize){
		q_struct->queueSize = q_struct->queueSize * 2;
		void *newArr = malloc(q_struct->elemSize * q_struct->queueSize);
		memcpy(newArr,q_struct->queueArr,q_struct->currLen);
	}

	q_struct->queueArr[q_struct->tailIndex] = data;
	q_struct->tailIndex++;
	q_struct->currLen++;
}

// Function that dequeues the last element in the and returns the ptr.
// Returns NULL if the queue is empty.
void * queue_dequeue(T q_struct)
{
	assert(q_struct);
	assert(q_struct->frontIndex <= q_struct->tailIndex);
	assert(q_struct->frontIndex < q_struct->queueSize);

	if ( q_struct->currLen == 0)
		return NULL;

	void * data = q_struct->queueArr[q_struct->frontIndex];
	q_struct->frontIndex++;
	q_struct->currLen--;
	return data;
}

// Returns 1 if queue is empty. 0 otherwise.
int queue_isEmpty(T q_struct)
{
	assert(q_struct);
	if( q_struct->currLen == 0)
		return 1;
	return 0;
}

// Returns a copy of the given Queue
T queue_copy(T q_struct)
{
	assert(q_struct);
	T new_struct = malloc(sizeof(struct T));
	if (new_struct == NULL){
		printf("CRE: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	printf("ELEM SIZE: %lu\n",q_struct->elemSize);
	queue_init(new_struct,q_struct->elemSize,q_struct->currLen);
	memcpy(new_struct->queueArr,q_struct->queueArr,q_struct->currLen);
	return new_struct;

}

// Returns the number of elements in the queue
int queue_size(T q_struct)
{
	assert(q_struct);
	printf("ELem size %lu\n",q_struct->elemSize);
	return q_struct->currLen;
}


// Function that frees the queue.
void queue_free(T *queue_p)
{
	assert(queue_p && *queue_p);
	free((*queue_p)->queueArr);
	free(*queue_p);
}




#undef T
























































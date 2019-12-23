#include <stdlib.h>
#include <stdio.h>
#include "queue.h"
#include "UArray.h"




int main(int argc, char *argv[])
{
	(void)argc,(void)argv;

	// Initializing the queue
	Queue_T q = queue_new(sizeof(void *));

	//Appending to the queue.
	int data1 = 10, data2 = 20;
	queue_enqueue(q,&data1);
	queue_enqueue(q,&data2);

	printf("Queue size: %d\n",queue_size(q));

	
	// Copying and testing the queue
	Queue_T copy = queue_copy(q);
	printf("Copy queue size: %d\n",queue_size(q));
	int copysize = queue_size(copy);
	for(int i = 0 ; i <copysize ; i++){
		int * d = queue_dequeue(copy);
		printf("Dequeue value: %d\n",*d);
	}
	printf("Copy SUCCESSFUL\n");


	// Dequeing and printing
	int size = queue_size(q);
	for(int i = 0 ; i < size ; i++){
		int * d = queue_dequeue(q);
		printf("Dequeue value: %d\n",*d);
	}
	queue_dequeue(q);

	// Freeing the queue.
	queue_free(&q);
	queue_free(&copy);

	exit(EXIT_SUCCESS);
}


































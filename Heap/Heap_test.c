#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "Heap.h"

int compare(void *p1, void *p2);
void addElems(Heap_T heap, int numElems,int type);
void deleteElems(Heap_T heap, int numElems, int type);


struct testNode{
	int val;
};

int main(int argc, char *argv [])
{
	(void)argc,(void)argv;


	void *root = NULL;
	int numElems = 10;

	// *** Max heap testing ***
	printf("Testing max heap...\n");

	// Instanitating an instance of a heap
	Heap_T maxHeap = heap_new(sizeof(struct testNode));

	// Adding a new element to the heap
	addElems(maxHeap,numElems,1);

	// Printing the root node of the heap
	heap_root(maxHeap,&root);
	printf("Max heap root: %d\n\n",((struct testNode *)root)->val);
	free(root);



	// Deleting elements from the heap
	deleteElems(maxHeap,numElems,1);

	// Freeing the heap
	heap_free(&maxHeap);
	printf("Finished testing max heap\n\n");

	// *** Ending max heap test ***


	// *** Min heap testing ***
	printf("Testing min heap...\n");

	// Instantiating an instance of a heap
	Heap_T minHeap = heap_new(sizeof(struct testNode));

	// Adding a new element to the heap
	addElems(minHeap, numElems,0);

	// Printing the root node of the heap
	heap_root(minHeap,&root);
	printf("Min heap root: %d\n\n",*(int *)root);
	free(root);	

	// Deleting elements from the heap
	deleteElems(minHeap,numElems,0);

	// Freeing the heap
	heap_free(&minHeap);
	printf("Finished testing min heap\n\n");



	exit(EXIT_SUCCESS);
}


// Int compare function
int compare(void *p1, void *p2)
{
	if (*(int *) p1 > *(int *)p2)
		return 1;
	else if (*(int *) p1 < *(int *)p2)
		return 0;
	else
		return -1;
}

// Adds random elements to the heap
void addElems(Heap_T heap, int numElems, int type)
{
	srand(time(0)); 
	for(int i = 0 ; i < numElems ; i++){
		struct testNode *val = malloc(sizeof(struct testNode));
		val->val = rand() % 100;
		printf("Insert val %d\n",val->val);
		insert(heap,(void *)val,compare,type);
		free(val);
	}	
}


// Removes 'n' elements from the heap
void deleteElems(Heap_T heap, int numElems,int type)
{
	void *val = NULL;
	for(int i = 0 ; i < numElems ; i++){
		heap_root(heap,&val);
		removeRoot(heap,compare,type);
		printf("Delete item: %d\n",((struct testNode *)val)->val);
		free(val);
	}
}

// Freeing function for the node
void freeNode(void *elem_p)
{
	(void)elem_p;
	return;
}













































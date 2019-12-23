/* A heap is a binary search tree that has two properties:
	1. It is a complete binary tree i.e. every node other than the 
		leaves has two children. The last level is the only one that
		does not have to be completely filled. (shape)

	2. A parent node in the heap must have values greater than or 
		equal to or less than or equal to its children depending on
		the type of heap. (order)
		
Min-heap:
	- Heap where the parent node values are less than or equal to the
		children values.
Max-heap:
	- Heap where the parent node values are greater than or equal to
		the children values.

**NOTE: This is an arrray based implementation of a binary search tree.

*/



#ifndef HEAP_H_
#define HEAP_H_


#define T Heap_T
typedef struct T* T;

/*
	The compare function should be as follows:
	- Return 1 if *p1 > *p2
	- Return 0 if *p1 < *p2
	- Return -1 if *p1 == *p2
*/


// Initiaite a new instance of a heap
T heap_new(size_t elemSize);

// Free the heap data structure
void heap_free(T *heap);

// Copies rootNode value into the given pointer
// Caller has to free copy
void heap_root(T heap,void **val_pp);

// Insert an element into the heap
// type == 1 for max heap
// type == 0 for min heap
void heapInsert(T heap, void *val , int compare(void *p1, void *p2),
	int type);

// Deletes the root node for the heap
// type == 1 for max heap
// type == 0 for min heap
void heapRemoveRoot(T heap, int compare(void *p1, void *p2), int type);


#undef T
#endif






















































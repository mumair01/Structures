#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "assert.h"
#include "Heap.h"
#include "UArray.h"

#define T Heap_T
#define initialSize 1000

struct T{
	UArray_T tree;				// Array that acts as a binary tree.
	int arrSize;				// Total size of the tree
	int size;					// Number of elements in the heap.
	size_t elemSize; 			// Size of the element in the heap.
};


// Helper function that returns the index of the parent node of the 
// current node
int returnParent(int currIndex)
{
	assert(currIndex >= 0);
	return (currIndex - 1)/2;
}

// Helper function that returns the index of the left child of the 
// current node
int returnLeftChild(int currIndex)
{
	assert(currIndex >= 0);
	return (2*currIndex) + 1;
}

// Helper function that returns the index of the right child of the 
// current node
int returnRightChild(int currIndex)
{
	assert(currIndex >= 0);
	return (2*currIndex) + 2;
}

// Helper function resize the internal tree
void resizeTree(T heap_struct)
{
	assert(heap_struct);

	if(heap_struct->size >= UArray_len(heap_struct->tree)){
		heap_struct->arrSize = heap_struct->arrSize * 2;
		UArray_resize(heap_struct->tree,heap_struct->arrSize);
	}
}


void heap_init(T heap_struct,size_t elemSize)
{
	assert(heap_struct);
	heap_struct->arrSize = initialSize;
	heap_struct->tree = UArray_new(initialSize, elemSize);
	heap_struct->size = 0;
	heap_struct->elemSize = elemSize;
}

// Initiaite a new instance of a heap
T heap_new(size_t elemSize)
{
	T heap_struct = malloc(sizeof(struct T));
	if (! heap_struct){
		printf("CRE: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	heap_init(heap_struct,elemSize);
	return heap_struct;
}

// Free the heap data structure
void heap_free(T *heap_struct_p)
{
	assert(heap_struct_p && *heap_struct_p);
	UArray_free(&(*heap_struct_p)->tree);
	free(*heap_struct_p);
}

// Returns the top element of the heap
void heap_root(T heap_struct,void **val_pp)
{
	assert(heap_struct);
	assert(val_pp);
	*val_pp = malloc(heap_struct->elemSize);
	memcpy(*val_pp,UArray_at(heap_struct->tree,0),heap_struct->elemSize);

}

// Helper function that swapws 
void swap_node(void *currVal,void *swapVal,size_t elemSize)
{
	// Only swap different pointers
	if (currVal == swapVal)
		return;
	// Storing curr in temp
	void *temp = malloc(elemSize);
	memcpy(temp,currVal,elemSize);
	// Copying nxt into curr
	memcpy(currVal,swapVal,elemSize);
	// Copying temp into nxt
	memcpy(swapVal,temp,elemSize);
	free(temp);
}

// Helper function for removeNode
void heapify_down(UArray_T tree,int nodeIndex,
	int compare(void *p1, void *p2), int size, int type)
{

	assert(tree && compare);
	assert(nodeIndex >= 0 && size >= 0);
	assert(type == 0 || type == 1);

	int leftChildIndex, rightChildIndex;
	int newIndex = nodeIndex;
	void *curr;


	leftChildIndex = returnLeftChild(nodeIndex);
	rightChildIndex = returnRightChild(nodeIndex);

	curr = UArray_at(tree,nodeIndex);


	if (leftChildIndex < size && 
		compare(UArray_at(tree,leftChildIndex),curr) == type)
		newIndex = leftChildIndex;

	if (rightChildIndex < size &&
		compare(UArray_at(tree,rightChildIndex),
			UArray_at(tree,newIndex)) == type)
		newIndex = rightChildIndex;

	if (newIndex != nodeIndex){
		swap_node(curr,UArray_at(tree,newIndex),UArray_elemSize(tree));
		heapify_down(tree,newIndex,compare,size,type);
	}
}

// Deletes and returns the rootNode for a heap
/*
	- To delete we need to remove the roort node for the entire node
	- To preserve shape, the rightmost leaf can be subsituted to 
		the root position.
	- The root node can be heapified down in order preserve order
*/
// Deletes the root node for the heap
// type == 1 for max heap
// type == 0 for min heap
void heapRemoveRoot(T heap_struct, int compare(void *p1, void *p2), int type)
{
	assert(heap_struct && compare);
	assert(type == 0 || type == 1);
	assert(heap_struct->size >0 );

	// Empty heap
	if (heap_struct->size == 0)
		return;

	// Removing the top node
	swap_node(UArray_at(heap_struct->tree,0),UArray_at(heap_struct->tree,
		heap_struct->size-1),heap_struct->elemSize);
	heap_struct->size--;

	heapify_down(heap_struct->tree,0,compare,heap_struct->size,type);
}




// Heapify up helper function that takes the defined element to the 
// top of the heap
// type == 1 for max heap
// type == 0 for min heap
void heapify_up(UArray_T tree, int nodeIndex, int compare(void *p1, 
	void *p2), int type)
{
	assert(tree && compare);
	assert(nodeIndex >= 0);
	assert(type == 0 || type == 1);

	int parentIndex;
	void *curr, *parent;

	if (nodeIndex != 0){
		parentIndex = returnParent(nodeIndex);
		curr = UArray_at(tree,nodeIndex);
		parent = UArray_at(tree,parentIndex);
		if (type == 0 && compare(curr,parent) == 0){
			swap_node(curr,parent,UArray_elemSize(tree));
			heapify_up(tree,parentIndex, compare,type);
		}
		else if (type == 1 && compare(curr,parent) == 1){
			swap_node(curr,parent,UArray_elemSize(tree));
			heapify_up(tree,parentIndex,compare,type);
		}
	}
}


/*
	SHAPE PROPERTY:
	The heap is a complete tree i.e. we need to make sure that 
	elements are added to the left-most position in the tree.

	ORDER PROPERTY:
	The max heap has to be such that the root is always greater/less than
	or equal to the child nodes.
	We do this by swapping child with the root recursively
*/


// Insert an element into the heap
// type == 1 for max heap
// type == 0 for min heap
void heapInsert(T heap_struct, void *val_p , int compare(void *p1, void *p2),
	int type)
{
	assert(heap_struct && compare);
	assert(val_p);
	assert(type == 0 || type == 1);

	// Checking if the array needs to be resized
	resizeTree(heap_struct);

	// Adding to the end of array to maintain shape
	memcpy(UArray_at(heap_struct->tree,heap_struct->size), val_p,
		heap_struct->elemSize);
	heap_struct->size++;

	// Heapifying up to maintain order
	heapify_up(heap_struct->tree,heap_struct->size - 1,compare,type);

}


#undef T























































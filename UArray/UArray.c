#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "UArray.h"
#include "assert.h"
#include "Heap.h"

#define T UArray_T

struct T{
	int len;
	size_t elemSize;
	char *elems;
};


void init(T ray_struct, int length, size_t elemSize, void *elems)
{
	assert(ray_struct);
	assert((elems && length > 0 ) || (elems == NULL && length == 0));
	assert(elemSize > 0);
	ray_struct->len = length;
	ray_struct->elemSize = elemSize;
	ray_struct->elems = elems;

}

T UArray_new(int length, size_t elemSize)
{
	assert(length >= 0 && elemSize > 0);
	T ray_struct = malloc(sizeof(struct T));
	if (length > 0)
		init(ray_struct, length, elemSize, calloc(length,elemSize));
	else
		init(ray_struct,length,elemSize,NULL);
	return ray_struct; 
}


void UArray_free(T *ray_struct_p)
{
	assert(ray_struct_p && *ray_struct_p);
	free((*ray_struct_p)->elems);
	free(*ray_struct_p);
}

int UArray_len(T ray_struct)
{
	assert(ray_struct);
	return ray_struct->len; 
}

size_t UArray_elemSize(T ray_struct)
{
	assert(ray_struct);
	return ray_struct->elemSize;
}

void * UArray_at(T ray_struct,int index)
{
	assert(ray_struct);
	assert(index < ray_struct->len && index >= 0);
	return (ray_struct->elems + (index * ray_struct->elemSize));
}

void UArray_resize(T ray_struct, int new_length)
{
	assert(ray_struct);
	assert(new_length >= 0);
	void *newElems = NULL;
	if (new_length == 0){
		free(ray_struct->elems);
		ray_struct->elems = NULL;
	}
	else if (ray_struct->len == 0){
		ray_struct->elems = malloc(ray_struct->elemSize * new_length);
		if (ray_struct->elems == NULL){
			printf("CRE: Memory allocation failed\n");
			exit(EXIT_FAILURE);
		}
	}
	else{
		if (new_length > ray_struct->len)
			newElems = memcpy(calloc(new_length,ray_struct->elemSize)
				,ray_struct->elems,ray_struct->len * ray_struct->elemSize);
		else
			newElems = memcpy(calloc(new_length,ray_struct->elemSize)
				,ray_struct->elems,new_length * ray_struct->elemSize);
		free(ray_struct->elems);
		ray_struct->elems = newElems;
	}
	ray_struct->len = new_length;

}

T UArray_copy(T ray_struct, int new_length)
{
	assert(ray_struct);
	assert(new_length >= 0);
	T new_arr = UArray_new(new_length,ray_struct->elemSize);
	if (new_arr->len > ray_struct->len && ray_struct->len > 0)
		memcpy(new_arr->elems,ray_struct->elems,
			ray_struct->elemSize * ray_struct->len);
	else if (ray_struct->len >= new_arr->len && new_arr->len > 0)
		memcpy(new_arr->elems,ray_struct->elems,new_length * 
			ray_struct->elemSize);
	return new_arr;

}

// Helper function that swapws 
void swap(void *currVal,void *swapVal,size_t elemSize)
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

// Function that reverses the order of elements in the array
// Does an in-place reverse
void UArray_reverse(T ray_struct)
{
	assert(ray_struct);

	int midIndex = (ray_struct->len - 1) / 2;
	size_t elemSize = ray_struct->elemSize;

	for(int i = 0 ; i <= midIndex ; i++){
		swap(UArray_at(ray_struct,i),UArray_at(ray_struct,
			ray_struct->len - 1 - i),elemSize);
	}

}






// Bubble sort algorithm implementation
// In-place implementation
// Time complexity: O(n^2)
void UArray_bubble_sort(T ray_struct, int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);

	void *curr,*nxt;
	curr = nxt = NULL;
	int swapped;
	size_t elemSize = ray_struct->elemSize;
	int arrLen = ray_struct->len;

	for(int i = 0 ; i < arrLen ; i++){
		swapped = 0;
		for(int j = 0 ; j < arrLen - i -1 ; j++){
			curr = UArray_at(ray_struct,j);
			nxt = UArray_at(ray_struct,j+1);
			// Element at index j is greater than element at index j+1
			if (compare(curr,nxt) > 0){
				swap(curr,nxt,elemSize);
				swapped = 1;
			}	
		}
		if (swapped == 0)
			break;
	}
}

// Selection sort algorithm implementation
// In place implementation
// Split the array into sections. 
// Find smallest value in the array and replace with the top value
// Time complexity: O(n^2)
void UArray_selection_sort(T ray_struct, int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);

	void *min,*curr;
	min = curr = NULL;
	int minIndex;

	size_t elemSize = ray_struct->elemSize;
	int arrLen = ray_struct->len;
	for(int i = 0 ; i < arrLen - 1 ; i++){
		minIndex = i;
		for(int j = i ; j < arrLen ; j++){
			min = UArray_at(ray_struct,minIndex);
			curr = UArray_at(ray_struct,j);
			// Curr is smaller than min
			if (compare(min,curr) > 0)
				minIndex = j;
		}
		// Moving min to the start of the array
		if (minIndex != i)
			swap(UArray_at(ray_struct,i),UArray_at(ray_struct,minIndex),elemSize);
	}
}


// Insertion sort algorithm implementation
// For every element, determines if the last element is greater than the current 
// If so, shifts the previous array forward one by one until needed.
// Adds the curr element at the correct position
// Time complexity: O(n^2)
void UArray_insertion_sort(T ray_struct, int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);

	void*curr = NULL;

	size_t elemSize = ray_struct->elemSize;
	int arrLen = ray_struct->len;

	for(int i = 1 ; i < arrLen ; i++){
		curr = UArray_at(ray_struct,i);
		int j = i-1;
		// Element at j is greater than the element at i
		while( j>= 0 && compare(UArray_at(ray_struct,j),curr) > 0){
			memcpy(UArray_at(ray_struct,j+1),UArray_at(ray_struct,j),elemSize);
			j = j-1;
		}
		// Adding the curr element to the correct position in the arr
		if (j >= 0 && j != i)
			memcpy(UArray_at(ray_struct,j),curr,elemSize);
	}
}



// Helper function to merge the elements in a merge sort
void merge(T ray_struct, int leftIndex, int midIndex, int rightIndex,
	int compare(void *p1, void *p2))
{

	assert(ray_struct);
	assert(leftIndex >= 0 && rightIndex >= 0 && midIndex >= 0 );

	int len1, len2, count1, count2, mergeIndex;
	size_t elemSize = ray_struct->elemSize;

	// The 1 is added because the mid-value is rounded down
	// Adds up to original array length
	len1 = midIndex - leftIndex + 1;
	len2 = rightIndex - midIndex;

	// Auxillary arrays
	char *arr1 = malloc(len1 * ray_struct->elemSize);
	char *arr2 = malloc(len2 * ray_struct->elemSize);

	for(int i = 0 ; i < len1 ; i++){
		memcpy(arr1 + (elemSize * i), UArray_at(ray_struct,leftIndex + i), elemSize);
	}

	for(int i = 0 ; i < len2 ; i++){
		memcpy(arr2 + (elemSize * i), UArray_at(ray_struct,1+midIndex + i),elemSize);
	}

	count1 = 0;					// Initial index of first sub-array
	count2 = 0;					// Initial index of second sub-array
	mergeIndex = leftIndex;		// Initial index of the original array

	// Sorting through both arrays into one bigger array
	while(count1 < len1 && count2 < len2){

		if (compare(arr1 + (count1 * elemSize),arr2 + (count2 * elemSize)) < 1) {
			memcpy(UArray_at(ray_struct,mergeIndex), arr1 + (elemSize * count1),elemSize);
			count1++;
		}
		else{
			memcpy(UArray_at(ray_struct,mergeIndex), arr2 + (elemSize * count2),elemSize);
			count2++;
		}
		mergeIndex++;
	}

	// Adding elements from arr1 if left
	while(count1 < len1){
		memcpy(UArray_at(ray_struct,mergeIndex), arr1 + (elemSize * count1),elemSize);
		count1++;
		mergeIndex++;
	}

	// Adding elements from arr2 if left
	while( count2 < len2 ){
		memcpy(UArray_at(ray_struct,mergeIndex), arr2 + (elemSize * count2),elemSize);
		count2++;
		mergeIndex++;
	}
	free(arr1);
	free(arr2);


}

// Helper function to divide the elements of the array in merge sort
void divide(T ray_struct, int leftIndex, int rightIndex,int compare(void *p1, void *p2))
{
	assert(ray_struct);
	assert(leftIndex >= 0 && rightIndex >= 0);

	// More than one element in the array.
	if (leftIndex < rightIndex){
		int midIndex = leftIndex + (rightIndex - leftIndex) / 2;
		divide(ray_struct,leftIndex,midIndex,compare);
		divide(ray_struct,midIndex+1,rightIndex,compare);
		merge(ray_struct, leftIndex ,midIndex, rightIndex,compare);
	}



}

// Merge sort algorithm implementation
// Is stable i.e. the order of equal keys is not changed b/w input and output
// Divide and conquer algorithm
// The algorithm will recursively divide the list into single element lists that are sorted
// The single element lists are then grouped together in sorted order until a 
// list of the original N size is made
// Auxillary data structures: Two char arrays.
// Time complexity: O(n lg(n))
void UArray_merge_sort(T ray_struct, int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);
	divide(ray_struct,0,ray_struct->len-1,compare);

}


// Helper function for the quicksort algorithm
// This uses the Lomuto partition scheme
int lumoto_partition(T ray_struct,int leftIndex, int rightIndex,
	int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);
	assert(leftIndex >= 0 && rightIndex >= 0);

	int pivotIndex, i;
	void *pivotElem;
	size_t elemSize = ray_struct->elemSize;

	// Pivot is the rightmost element
	pivotIndex = rightIndex;
	i = leftIndex;
	pivotElem = UArray_at(ray_struct,pivotIndex);

	for(int j = leftIndex ; j < rightIndex ; j++){
		// Curr element is less than the pivot
		if (compare(UArray_at(ray_struct,j), pivotElem) == 0){
			// Find a lower element than pivot on the left and swap with a greater element
			swap(UArray_at(ray_struct,i),UArray_at(ray_struct,j),elemSize);
			i++;
		}
	}
	swap(UArray_at(ray_struct,i),pivotElem,elemSize);
	return i;
}	


// Helper function for the quicksort function
void lumoto_quicksort(T ray_struct,int leftIndex, int rightIndex,
	int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);
	//assert(leftIndex >= 0 && rightIndex >= 0);
	int partitionIndex;

	// Only applied if array has at least two elements
	if (leftIndex < rightIndex){
		partitionIndex = lumoto_partition(ray_struct,leftIndex,rightIndex,compare);
		// Applying quick sort on the left sub-array
		lumoto_quicksort(ray_struct,leftIndex,partitionIndex - 1,compare);
		// Applying quick sort on the right sub-array
		lumoto_quicksort(ray_struct,partitionIndex+1,rightIndex,compare);
	}


}

// Quicksort algorithm implementation
// Uses a pivot and places smaller items to left and larger to right
// Ensures pivot is in correct position.
// Continues approach in the subsets produced by this pivot
// Is  an unstable sorting algorithm
// In place algorithm
// Time complexity: O(n^2)
// Min. time complexity: O(n lg(n))

/*
	Quick sort has multiple partitioning schemes:
	1. Lomuto scheme
		- O(n^2)
		- Min: O(nlg(n))

*/

void UArray_quick_sort_lumoto(T ray_struct, int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);
	lumoto_quicksort(ray_struct,0,ray_struct->len - 1,compare);
}


// Helper function that calculates the pivot for hoare sort using the median
// of three rule.
// Returns the index of the partition
int median_of_three_pivot(T ray_struct,int compare(void *p1, void *p2), 
	int leftIndex, int rightIndex)
{
	assert(ray_struct && compare);

	size_t elemSize = ray_struct->elemSize;

	// This form is used to prevent overflow for large boundaries
	int pivotIndex = leftIndex + ((rightIndex - leftIndex)/2);

	// Left is greater than the middle
	if (compare(UArray_at(ray_struct,leftIndex), UArray_at(ray_struct,pivotIndex)) == 1)
		swap(UArray_at(ray_struct,leftIndex),UArray_at(ray_struct,pivotIndex),
			elemSize);
	// Left is greater than right
	if (compare(UArray_at(ray_struct,leftIndex), UArray_at(ray_struct,rightIndex)) == 1)
		swap(UArray_at(ray_struct,leftIndex),UArray_at(ray_struct,rightIndex),
			elemSize);
	// Middle is greater than right
	// This puts the median element on the right-most position
	if (compare(UArray_at(ray_struct,rightIndex), UArray_at(ray_struct,pivotIndex)) == 1)
		swap(UArray_at(ray_struct,pivotIndex),UArray_at(ray_struct,rightIndex),
			elemSize);
	return rightIndex;


}

// Helper function for the quicksort algorithm
// This uses the hoare partition scheme
int hoare_partition(T ray_struct,int leftIndex, int rightIndex,
	int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);
	assert(leftIndex >= 0 && rightIndex >= 0);

	size_t elemSize = ray_struct->elemSize;

	int pivotIndex = median_of_three_pivot(ray_struct,compare, leftIndex,rightIndex);

	void * pivotElem = UArray_at(ray_struct,pivotIndex);

	while(1){


		//printf("Left index %d, right index %d\n",leftIndex,rightIndex);

		// Move left until curr is greater than the pivot
		while(compare(UArray_at(ray_struct,leftIndex), pivotElem) == 0)
			leftIndex++;
		// Move right until curr is less than the pivot
		while(compare(UArray_at(ray_struct,rightIndex), pivotElem) == 1)
			rightIndex--;
		//printf("Left index %d, Right index %d\n",leftIndex,rightIndex);
		// Stop if both indicies are equal
		if (leftIndex >= rightIndex)
			return rightIndex;

		// Swap invertable elements
		swap(UArray_at(ray_struct,leftIndex),UArray_at(ray_struct,rightIndex),
			elemSize);
		leftIndex++;
		rightIndex--;
	}

}



// Helper function for the quicksort function
void hoare_quicksort(T ray_struct,int leftIndex, int rightIndex,
	int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);
	//assert(leftIndex >= 0 && rightIndex >= 0);
	int partitionIndex;

	// Only applied if array has at least two elements
	if (leftIndex < rightIndex){
		partitionIndex = hoare_partition(ray_struct,leftIndex,rightIndex,compare);
		// Applying quick sort on the left sub-array
		hoare_quicksort(ray_struct,leftIndex,partitionIndex,compare);
		// Applying quick sort on the right sub-array
		hoare_quicksort(ray_struct,partitionIndex+1,rightIndex,compare);
	}


}

// Quicksort algorithm implementation using Hoare partition scheme
void UArray_quick_sort_hoare(T ray_struct, int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);
	hoare_quicksort(ray_struct,0,ray_struct->len - 1,compare);
}


// Heap sort algorithm implementation
/*
	Steps:
	1. Build min heap.
	2. Remove root from heap and replace the corrsponding array element
	3. Delete the heap.
*/
void UArray_heap_sort(T ray_struct, int compare(void *p1, void *p2))
{
	assert(ray_struct && compare);
	void *val;

	// Build min heap.
	Heap_T minHeap = heap_new(ray_struct->elemSize);

	// Inserting all elements of array into the heap
	for(int i = 0 ; i < ray_struct->len ; i++)
		heapInsert(minHeap,UArray_at(ray_struct,i),compare,0);
	

	// Removing elements from the heap and freeing
	for(int i = 0 ; i < ray_struct->len ; i++){
		val = UArray_at(ray_struct,i);
		heap_root(minHeap,&val);
		heapRemoveRoot(minHeap,compare,0);
		memcpy(UArray_at(ray_struct,i),val,ray_struct->elemSize);
		free(val);
	}

	heap_free(&minHeap);

}

#undef T
















































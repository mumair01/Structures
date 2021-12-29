#ifndef UARRAY_H_
#define UARRAY_H_

#define T UArray_T
typedef struct T *T;

// Instantiate a new element of the UArray
T UArray_new(int length, size_t elemSize);

// Free the UArray
void UArray_free(T *uarray_p);

// Returns the legth of the UArray
int UArray_len(T uarray);

// Returns the elemt size of the UArray
size_t UArray_elemSize(T uarray);

// Returns a pointer to an item in the array at given index.
void *UArray_at(T uarray, int index);

// Resizes the UArray to a new UArray
void UArray_resize(T uarray, int new_length);

// Resizes the array and returns a copy of the original array.
T UArray_copy(T uarray, int new_length);

// Function that reverses the order of elements in the array
void UArray_reverse(T uarray);

/*
	The compare function should be as follows:
	- Return 1 if *p1 > *p2
	- Return 0 if *p1 < *p2
	- Return -1 if *p1 == *p2
*/

// Bubble sort algorithm implementation
void UArray_bubble_sort(T uarray, int compare(void *p1, void *p2));

// Selection sort algorithm implementation
void UArray_selection_sort(T uarray, int compare(void *p1, void *p2));

// Insertion sort algorithm implementation
void UArray_insertion_sort(T uarray, int compare(void *p1, void *p2));

// Merge sort algorithm implementation
void UArray_merge_sort(T uarray, int compare(void *p1, void *p2));

// Quicksort algorithm implementation using lumoto partition scheme
void UArray_quick_sort_lumoto(T uarray, int compare(void *p1, void *p2));

// Quicksort algorithm implementation using hoare partition scheme
void UArray_quick_sort_hoare(T uarray, int compare(void *p1, void *p2));

// Heap sort algorithm implementation
void UArray_heap_sort(T uarray, int compare(void *p1, void *p2));

#undef T
#endif

#ifndef UARRAY_H_
#define UARRAY_H_

#define T UArray_T 
typedef struct T* T;

// Instantiate a new element of the UArray
T UArray_new(int length, size_t elemSize);

// Free the UArray
void UArray_free(T *uarray_p);

// Returns the legth of the UArray
int UArray_len(T uarray);

// Returns the elemt size of the UArray
size_t UArray_elemSize(T uarray);

// Returns a pointer to an item in the array at given index.
void * UArray_at(T uarray, int index);

// Resizes the UArray to a new UArray
void UArray_resize(T uarray, int new_length);

// Resizes the array and returns a copy of the original array.
T UArray_copy(T uarray, int new_length);

#undef T
#endif



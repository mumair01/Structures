/*
	Header file for a 2D unboxed array with blocks
	An unboxed array is such that it contains the element itself 
	rather than a pointer to the element.

	Made by: Muhammad Umair
	7/28/19
*/



#ifndef UARRAY2b_H_
#define UARRAY2b_H_

#define T UArray2b_T
typedef struct T* T;


// Initialize a new unboxed blocked 2D array
T UArray2b_new(int width,int height, size_t elemSize, int blockSize);

// Initialize a new unboxed blocked 2D array with 64K byte blocks
T UArray2b_new_64K(int width, int height, size_t elemSize);

// Free an unboxed blocked 2D array
void UArray2b_free(T * uarray2b);

// Returns the width of the 2b array
int UArray2b_width(T uarray2b);

// Returns the height of the 2b array
int UArray2b_height(T uarray2b);

// Returns the elemSize of an element in the 2b array
size_t UArray2b_elemSize(T uarray2b);

// Returns the Blocksize
int UArray2b_blockSize(T uarray2b);

// Returns a pointer to a specified element in the array
void * UArray2b_at(T uarray2b, int col, int row);

// Does a column major mapping through the array
// Row indicies change faster.
void UArray2b_map_col_major(T uarray2b,void apply(T UArray2b, void *, void *),
	void *closure);

// Does a row major mapping through the array.
// Columns indicies change faster.
void UArray2b_map_row_major(T uarray2b,void apply(T uarray2b, void *, void*),
	void *closure);

// Columns major block mapping
void UArray2b_map_block(T uarray2b,void(T uarray2b, void *, void*),
	void *closure);




#undef T
#endif











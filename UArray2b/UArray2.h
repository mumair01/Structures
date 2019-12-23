#ifndef UARRAY2_H_
#define UARRAY2_H_

#define T UArray2_T
typedef struct T *T;



// Initialize a new UArray2 instance
T UArray2_new(int width,int height, size_t elemSize);

// Free an instance of UArray2
void UArray2_free(T *uarray2);

// Returns the num of cols.
int UArray2_width(T uarray2);

// Returns the num of rows
int UArray2_height(T uarray2);

// Returns the size of the elements
size_t UArray2_elemSize(T uarray2);

// Returns the pointer to an index in the arr
void * UArray2_at(T uarray2, int col, int row);

// Row major mapping. Column indicies change faster
void UArray2_map_row_major(T uarray2, void apply(T ray_struct,void *,
	void *), void *closure);

// Col major mapping. Row indicicies change faster
void UArray2_map_col_major(T uarray2, void apply(T ray_struct,void *,
	void *), void *closure);

// Resizes the array
void UArray2_resize(T uarray2,int new_width,int new_height);

// Resizes the array and returns a copy of the original array.
T UArray2_copy(T uarray2, int new_width, int new_height);







#undef T
#endif


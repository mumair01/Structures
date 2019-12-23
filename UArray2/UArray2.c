#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "UArray.h"
#include "UArray2.h"



#define T UArray2_T

struct T{
	int width;
	int height;
	size_t elemSize;
	UArray_T in_arr;
};


// Helper function to initalize the array.
void UArray2_init(T ray_struct,int width, int height, size_t elemSize,
	UArray_T in_arr)
{
	assert(ray_struct);
	assert(width >= 0 && height >= 0);
	assert(elemSize > 0);
	assert(width * height >=0 );
	ray_struct->width = width;
	ray_struct->height = height;
	ray_struct->elemSize = elemSize;
	ray_struct->in_arr = in_arr;
}	


// Initialize a new UArray2 instance
T UArray2_new(int width,int height,size_t elemSize)
{
	assert(width >= 0 && height >= 0);
	assert(elemSize > 0);
	T ray_struct = malloc(sizeof(struct T));
	UArray2_init(ray_struct,width,height,elemSize,
		UArray_new(width*height,elemSize));
	return ray_struct;
}

// Free an instance of UArray2
void UArray2_free(T * ray_struct_p)
{
	assert(ray_struct_p);
	UArray_free(&(*ray_struct_p)->in_arr);
	free(*ray_struct_p);

}

int UArray2_width(T ray_struct)
{
	assert(ray_struct);
	return ray_struct->width;
}

int UArray2_height(T ray_struct)
{
	assert(ray_struct);
	return ray_struct->height;
}

size_t UArray2_elemSize(T ray_struct)
{
	assert(ray_struct);
	return ray_struct->elemSize;
}

void * UArray2_at(T ray_struct, int col, int row)
{
	assert(ray_struct);
	assert(col >= 0 && row >= 0 );
	assert(col < ray_struct->width && row < ray_struct->height);
	int index;
	index = (ray_struct->width * row) + col;
	return UArray_at(ray_struct->in_arr,index);
}

void UArray2_map_row_major(T ray_struct, void apply(T ray_struct,void *,
	void *), void *closure)
{
	assert(ray_struct);
	assert(apply);
	int width,height;

	width = ray_struct->width;
	height = ray_struct->height;

	for (int row = 0 ; row < height ; row++){
		for (int col = 0 ; col < width ; col++){
			apply(ray_struct,UArray2_at(ray_struct,col,row),closure);
		}
	}
}

void UArray2_map_col_major(T ray_struct, void apply(T ray_struct,void *,
	void *), void *closure)
{
	assert(ray_struct);
	assert(apply);
	int width,height;

	width = ray_struct->width;
	height = ray_struct->height;

	for(int col = 0 ; col < width ; col++){
		for(int row = 0 ; row < height ; row++){
			apply(ray_struct,UArray2_at(ray_struct,col,row),closure);
		}
	}
}


void UArray2_resize(T ray_struct,int new_width,int new_height)
{
	assert(ray_struct);
	assert(new_width >= 0 && new_height >= 0);
	UArray_resize(ray_struct->in_arr,new_height*new_width);
	ray_struct->width = new_width;
	ray_struct->height = new_height;
}


T UArray2_copy(T ray_struct, int new_width, int new_height)
{
	assert(ray_struct);
	assert(new_height >= 0 && new_width >= 0);
	T new_ray_struct = malloc(sizeof(struct T));
	UArray2_init(new_ray_struct,new_width,new_height,ray_struct->elemSize,
		UArray_copy(ray_struct->in_arr,new_width * new_height));
	return new_ray_struct;
}





#undef T


























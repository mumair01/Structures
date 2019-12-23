#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "UArray.h"
#include "UArray2.h"



#define T UArray2_T

struct T{
	int width;
	int height;
	int elemSize;
	UArray_T in_arr;
};

T UArray2_new(int width,int height,size_t elemSize)
{
	assert(width > 0 && height > 0 && elemSize > 0);
	T ray_struct = malloc(sizeof(struct T));
	ray_struct->width = width;
	ray_struct->height = height;
	ray_struct->elemSize = elemSize;
	ray_struct->in_arr = UArray_new(width*height,elemSize);
	return ray_struct;
}

void UArray2_free(T * ray_struct_p)
{
	assert(ray_struct_p != NULL);
	UArray_free(&(*ray_struct_p)->in_arr);
	free(*ray_struct_p);

}

int UArray2_width(T ray_struct)
{
	assert(ray_struct != NULL);
	return ray_struct->width;
}

int UArray2_height(T ray_struct)
{
	assert(ray_struct != NULL);
	return ray_struct->height;
}

size_t UArray2_elemSize(T ray_struct)
{
	assert(ray_struct != NULL);
	return ray_struct->elemSize;
}

void * UArray2_at(T ray_struct, int col, int row)
{
	assert(ray_struct != NULL);
	int index = (ray_struct->width * row) + col;
	return UArray_at(ray_struct->in_arr,index);
}

void UArray2_map_row_major(T ray_struct, void apply(T ray_struct,void *,
	void *), void *closure)
{
	for (int row = 0 ; row < ray_struct->height ; row++){
		for (int col = 0 ; col < ray_struct->width ; col++){
			apply(ray_struct,UArray2_at(ray_struct,col,row),closure);
		}
	}
}

void UArray2_map_col_major(T ray_struct, void apply(T ray_struct,void *,
	void *), void *closure)
{
	for(int col = 0 ; col < ray_struct->width ; col++){
		for(int row = 0 ; row < ray_struct->height ; row++){
			apply(ray_struct,UArray2_at(ray_struct,col,row),closure);
		}
	}
}


void UArray2_resize(T ray_struct,int new_width,int new_height)
{
	assert(ray_struct != NULL && new_width > 0 && new_height > 0);
	UArray_resize(ray_struct->in_arr,new_height*new_height);
	ray_struct->width = new_width;
	ray_struct->height = new_height;
}

T UArray2_copy(T ray_struct, int new_width, int new_height)
{
	assert(ray_struct != NULL && new_width > 0 && new_height > 0);
	T new_ray_struct = malloc(sizeof(struct T));
	new_ray_struct->width = ray_struct->width;
	new_ray_struct->height = ray_struct->height;
	new_ray_struct->elemSize = ray_struct->elemSize;
	new_ray_struct->in_arr = UArray_copy(ray_struct->in_arr,
		UArray_len(ray_struct->in_arr));
	return new_ray_struct;
}





#undef T


























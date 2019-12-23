#include <stdlib.h>
#include "UArray.h"
#include "assert.h"
#include <string.h>
#include <stdio.h>

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

#undef T

























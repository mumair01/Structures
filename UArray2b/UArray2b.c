#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "math.h"
#include "UArray2b.h"
#include "UArray2.h"
#include "UArray.h"

#include "stdio.h"

#define T UArray2b_T


struct T{
	int width, height, blockSize;
	int blockWidth, blockHeight;
	size_t elemSize;
	UArray2_T blocks;
};



// Helper function to make new array.
void UArray2b_init(T ray_struct,int width, int height, 
	size_t elemSize,int blockSize)
{
	assert(ray_struct);
	assert(width > 0 && height > 0 && elemSize > 0 && blockSize > 0);
	int blockWidth, blockHeight;

	blockWidth = ceil((double)width / (double)blockSize);
	blockHeight = ceil((double)height / (double)blockSize);

	ray_struct->width = width;
	ray_struct->height = height;
	ray_struct->elemSize = elemSize;
	ray_struct->blockSize = blockSize;
	ray_struct->blockWidth = blockWidth;
	ray_struct->blockHeight = blockHeight;
	ray_struct->blocks = UArray2_new(blockWidth,blockHeight,sizeof(void *));
	for(int col = 0 ; col < blockWidth ; col++){
		for(int row = 0 ; row < blockHeight ; row++){
			UArray_T * elem_p = UArray2_at(ray_struct->blocks,col,row);
			UArray_T cells = UArray_new(blockSize * blockSize,elemSize);
			*elem_p = cells;
		}
	}

}


T UArray2b_new(int width,int height, size_t elemSize, int blockSize)
{
	assert(width > 0 && height > 0 && elemSize > 0 && blockSize > 0);
	T ray_struct = malloc(sizeof(struct T));
	if (ray_struct == NULL){
		printf("CRE: Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	UArray2b_init(ray_struct,width,height,elemSize,blockSize);
	return ray_struct;

}

T UArray2b_new_64K(int width, int height, size_t elemSize)
{
	assert(width > 0 && height > 0 && elemSize > 0);
	int blockSize;

	blockSize = ceil(sqrt((64*1024)/elemSize));
	T ray_struct = malloc(sizeof(struct T));

	if(ray_struct == NULL){
		printf("CRE: Memory allocation failed");
		exit(EXIT_FAILURE);
	}
	UArray2b_init(ray_struct,width,height,elemSize,blockSize);
	return ray_struct;

}

int UArray2b_width(T ray_struct)
{
	assert(ray_struct);
	return ray_struct->width;
}

int UArray2b_height(T ray_struct)
{
	assert(ray_struct);
	return ray_struct->height;
}

size_t UArray2b_elemSize(T ray_struct)
{
	assert(ray_struct);
	return ray_struct->elemSize;
}

int UArray2b_blockSize(T ray_struct)
{
	assert(ray_struct);
	return ray_struct->blockSize;
}

// Helper function that calculates the indicies
void calculateIndicies(T ray_struct,int col,int row, int * blockRow,
	int * blockCol, int * cellIndex)
{
	int blockSize;
	blockSize = ray_struct->blockSize;
	*blockCol = col/blockSize;
	*blockRow = row/blockSize;
	*cellIndex = (blockSize * (col % blockSize)) + (row % blockSize);
	assert(*blockCol < ray_struct->blockWidth && *blockRow < 
		ray_struct->height);
	assert(*cellIndex < (blockSize*blockSize));
}

void * UArray2b_at(T ray_struct, int col, int row)
{
	assert(ray_struct);
	assert(col >= 0 && row >= 0);
	assert(col < ray_struct->width && row < ray_struct->height);
	int blockCol, blockRow, cellIndex;
	UArray_T * cells;
	calculateIndicies(ray_struct,col,row,&blockRow,&blockCol,&cellIndex);
	cells =  UArray2_at(ray_struct->blocks,blockCol,blockRow);
	return UArray_at(*cells,cellIndex);
}

void UArray2b_map_col_major(T ray_struct,void apply(T UArray2b, void *, void *),
	void *closure)
{
	assert(ray_struct && apply );
	for(int col = 0 ; col < ray_struct->width ; col++){
		for(int row = 0 ; row < ray_struct->height ; row++){
			apply(ray_struct,UArray2b_at(ray_struct,col,row),closure);
		}
	}
}

void UArray2b_map_row_major(T ray_struct,void apply(T ray_struct, void *, void*),
	void *closure)
{
	assert(ray_struct && apply);
	for(int row = 0 ; row < ray_struct->height ; row++){
		for(int col = 0 ; col < ray_struct->width ; col++){
			apply(ray_struct,UArray2b_at(ray_struct,col,row),closure);
		}
	}
}

// Function that verifies the index of the cell being accessed.
int verifyIndex(T ray_struct, int cell, int blockCol,int blockRow,
	int *cellCol, int *cellRow)
{
	assert(ray_struct);
	assert(cellCol && cellRow);
	assert(cell >= 0 && blockCol >= 0 && blockRow >= 0);



	int inner_col, inner_row;
	int blockSize = ray_struct->blockSize;
	inner_col = cell / blockSize;
	inner_row = cell % blockSize;
	*cellCol = (blockSize * blockCol) + inner_col;
	*cellRow = (blockSize * blockRow) + inner_row;
	if (*cellCol < ray_struct->width && *cellRow < ray_struct->height){
		return 1;
	}
	return 0;


}



void UArray2b_map_block(T ray_struct,void apply(T uarray2b, void *, void*),
	void *closure)
{
	assert(ray_struct && apply);
	int cell_col , cell_row;
	for(int col = 0 ; col < ray_struct->blockWidth ; col++){
		for(int row = 0 ; row < ray_struct->blockHeight ; row++){
			for(int cell = 0 ; cell < ray_struct->blockSize * 
				ray_struct->blockSize ; cell++){
				if (verifyIndex(ray_struct, cell,col,row,&cell_col,
					&cell_row)){
					apply(ray_struct,UArray2b_at(ray_struct, cell_col,
						cell_row),closure);
				}
			}
		}
	}
}



void UArray2b_free(T * ray_struct_p)
{
	assert(ray_struct_p != NULL);
	T ray_struct = *ray_struct_p;
	for(int col = 0 ; col < ray_struct->blockWidth ; col++){
		for(int row = 0 ; row < ray_struct->blockHeight ; row++){
			UArray_T * elem_p = UArray2_at(ray_struct->blocks,col,row);
			UArray_free(elem_p);
		}
	}
	UArray2_free(&ray_struct->blocks);
	free(ray_struct);
}



#undef T





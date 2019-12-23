#include <stdlib.h>
#include <stdio.h>
#include "UArray2b.h"


void store_and_retrieve(UArray2b_T arr, int width, int height);
void print_vals(UArray2b_T arr,void *elem_p,void *closure);


int main(int argc, char *argv[])
{
	(void)argc,(void)argv;
	int width,height,blockSize;
	width = 4, height = 3, blockSize = 2;

	// Initiating a new UArray2b array.
	UArray2b_T arr = UArray2b_new(width,height,sizeof(int),blockSize);

	// Testing the UArray2b_at function.
	store_and_retrieve(arr,width,height);

	// Testing column major mapping
	printf("Testing column major mapping...\n");
	UArray2b_map_col_major(arr,print_vals,NULL);
	printf("\n");

	// Testing row major mapping
	printf("Testing row major mapping...\n");
	UArray2b_map_row_major(arr,print_vals,NULL);
	printf("\n");

	// Testing block major mapping
	printf("Testing block major mapping...\n");
	UArray2b_map_block(arr,print_vals,NULL);
	printf("\n");

	// Freeing the array.
	UArray2b_free(&arr);


	// Initiating a 64K UArray2b array
	UArray2b_T arr_2 = UArray2b_new_64K(width,height,sizeof(int));
	UArray2b_free(&arr_2);

	exit(EXIT_SUCCESS);
}

void store_and_retrieve(UArray2b_T arr, int width, int height)
{
	printf("Running test store and retrieve...\n");
	for(int col = 0 ; col < width ; col++ ){
		for(int row = 0 ; row < height ; row++){
			*(int *)UArray2b_at(arr,col,row) = row;
		}
	}

	for(int col = 0 ; col < width ; col++){
		for(int row = 0 ;row < height ; row++){
			if (*(int *)UArray2b_at(arr,col,row) != row){
				printf("FAILED\n");
				return;
			}
		}
	}
	printf("PASSED\n");
}


void print_vals(UArray2b_T arr,void *elem_p,void *closure)
{
	(void)arr,(void)closure;
	printf("Val: %d\n",*(int *)elem_p);
}













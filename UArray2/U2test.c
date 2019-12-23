#include <stdlib.h>
#include <stdio.h>
#include "UArray2.h"



// Function that stores elements in the array and checks them.
void store_and_retrieve(UArray2_T arr,int width,int height);
// Apply function used to print elements.
void print_val(UArray2_T arr,void * elem_p, void *closure);
// Function that verifies array dimensions
void verifyDimensions(UArray2_T arr, int width, int height, 
	size_t elemSize);
// Function that tests row major mapping.
void checkRowMajorMap(UArray2_T arr);
// Function that tests col major mapping
void checkColMajorMap(UArray2_T arr);
// Function that tests UArray2 resize
void checkResize(UArray2_T arr, int width, int height);
// Function that checks UArray2 copy
void checkCopy(UArray2_T arr,int width, int height);

int main(int argc, char *argv[])
{
	(void)argc,(void)argv;
	int height = 100, width = 5;
	size_t elemSize = sizeof(int);

	// Initalizing the 2d array.
	UArray2_T arr = UArray2_new(width,height,elemSize);

	// Veifying dimensions
	verifyDimensions(arr,width,height,elemSize);

	// Running store and print test.
	store_and_retrieve(arr,width,height);

	// Checking row major mapping
	checkRowMajorMap(arr);

	// Checking col major mapping
	checkColMajorMap(arr);


	// Checking copy
	checkCopy(arr, width, height);

	// Checking UArray2 resize
	checkResize(arr,width,height);


	// Freeing the array.
	UArray2_free(&arr);


	exit(EXIT_SUCCESS);
}


void store_and_retrieve(UArray2_T arr,int width,int height)
{
	printf("Running test store and retrieve...\n");
	for(int col = 0 ; col < width ; col++){
		for(int row = 0 ; row < height ; row++){
			*(int *)UArray2_at(arr,col,row) = row;
		}
	}

	for(int col = 0 ; col < width ; col++){
		for(int row = 0 ;row < height ; row++){
			if (*(int *)UArray2_at(arr,col,row) != row){
				printf("FAILED\n");
				return;
			}
		}
	}
	printf("PASSED\n");
}


void print_val(UArray2_T arr,void * elem_p, void *closure)
{	
	(void)arr,(void)closure;
	printf("Val: %d\n",*(int *)elem_p);
}

// Function that verifies array dimensions
void verifyDimensions(UArray2_T arr, int width, int height, 
	size_t elemSize)
{
	printf("Running verify dimensions...\n");
	if (width != UArray2_width(arr) || height != UArray2_height(arr)
		|| elemSize != UArray2_elemSize(arr)){
		printf("FAILED\n");
		exit(EXIT_FAILURE);
	}
	printf("PASSED\n");
}

// Function that tests row major mapping.
void checkRowMajorMap(UArray2_T arr)
{
	printf("Testing row major mapping...\n");
	UArray2_map_row_major(arr,print_val,NULL);
	printf("Completed!\tVerify\n\n");
}


// Function that tests col major mapping
void checkColMajorMap(UArray2_T arr)
{
	printf("Testing col major mapping...\n");
	UArray2_map_col_major(arr,print_val,NULL);
	printf("Completed!\tVerify\n\n");
}

// Function that tests UArray2 resize
void checkResize(UArray2_T arr, int width, int height)
{
	printf("Checking reisze...\n");
	for(int i = 0 ; i < 100 ; i++ ){
		UArray2_resize(arr,0,0);
		UArray2_resize(arr,width,height);
		UArray2_resize(arr,10,10);
		UArray2_resize(arr,width,height);
	}
	printf("SUCCESS\n\n");
}


// Function that checks UArray2 copy
void checkCopy(UArray2_T arr, int width, int height)
{
	for(int col = 0 ; col < width ; col++){
		for(int row = 0 ; row > height ; row++){
			*(int *) UArray2_at(arr,col,row) = row;
		}
	}
	UArray2_T copy = UArray2_copy(arr,width,height);
	for(int col = 0 ; col < width ; col++){
		for(int row = 0 ; row > height ; row++){
			int data = *(int *) UArray2_at(copy,col,row);
			printf("Copy data: %d\n",data);
		}
	}



	printf("Checking copy...\n");
	for(int col = 0 ; col < width ; col++){
		for(int row = 0 ; row < height ; row++){
			if ( *(int *)UArray2_at(arr,col,row) != 
				*(int *) UArray2_at(copy,col,row)){
				printf("FAILED\n");
				exit(EXIT_FAILURE);
			}
		}
	}
	UArray2_free(&copy);
	printf("SUCCESS\n\n");
}











































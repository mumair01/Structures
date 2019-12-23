#include <stdlib.h>
#include <stdio.h>
#include "UArray.h"
#include <time.h>


void store_and_check(UArray_T my_arr, int len);
void check_resize(UArray_T my_arr, int new_len);
void check_copy(UArray_T my_arr, int new_len);
void checkReverse(UArray_T my_arr);

int compare(void *p1, void *p2);
void sortTest(UArray_T sortArr, int len);
void checkSorted(UArray_T sortArr, int len);





int main(int argc, char *argv[])
{
	(void)argc,(void)argv;


	// Making a new array.
	int len = 6;
	UArray_T my_arr = UArray_new(len,sizeof(int));
	(void) my_arr;

	// Checking at function
	store_and_check(my_arr,len);

	// Checking the resize function
	check_resize(my_arr,len/2);

	// Checking the copy function
	check_copy(my_arr,len);

	// Checking the reverse function
	checkReverse(my_arr);

	// Freeing the UArray
	UArray_free(&my_arr);


	// Testing sorting
	len = 10000;
	UArray_T sortArr = UArray_new(len,sizeof(int));
	sortTest(sortArr,len);

	UArray_free(&sortArr);



	exit(EXIT_SUCCESS);
}

void store_and_check(UArray_T my_arr,int len)
{

	printf("Running store_and_check...\n");
	// Storing.
	for(int i = 0 ; i < len ; i++){
		*(int *)UArray_at(my_arr,i) = i;
	}

	// Checking
	for(int i = 0 ; i < len ; i++){
		if (*(int *)UArray_at(my_arr,i) != i){
			printf("FAILURE\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("SUCCESS\n");
}

void check_resize(UArray_T my_arr, int new_len)
{
	int len = UArray_len(my_arr);
	printf("Running check resize...\n");
	UArray_resize(my_arr,new_len);
	for( int i = len  ; i < new_len ; i++){
		*(int *)UArray_at(my_arr,i) = i;
	}
	for( int i = 0 ; i < new_len ; i++){
		if (*(int *)UArray_at(my_arr,i) != i ){
			printf("FAILURE\n");
			exit(EXIT_FAILURE);
		}
		printf("Resize elem: %d\n",(*(int *)UArray_at(my_arr,i)));
	}
	if (UArray_len(my_arr) != new_len){
		printf("FAILURE\n");
		exit(EXIT_FAILURE);
	}
	printf("SUCCESS\n");
}

void check_copy(UArray_T my_arr, int new_len)
{
	printf("Running check copy...\n");
	int index;
	UArray_T copy = UArray_copy(my_arr,new_len);
	if (UArray_len(my_arr) > new_len)
		index = new_len;
	else 
		index = UArray_len(my_arr);
	for(int i = 0 ; i < index ; i++){
		if ( *(int *) UArray_at(my_arr,i) != *(int *) UArray_at(copy,i)){
			printf("FAILURE\n");
			exit(EXIT_FAILURE);
		}
	}
	UArray_free(&copy);
	printf("SUCCESS\n");
}

void checkReverse(UArray_T my_arr)
{
	printf("Running check reverse...\n");
	int len = UArray_len(my_arr);

	UArray_T copy = UArray_copy(my_arr,len);

	UArray_reverse(my_arr);


	for(int i = 0 ; i < len ; i++){
		if(* (int *) UArray_at(my_arr,i) != *(int *) UArray_at(copy,len-1-i)){
			printf("FAILED\n");
			exit(EXIT_FAILURE);
		}
	}

	UArray_free(&copy);
	printf("SUCCESS\n");
}


int compare(void *p1, void *p2)
{
	if (*(int *) p1 > *(int *)p2)
		return 1;
	else if (*(int *) p1 < *(int *)p2)
		return 0;
	else
		return -1;
}

void checkSorted(UArray_T sortArr, int len)
{
	for(int i = 0 ; i < len -1 ; i++){
		if (compare(UArray_at(sortArr,i), UArray_at(sortArr,i+1)) > 0){
			printf("FAILURE\n");
			exit(EXIT_FAILURE);
		}
	}
	printf("SUCCESS\n");
}


void sortTest(UArray_T sortArr,int len)
{
	for(int i = 0 ; i < 1 ; i++){
		clock_t t;
		printf("\nRunning sorting test...\n");

		srand(time(NULL));
		for (int i = 0 ; i < len ; i++)
			*(int *)UArray_at(sortArr,i) = rand() % 10000 + 1; 

		printf("Testing bubble sort...\n");
		t = clock();
		UArray_bubble_sort(sortArr,compare);
		t = clock() - t;
		checkSorted(sortArr,len);
		printf("Bubble sort time: %f seconds\n",((double)t)/CLOCKS_PER_SEC);
		printf("\n");


		srand(time(NULL));
		for (int i = 0 ; i < len ; i++)
			*(int *)UArray_at(sortArr,i) = rand() % 10000 + 1; 


		printf("Testing selection sort...\n");
		t = clock();
		UArray_selection_sort(sortArr,compare);
		t = clock() - t;
		checkSorted(sortArr,len);
		printf("Selection sort time: %f seconds\n",((double)t)/CLOCKS_PER_SEC);
		printf("\n");


		srand(time(NULL));
		for (int i = 0 ; i < len ; i++)
			*(int *)UArray_at(sortArr,i) = rand() % 10000 + 1; 

		printf("Testing insertion sort...\n");
		t = clock();
		UArray_insertion_sort(sortArr,compare);
		t = clock() - t;
		checkSorted(sortArr,len);
		printf("Insertion sort time: %f seconds\n",((double)t)/CLOCKS_PER_SEC);
		printf("\n");

		srand(time(NULL));
		for (int i = 0 ; i < len ; i++)
			*(int *)UArray_at(sortArr,i) = rand() % 10000 + 1; 


		printf("Testing merge sort...\n");
		t = clock();
		UArray_merge_sort(sortArr,compare);
		t = clock() - t;
		checkSorted(sortArr,len);
		printf("Merge sort time: %f seconds\n",((double)t)/CLOCKS_PER_SEC);
		printf("\n");

		srand(time(NULL));
		for (int i = 0 ; i < len ; i++)
			*(int *)UArray_at(sortArr,i) = rand() % 10000 + 1; 

		printf("Testing quick sort lumoto scheme...\n");
		t = clock();
		UArray_quick_sort_lumoto(sortArr,compare);
		t = clock() - t;
		checkSorted(sortArr,len);
		printf("Quicksort time: %f seconds\n",((double)t)/CLOCKS_PER_SEC);
		printf("\n");

		srand(time(NULL));
		for (int i = 0 ; i < len ; i++)
			*(int *)UArray_at(sortArr,i) = rand() % 10000 + 1; 


		printf("Testing quick sort hoare scheme...\n");
		t = clock();
		UArray_quick_sort_hoare(sortArr,compare);
		t = clock() - t;
		checkSorted(sortArr,len);
		printf("Quicksort time: %f seconds\n",((double)t)/CLOCKS_PER_SEC);
		printf("\n");

		srand(time(NULL));
		for (int i = 0 ; i < len ; i++)
			*(int *)UArray_at(sortArr,i) = rand() % 10000 + 1;

		printf("Testing heap sort...\n");
		t = clock();
		UArray_heap_sort(sortArr,compare);
		t = clock() - t;
		checkSorted(sortArr,len);
		printf("Heap sort time: %f seconds\n",((double)t)/CLOCKS_PER_SEC);
		printf("\n");

	}

}

































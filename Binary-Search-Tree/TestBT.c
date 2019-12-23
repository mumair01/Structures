#include <stdio.h>
#include <stdlib.h>
#include "binaryTree.h"



// Comparison function for data in the bst
int compare(void *p1,void *p2);
// Apply function for traversal
void print_val(bst_T bst, void *elem_p, void *closure);

int main(int argc, char *argv[])
{
	(void)argc,(void)argv;

	// Instantiating a new bst instance
	bst_T bst = bst_new();
	(void)bst;

	// Inserting some nodes into the bst
	for(int i = 0 ; i <  10 ; i++){
		bst_insert(bst,&i,sizeof(int),compare);
	}

	// Testing in order traversal.
	printf("Testing in order traversal\n");
	bst_in_order(bst,print_val,NULL);
	printf("\n");

	// Testing pre order traversal.
	printf("Testing pre order traversal\n");
	bst_pre_order(bst,print_val,NULL);
	printf("\n");

	// Testing in order traversal.
	printf("Testing post order traversal\n");
	bst_post_order(bst,print_val,NULL);
	printf("\n");

	// Testing breadth first search
	printf("Testing breadth first search\n");
	int val = 9;
	int *data = bst_breadth_first_search(bst,&val,compare);
	if (data)
		printf("Search data value: %d\n",*data);
	else
		printf("Not found\n");
	printf("\n");


	// Testing depth first search
	printf("Testing depth first search...\n");
	int val2 = 5;
	int *data2 = bst_depth_first_search(bst,&val2,compare);
	if(data2)
		printf("Search data value: %d\n",*data2);
	else
		printf("Not found");
	printf("\n");


	// Testing binary search
	printf("Testing binary search...\n");
	int val3 = 5;
	int *data3 = bst_binary_search(bst,&val3,compare);
	if (data3)
		printf("Search data value: %d\n",*data3);
	else
		printf("Not found\n");
	printf("\n");


	// Deleting some nodes
	printf("\nDeleting values...\n");
	for(int i = 0 ; i < 10 ; i+=2)
		bst_delete(bst,&i,compare);
	printf("Testing in order traversal\n");
	bst_in_order(bst,print_val,NULL);
	printf("\n");


	// Copying the tree
	printf("Copying the tree...\n");
	bst_T copy = bst_copy(bst,sizeof(int),compare);
	printf("Testing in order traversal for copied tree\n");
	bst_in_order(copy,print_val,NULL);
	printf("\n");

	printf("\nDeleting values...\n");
	for(int i = 1 ; i < 10 ; i+=2)
		bst_delete(bst,&i,compare);
	printf("Testing in order traversal\n");
	bst_in_order(bst,print_val,NULL);
	printf("\n");

	// Freeing the bst.
	bst_free(&bst);
	bst_free(&copy);

	exit(EXIT_SUCCESS);
}


// Comparison function for data in the bst
int compare(void *p1,void *p2)
{
	if(*(int *)p1 > *(int *)p2)
		return 1;
	else if (*(int *)p1 < *(int *)p2)
		return 0;
	else return -1;
}


// Apply function for traversal
void print_val(bst_T bst, void *elem_p, void *closure)
{
	(void)bst,(void)closure;
	printf("Elem: %d\n",*(int*)elem_p);
}

















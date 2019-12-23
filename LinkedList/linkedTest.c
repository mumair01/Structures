#include <stdlib.h>
#include <stdio.h>
#include "linkedList.h"


// Prints an individual element in the list.
void printList(void ** x, void *closure);


int main(int argc, char *argv[])
{
	(void)argc,(void)argv;
	
	int data = 10,data2 = 20, data3 = 30;
	(void)data3;

	// Initializing the list.
	list_T list = list_push(NULL,&data);

	// Appending to the list
	list_append(list,list_push(NULL,&data2));

	// Mapping
	printf("\nPrinting...\n");
	list_map(list,printList,NULL);
	printf("List length: %d\n",list_length(list));

	// Copying the list
	list_T copy = list_copy(list);
	printf("\nPrinting copied...\n");
	list_map(copy,printList,NULL);
	printf("Copied list length: %d\n",list_length(list));

	// Reversing the list
	copy = list_reverse(copy);
	printf("\nPrinting reversed...\n");
	list_map(copy,printList,NULL);
	printf("Copied list length: %d\n",list_length(list));

	// Popping an element from the list
	list = list_pop(list,NULL);

	// Mapping
	printf("\nPrinting...\n");
	list_map(list,printList,NULL);
	printf("List length: %d\n",list_length(list));

	// Freeing the list
	list_free(&list);
	list_free(&copy);


	exit(EXIT_SUCCESS);
}




void printList(void ** x, void *closure)
{
	(void)closure;
	if (*(int **)x)
		printf("Element %d\n",*(int *)(*(int **)x));
}

































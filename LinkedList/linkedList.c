#include <stdlib.h>
#include "assert.h"
#include "linkedList.h"
#include <stdio.h>

#define T list_T


struct T{
	void *data;					// Ptr to an element in the list.
	T rest;						// Rest of the list.
};

// Adds a new element to the start of the list.
// Accepts NULL as the list argument
// data is the pointer to the elelemt to add to the list.
T list_push(T list, void *data)
{
	assert(data);
	T list_struct = malloc(sizeof(struct T));
	if (list_struct == NULL){
		printf("CRE: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	list_struct->data = data;
	list_struct->rest = list;
	return list_struct;
}


// Frees a list instance
// Must pass in a valid list.
void list_free(T *list_p)
{
	assert(list_p);
	T nxt;
	for( ; *list_p ; *list_p = nxt){
		nxt = (*list_p)->rest;
		free(*list_p);
	}
}


// Function that adds a list to the end of the given list.
// Both arguments can be NULL.
// Both cannot be the same list
T list_append(T list, T newList)
{
	assert(list != newList);
	T *p = &list;
	while(*p){
		p = &(*p)->rest;
	}
	*p = newList;
	return list;
}

// Mapping function for the list.
void list_map(T list,void apply(void ** x, void *closure), void * closure)
{
	assert(apply && list);
	for( ; list ; list = list->rest)
		apply(&list->data,closure);
}

// Removes the first node in a non-empty list and removes it from the list.
// If the input list is empty, the function returns an empty list.
// If x in no-NULL, *x is given the data pointer of the node being popped.
T list_pop(T list,void ** data_p)
{
	if(list){
		T head = list->rest;
		if (data_p)
			*data_p = list->data;
		free(list);
		return head;
	}
	else
		return list;

}

// Returns the number of elements in the list
int list_length(T list)
{
	assert(list);
	int len = 0;
	for( ; list ; list = list->rest)
		len++;
	return len;
}

// Copies the given list and returns a new list.
T list_copy(T list)
{
	assert(list);
	T newList;
	T * curr = &newList;
	for( ; list ; list = list->rest){
		*curr = malloc(sizeof(struct T));
		(*curr)->data = list->data;
		curr = &(*curr)->rest; 
	}
	*curr = NULL;
	return newList;
}

// Function that reverses the all the elements in the list
T list_reverse(T list)
{
	assert(list);
	T head = NULL, next;
	for( ; list ; list = next){
		next = list->rest;
		list->rest = head;
		head = list;
	}
	return head;
}



#undef T


































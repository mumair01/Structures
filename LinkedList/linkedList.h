/*
	Implementation of a generic list that is a collection of one or more pointer.

	Made by: Muhammad Umair
	Date: 7/29/19
*/


#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#define T list_T
typedef struct T * T;


// Creates and returns a new list instance
// Accepts NULL as the list argument
// data is the pointer to the elelemt to add to the list.
// Appends data to the start of the list.
T list_push(T list, void *data);

// Function that adds a list to the end of the given list.
// Both arguments can be NULL.
// Both cannot be the same list
T list_append(T list, T newList);

// Mapping function for the list.
// x is a pointer to the element stored in the list, which is a void *.
void list_map(T list,void apply(void ** x, void *closure), void * closure);

// Removes the first node in a non-empty list and removes it from the list.
// If the input list is empty, the function returns an empty list.
// If x in no-NULL, *x is given the data pointer of the node being popped.
T list_pop(T list,void ** data_p);

// Returns the number of elements in the list.
int list_length(T list);

// Copies the given list and returns a new list
T list_copy(T list);

// Function that reverses the all the elements in the list
T list_reverse(T list);

// Frees a list instance
void list_free(T *list);




#undef T
#endif

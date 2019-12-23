/*
	Implementation of a generic binary tree in c. 
	Stores the data element i.e. unboxed.
*/


#ifndef BINARYTREE_H_
#define BINARYTREE_H_

#define T bst_T
typedef struct T* T;


// Instantiate a new BST
T bst_new();

// Free an instance of the BST
void bst_free(T *bst_p);

// Initialize a new instance of a BST
// If compare > 0, then the data pointed to by p1 is greater 
// than the data pointed to by p2. Returns -1 if equal
void bst_insert(T bst, void *data, size_t elemSize,
	int compare(void *p1,void *p2));

// Implementation of breadth first search on the bst
// Returns the pointer to the data in the bst
void * bst_breadth_first_search(T bst, void *data,
	int compare(void *p1,void *p2));

// Implementation of depth first search on the bst
void * bst_depth_first_search(T bst, void *data,
	int compare(void *p1,void *p2));

// Implementation of a binary search on the bst
void *bst_binary_search(T bst, void *data, 
	int compare(void *p1, void *p2));

// Function that deletes a specific element from the tree if found
void bst_delete(T bst, void *deleteItem, int compare(void *p1,void *p2));

// Copy the binary tree and return the copy
T bst_copy(T bst,size_t elemSize,int compare(void *p1,void *p2));

// In-order traversal function for bst.
void bst_in_order(T bst, void apply(T bst, void *, void* ),
	void *closure);

// Pre-order traversal function for bst.
void bst_pre_order(T bst, void apply(T bst, void *, void* ),
	void *closure);

// Post-order traversal function for bst.
void bst_post_order(T bst, void apply(T bst, void *, void* ),
	void *closure);



#undef T
#endif

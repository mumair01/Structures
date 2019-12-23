#include <stdlib.h>
#include <stdio.h>
#include "assert.h"
#include "string.h"
#include "binaryTree.h"
#include "queue.h"
#include "stack.h"

#define T bst_T

struct T{
	struct node *root; 			// Points to the start of the bst.
};

struct node{
	void *data;					// Data pointer stored.
	struct node* left;			// Ptr to the left node.
	struct node* right;			// Ptr to the right node.
	int count;					// Number of instances for this node	
};


// Function that initializes a new instances of the bstNode
void init_bstNode(struct node * bstNode, void *data, size_t elemSize)
{

	assert(data);
	assert(elemSize > 0);

	bstNode->data = malloc(elemSize);

	if (! bstNode || ! bstNode->data){
		printf("CRE: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}

	// Making deep copy of pointer data content
	memcpy(bstNode->data,data,elemSize);

	bstNode->left = bstNode->right = NULL;
	bstNode->count = 0;
}

// Instantiate a new BST
T bst_new()
{

	T bst = malloc(sizeof(struct T));
	if (! bst){
		printf("CRE: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	bst->root = NULL;
	return bst;

}

// Helper function to free one node
void freeNodes(struct node ** node_p)
{
	if(*node_p){
		free((*node_p)->data);
		freeNodes(&(*node_p)->left);
		freeNodes(&(*node_p)->right);
		free(*node_p);
	}
}

// Free an instance of the BST
void bst_free(T *bst_p)
{
	assert(bst_p && *bst_p);
	freeNodes(&(*bst_p)->root);
	free(*bst_p);
}

// Helper function for inserting
void insertNode(struct node **rootNode_p, void *data, size_t elemSize,
	int compare(void *,void *))
{
	assert(rootNode_p);
	assert(data);
	assert(compare);
	assert(elemSize > 0);

	// No BST exists in this case.
	if (*rootNode_p == NULL){
		// Allocating memory for node.
		*rootNode_p = malloc(sizeof(struct node));

		init_bstNode(*rootNode_p,data,elemSize);
	}
	// Data is greater than the current node value.
	// Insert on the right side in this case.
	else if (compare(data,(*rootNode_p)->data) > 0){
		insertNode(&(*rootNode_p)->right,data,elemSize,compare);
	}
	// Data is less than the curret node value.
	// Insert on the left hand side in this case.
	else if (compare(data,(*rootNode_p)->data) == 0){
		insertNode(&(*rootNode_p)->left,data,elemSize,compare);
	}
	// Data is equal in this case
	else{
		(*rootNode_p)->count++;
	}
}


// Insert a new element into the BST
// If compare > 0, then the data pointed to by p1 is greater 
// than the data pointed to by p2. Returns -1 if equal
void bst_insert(T bst, void *data, size_t elemSize,
	int compare(void *,void *))
{
	assert(bst);
	insertNode(&bst->root,data,elemSize,compare);
}

// Helper function for the breadth first search
void * breadth_first_search(Queue_T searchQueue,
	void *data, int compare(void *p1,void *p2))
{

	assert(searchQueue);
	// Make sure queue is not empty / rootNode enqueued.
	assert(queue_isEmpty(searchQueue) == 0);
	assert(data && compare);

	struct node * rootNode;


	while(queue_isEmpty(searchQueue) == 0){
		rootNode = queue_dequeue(searchQueue);
		// The rootNode data and current data are equal.
		if (compare(rootNode->data,data) == -1)
			return rootNode->data;
		else{
			if (rootNode->left)
				queue_enqueue(searchQueue,rootNode->left);
			if (rootNode->right)
				queue_enqueue(searchQueue,rootNode->right);
		}
	}
	// Data not found in this case
	return NULL;

}


// Implementation of breadth first search on the bst
// Returns the pointer to the data in the bst
// Returns NULL if data element not found
void * bst_breadth_first_search(T bst, void *data,
	int compare(void *p1,void *p2))
{
	assert(bst);
	assert(data);
	assert(compare);
	void *foundData;

	if (! bst->root)
		return NULL;

	// Setting up the queue for the search
	Queue_T searchQueue = queue_new();
	queue_enqueue(searchQueue,bst->root);
	foundData = breadth_first_search(searchQueue,data,compare);
	queue_free(&searchQueue);
	return foundData;

}



// Helper function for the depth first search
void * depth_first_search(stack_T searchStack, 
	void *data, int compare(void *p1, void *p2))
{

	assert(searchStack);
	assert(data && compare);
	assert(stack_empty(searchStack) == 0);

	struct node *rootNode;
	while(stack_empty(searchStack) == 0){

		rootNode = stack_pop(searchStack);
		if (compare(rootNode->data,data)==-1)
			return rootNode->data;
		else{
			if (rootNode->left)
				stack_push(searchStack,rootNode->left);
			if (rootNode->right)
				stack_push(searchStack,rootNode->right);
		}
	}
	return NULL;
}



// Implementation of depth first search on the bst
void *bst_depth_first_search(T bst, void *data,
	int compare(void *p1,void *p2))
{
	assert(bst);
	assert(data);
	assert(compare);

	void *foundData;

	if (!bst->root)
		return NULL;

	// Setting up a stack for the search.
	stack_T searchStack = stack_new();
	stack_push(searchStack,bst->root);
	foundData = depth_first_search(searchStack,data,compare);
	stack_free(&searchStack);
	return foundData;
}


// Helper function for the binary search
// Returns NULL in case data is not found.
void * binary_search(struct node *rootNode, void *data, 
	int compare(void *p1, void *p2))
{
	assert(rootNode && compare);
	assert(data);

	// Data is equal
	if (compare(rootNode->data,data) == -1)
		return rootNode->data;
	else{
		// The data in the  node is greater than the data to be found.
		// Move to the left in this case.
		if (compare(rootNode->data,data) > 0 && rootNode->left)
			return binary_search(rootNode->left,data,compare);
		// The data in the node is less than the data to be found.
		// Move to the right in this case
		else if (compare(rootNode->data,data) == 0 && rootNode->right)
			return binary_search(rootNode->right,data,compare);
	}
	return NULL;


}



// Implementation of a binary search on the bst
void *bst_binary_search(T bst, void *data, 
	int compare(void *p1, void *p2))
{
	assert(bst);
	assert(data);
	assert(compare);

	if (! bst->root)
		return NULL;

	return binary_search(bst->root,data,compare);


}


// Helpfer function for deleting a node from the tree
// Returns the node that is deleted
void * deleteNode(struct node **rootNode_p,void *deleteItem,
	int compare(void *p1,void *p2))
{
	assert(deleteItem && compare);

	// No elements to search in this case
	if ( ! *rootNode_p )
		return NULL;

	// If the node value is greater than the deleteItem
	// Delete item has to be on left
	if(compare((*rootNode_p)->data,deleteItem) > 0)
		(*rootNode_p)->left = deleteNode(&(*rootNode_p)->left,deleteItem,compare);
	// If the node value is less than the deleteItem
	// Delete item will be on the right
	else if(compare((*rootNode_p)->data,deleteItem) == 0 )
		(*rootNode_p)->right = deleteNode(&(*rootNode_p)->right,deleteItem,compare);
	// The node is found
	else{
		// Node with only one or no child
		if ((*rootNode_p)->left == NULL){
			struct node *temp = (*rootNode_p)->right;
			(*rootNode_p)->left = (*rootNode_p)->right = NULL;
			freeNodes(rootNode_p);
			return temp;
		}
		else if ((*rootNode_p)->right == NULL){
			struct node *temp = (*rootNode_p)->left;
			(*rootNode_p)->left = (*rootNode_p)->right = NULL;
			freeNodes(rootNode_p);
			return temp;
		}

		// Getting the smallest node in the right sub-tree
		struct node *temp = (*rootNode_p)->right;
		while(! temp->left)
			temp = temp->left;
		(*rootNode_p)->data = temp->data;

		// Delete the right inorder successor
		deleteNode(&(*rootNode_p)->right,temp->data,compare);
	}
	return *rootNode_p;
}


// Struct to help copy tree
struct copy{
	T new_bst;
	size_t size;
	int (*func)(void *,void*);
};


// Helper function to copy the bst.
void copy(T bst, void *data, void *closure)
{
	assert(bst);
	assert(closure);
	struct copy *cl = closure;

	bst_insert(cl->new_bst,data,cl->size,cl->func);
}	


// Copy the binary tree and return the copy
T bst_copy(T bst,size_t elemSize,int compare(void *p1,void *p2))
{
	assert(bst);

	T new_bst = malloc(sizeof(struct T));
	if (! new_bst){
		printf("CRE: Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	new_bst->root = NULL;

	struct copy *cl = malloc(sizeof(struct copy));
	cl->new_bst = new_bst;
	cl->size = elemSize;
	cl->func = compare;

	bst_in_order(bst, copy, cl);
	free(cl);

	return new_bst;
	

}


// Function that deletes a specific element from the tree if found
// Returns the deleted item.
// Returns NULL if the item is not found
void bst_delete(T bst, void *deleteItem, int compare(void *p1,void *p2))
{
	assert(bst);
	assert(deleteItem);
	assert(compare);
	bst->root = deleteNode(&bst->root,deleteItem,compare);
}


// Helper function for the in order traversal
// Left, print, right.
void in_order(T bst,struct node * rootNode, void apply(T bst, void *, void* ),
	void *closure)
{
	assert(apply);
	if (rootNode){
		in_order(bst,rootNode->left, apply,closure);
		apply(bst,rootNode->data,closure);
		in_order(bst,rootNode->right,apply,closure);
	}
}

// In-order traversal function for bst.
void bst_in_order(T bst, void apply(T bst, void *, void* ),
	void *closure)
{
	assert(bst && apply);
	in_order(bst,bst->root,apply,closure);
}

// Helper function for pre-order traversal
// Print, Left, Right
void pre_order(T bst,struct node * rootNode, void apply(T bst, void *, void* ),
	void *closure)
{
	assert(apply);
	if (rootNode){
		apply(bst,rootNode->data,closure);
		pre_order(bst,rootNode->left, apply,closure);
		pre_order(bst,rootNode->right,apply,closure);
	}
}

// Pre-order traversal function for bst.
void bst_pre_order(T bst, void apply(T bst, void *, void* ),
	void *closure)
{
	assert(bst && apply);
	pre_order(bst,bst->root,apply,closure);
}

// Helper function for pre-order traversal
// Print, Left, Right
void post_order(T bst,struct node * rootNode, void apply(T bst, void *, void* ),
	void *closure)
{
	assert(apply);
	if (rootNode){
		post_order(bst,rootNode->left, apply,closure);
		post_order(bst,rootNode->right,apply,closure);
		apply(bst,rootNode->data,closure);
	}
}

// Pre-order traversal function for bst.
void bst_post_order(T bst, void apply(T bst, void *, void* ),
	void *closure)
{
	assert(bst && apply);
	post_order(bst,bst->root,apply,closure);
}

#undef T

































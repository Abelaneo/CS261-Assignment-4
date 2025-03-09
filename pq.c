/*
 * In this file, you will write the structures and functions needed to
 * implement a priority queue.  Feel free to implement any helper functions
 * you need in this file to implement a priority queue.  Make sure to add your
 * name and @oregonstate.edu email address below:
 *
 * Name: Oscar Abelanet
 * Email: abelaneo@oregonstate.edu
 */

#include <stdlib.h>

#include "pq.h"
#include "dynarray.h"
#include <math.h>

/*
 * This is the structure that represents a priority queue.  You must define
 * this struct to contain the data needed to implement a priority queue.
 * 
 * A dynamic array that will store priority_nodes, a struct that itself stores 
 * data as a void* then a priority 
 */
struct pq {
	struct dynarray* array;
};

struct priority_node {
	int priority;
	void* value;
};

/*
 * This function should allocate and initialize an empty priority queue and
 * return a pointer to it.
 */
struct pq* pq_create() {
	struct pq* PQ = malloc(sizeof(struct pq));
	PQ->array = dynarray_create();
	return PQ;
}

/*
 * This function should free the memory allocated to a given priority queue.
 * Note that this function SHOULD NOT free the individual elements stored in
 * the priority queue.  That is the responsibility of the caller.
 *
 * Params:
 *   pq - the priority queue to be destroyed.  May not be NULL.
 */
void pq_free(struct pq* pq) {
	dynarray_free(pq->array);
	free(pq);
	return;
}

/*
 * This function should return 1 if the specified priority queue is empty and
 * 0 otherwise.
 *
 * Params:
 *   pq - the priority queue whose emptiness is to be checked.  May not be
 *     NULL.
 *
 * Return:
 *   Should return 1 if pq is empty and 0 otherwise.
 */
int pq_isempty(struct pq* pq) {
	if (dynarray_size(pq->array) == 0) {
		return 1;
	}
	return 0
}

/*
 * This function should insert a given element into a priority queue with a
 * specified priority value.  Note that in this implementation, LOWER priority
 * values are assigned to elements with HIGHER priority.  In other words, the
 * element in the priority queue with the LOWEST priority value should be the
 * FIRST one returned.
 *
 * Params:
 *   pq - the priority queue into which to insert an element.  May not be
 *     NULL.
 *   value - the value to be inserted into pq.
 *   priority - the priority value to be assigned to the newly-inserted
 *     element.  Note that in this implementation, LOWER priority values
 *     should correspond to elements with HIGHER priority.  In other words,
 *     the element in the priority queue with the LOWEST priority value should
 *     be the FIRST one returned.
 */
void pq_insert(struct pq* pq, void* value, int priority) {
	struct priority_node* new_node = malloc(sizeof(struct priority_node));
	new_node->priority = priority;
	new_node->value = value;

	dynarray_insert(pq->array, new_node);
	int new_pos = dynarray_size(pq->array) - 1;
	
	if (new_pos == 0) {
		return;
	}

	int parent_pos = floor((new_pos - 1) / 2);
	// While the new nodes priority is less than it's parents priority,
	// and the node is not the root, swap them
	while (pq->array->data[new_pos]->priority < pq->array->data[parent_pos]->priority &&
	       new_pos != 0) {
		
		dynarray_switch(pq->array, new_pos, parent_pos));
		new_pos = floor((new_pos - 1) / 2);
		parent_pos = floor((new_pos - 1) / 2);
	}
	return;
}

/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_first(struct pq* pq) {
	return pq->array->data[0]->value;
}


/*
 * This function should return the priority value of the first item in a
 * priority queue, i.e. the item with LOWEST priority value.
 *
 * Params:
 *   pq - the priority queue from which to fetch a priority value.  May not be
 *     NULL or empty.
 *
 * Return:
 *   Should return the priority value of the first item in pq, i.e. the item
 *   with LOWEST priority value.
 */
int pq_first_priority(struct pq* pq) {
	return pq->array->data[0]->priority;
}


/*
 * This function should return the value of the first item in a priority
 * queue, i.e. the item with LOWEST priority value, and then remove that item
 * from the queue.
 *
 * Params:
 *   pq - the priority queue from which to remove a value.  May not be NULL or
 *     empty.
 *
 * Return:
 *   Should return the value of the first item in pq, i.e. the item with
 *   LOWEST priority value.
 */
void* pq_remove_first(struct pq* pq) {
	void* temp = pq_first(pq);
	dynarray_remove(pq->array, 0);
	return temp;
}

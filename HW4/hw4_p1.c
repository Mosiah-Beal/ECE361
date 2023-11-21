/**
 * hw4_p1.c - Linked list-based Stack ADT source code
 *
 * Author: Mosiah Beal (mosiah@pdx.edu)
 * Date:   Nov. 10, 2023
 *
 * This is the stack ADT that you are implementing for the assignment.
 * Your stack ADT should implement the API which is defined in "stackADT_LL.h"
 * and should use the API defined and implemented in Roy's Linked List ADT (included
 * in starters/SLLLinked List.
 *
 * @note (Hint) The Linked List ADT should do most of the "heavy lifting"
 *  This ADT should make use of the SLLLinkedList API as the "stack"
 * 
 * @note (Observation) This ADT pushes and pops long int data to and from the stack, 
 * and doesn't support double (fractional) values, demoting data passed in.
 */
 
// include files
#include <stdio.h>
#include <stdlib.h>
#include "stackADT_LL.h"

/**
 * Creates a new instance of the stack
 *
 * @returns	a pointer to the new stack instance
 *
 * Making the stack instance includes making a new
 * instance of the Linked List
 */
struct Stack *createStack() {
    struct Stack *newStack = malloc(sizeof(struct Stack));
    newStack->top = createLList(); // create a new linked list
    return newStack;
}

/**
 * Pushes a new long onto the stack
 *
 * @returns	void
 *
 * Makes use of the insertNodeInLList() function.  In a stack
 * all new entries are added at the front of the linked list (pos = 1)
 */
void push(struct Stack *stk, long data){
    insertNodeInLList(stk->top, data, 1);   // insert at the front of the list
}

/**
 * Returns the number of items on the stack
 *
 * @returns	an int containing the number of items on the stack
 *
 * Makes use of the LListLength() function which returns the
 * number of nodes in the linked list
 */
int size(struct Stack *stk){
    return LListLength(stk->top);   // return the number of nodes in the linked list
}


/**
 * Returns true if the stack is empty
 *
 * @returns	true if the stack is empty, false otherwise
 *
 * Makes use of the LListLength() function which returns the
 * number of nodes in the linked list.  An empty stack is an empty
 * linked list so the number of nodes on the linked list is 0
 */
bool isEmpty(struct Stack *stk) {
    return LListLength(stk->top) == 0;  // return true if the number of nodes in the linked list is 0
}


/**
 * Pops the top entry from the stack
 *
 * @returns	a long containing the data from the top of the stack
 *
 * Makes use of the getNodeDataInLList() function.  In a stack
 * entries are returned from the front of the linked list (pos = 1) and
 * then then deleted by using the deleteNodeFromLLinkedList() function in the
 * Linked List ADT
 */
long pop(struct Stack *stk){ 
    long data = getNodeDataInLList(stk->top, 1); // get the data from the front of the list
    deleteNodeFromLLinkedList(stk->top, 1);  // delete the node from the front of the list
    return data;    // return the data from the front of the list
}


/**
 * returns the top entry on the stack
 *
 * @returns	a long containing the data from the top of the stack
 *
 * Makes use of the getNodeDataInLList() function.  In a stack
 * entries are returned from the front of the linked list (pos = 1).  Like pop()
 * except the entry is not removed from the linked list
 */
long peek(struct Stack * stk){
    return getNodeDataInLList(stk->top, 1); // return the data from the front of the list
}


/**
 * deletes all of the entries on the stack and the stack instance
 *
 * @returns	void
 *
 * Makes use of the deleteLList() function from the Linked List ADT
 * to remove the linked list and then frees the stack instance, itself
 */
void deleteStack(struct Stack *stk){
    deleteLList(stk->top);  // delete the linked list
    free(stk);  // free the stack instance
 }
 

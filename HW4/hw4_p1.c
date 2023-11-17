/**
 * stackADT_LL.c - Starter code for your linked list-based Stack ADT
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
struct Stack *createStack(){
    struct Stack newStack;
    newStack.top = createLList();//createLList() returns a pointer to
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
    //TODO:  Implement the functionality
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
    //TODO:  Implement the functionality
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
    //TODO:  Implement the functionality
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
    //TODO:  Implement the functionality
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
    //TODO:  Implement the functionality
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
    //TODO:  Implement the functionality
 }
 

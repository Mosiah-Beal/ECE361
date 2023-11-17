/**
 * stackADT_LL.h - Header file for linked list-based stack
 *
 * Author: Mosiah Beal (mosiah@pdx.edu)
 * Date: Nov. 10, 2023
 *
 * This is the header file for the stack ADT that you are going to write
 *
 */

#ifndef _STACKADT_LL_H
#define _STACKADT_LL_H

#include <limits.h> 
#include <stdbool.h> 

// The header file for Roy's Linked List ADT
// Your stack implementation shoud use the API for 
// Roy's Linked List ADT
#include "LinkedList.h"

// private typedefs and structs
struct Stack{
    LinkedListPtr_t top;
};


// API function prototypes
struct Stack *createStack();
void push(struct Stack *stk, long data);
int size(struct Stack *stk);
bool isEmpty(struct Stack *stk);
long pop(struct Stack *stk);
long peek(struct Stack * stk);
void deleteStack(struct Stack *stk);

#endif

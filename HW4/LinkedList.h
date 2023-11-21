/**
 * LinkedList.h - Linked List ADT header file
 *
 * @author Roy Kravitz (roy.kravitz@pdx.edu)
 * @date   07-Nov-2022
 * 
 * This is the header file for a Linked list ADT that
 * implements a pointer-based singly linked list
 *
 * @note Code is based on SinglyLinkedList.c from Narasimha Karumanchi
 * Data Structures and Algorithms Made Easy, Career Monk Publishers, 2016
 *
 * @note The data in this implementation is a single long int.  To change
 * the data type change the struct listNode.
 */

#ifndef _LINKEDLIST_H_
#define _LINKEDLIST_H_

// include required header files
#include <stddef.h>
#include <limits.h> 
#include <malloc.h>

// define the struct that contains a node in the linked list
typedef struct listNode {
	double data;	// data for the node // changed to long double
	struct listNode *next;	// next pointer for the node
} ListNode_t, *ListNodePtr_t;

// define the struct that contains an instance of the Linked List
typedef struct LinkedList {
	ListNodePtr_t head;		// pointer to the head node of the list
	int count;				// number of elements on the list
} LinkedList_t, *LinkedListPtr_t;


// function prototypes
LinkedListPtr_t createLList(void);
int LListLength(LinkedListPtr_t L);
void insertNodeInLList(LinkedListPtr_t L, double data, int pos);
long getNodeDataInLList(LinkedListPtr_t L, int pos);
void deleteNodeFromLLinkedList(LinkedListPtr_t L, int pos);
void printLList(LinkedListPtr_t L);
void deleteLList(LinkedListPtr_t L);
  
#endif
/*
 * LinkedList.c - Linked List ADT
 *
 * @author Roy Kravitz (roy.kravitz@pdx.edu)
 * @date   07-Nov-2022
 * 
 * This is the source code file for a Linked List ADT that
 * implements a singly linked list.  I've tried to define the
 * API in a way that we can change implementations but keep
 * the API the same
 *
 * @note Code is based on DynamicStack.c from Narasimha Karumanchi
 * Data Structures and Algorithms Made Easy, Career Monk Publishers, 2016
 *
 * @note Prints messages to stdout.  This is Karumanchi's doing, not mine
 */

#include <stdio.h>
#include <stdlib.h>
#include "LinkedList.h"

// API functions

/**
 * Creates a new instance of the Linked List
 *
 * @returns	Pointer to the new Linked List instance if it succeeds.  NULL if it fails
 */
LinkedListPtr_t createLList(void) {
	LinkedListPtr_t L = malloc(sizeof(LinkedList_t));
	if(L == NULL){
        printf("ERROR: LinkedList ADT(createLList): Could not create Linked List\n");
		return NULL;
    }
    
	L->head = NULL;
	L->count = 0;
	return L;
}


/**
 * Returns the number of items in the list
 * 
 * @param L is a Pointer to a LinkedList instance
 *
 * @returns	Returns the number of nodes in the linked list
 */
int LListLength(LinkedListPtr_t L){
    if (L == NULL) {
        printf("ERROR: LinkedList ADT(LListLength): Linked List does not exist\n");
		return 0;
    }
        
	return L->count;
}


/**
 * Returns the data from a selected node
 * 
 * @param L is a Pointer to a LinkedList instance
 * @param pos is the position in the list to insert the item
 *
 * @returns	the data from the selected node as a double float
 */
long getNodeDataInLList(LinkedListPtr_t L, int pos) {
    ListNodePtr_t p = L->head;
    int k = 1;

	if(p == NULL){
		printf("ERROR: LinkedList ADT(getNodeDataInLList): List Empty\n");
		return LONG_MIN;
	}
	else if(pos == 1){
        return p->data;
	}
	else {
		while((p != NULL) && (k < pos)){
			k++;			
			p = p->next;
		}
		if(p == NULL){
			printf("ERROR: LinkedList ADT(getNodeDataInLList): Position %d is not in the list\n", pos);
            return LONG_MIN;
		}
		else{
			return p->data;
		}
	}
}


/**
 * Inserts a new node into the linked list
 * 
 * @param L is a Pointer to a LinkedList instance
 * @param data is the data item to put into the ndw node
 * @param pos is the position in the list to insert the item
 *
 * @returns	void
 */
void insertNodeInLList(LinkedListPtr_t L, double data, int pos){
	ListNodePtr_t head = L->head;
	ListNodePtr_t q, p;
	ListNodePtr_t newNode = (ListNodePtr_t) malloc(sizeof(ListNode_t));
		
	int k = 1;
    
    if (L == NULL) {
        printf("ERROR: LinkedList ADT(insertNodeInLList): Linked List does not exist\n");
		return;
    }
	
	if(!newNode){
		printf("ERROR: LinkedList ADT(insertNodeInLList): Could not create new node\n");
		return;
	}
	newNode->data = data;
	p = head;
	if ((pos == 1) || (p == NULL)){
		newNode->next = head;
		L->head = newNode;
		L->count++;
	}
	else {
		while((p != NULL) && (k < pos)){
			k++;
			q = p;
			p = p->next;
		}
		newNode->next = q->next;
		q->next = newNode;
		L->count++;
	}
}


/**
 * Deletes a new node into the linked list
 * 
 * @param L is a Pointer to a LinkedList instance
 * @param pos is the position in the list of the node to delete
 *
 * @returns	void
 */
void deleteNodeFromLLinkedList(LinkedListPtr_t L, int pos) {
	ListNodePtr_t head = L->head;
	ListNodePtr_t q, p;
	
	int k = 1;
    
    if (L == NULL) {
        printf("ERROR: LinkedList ADT(deleteNodeFromLLinkedList): Linked List does not exist\n");
		return;
    }   
	
	p = head;
	if(head == NULL){
		printf("LinkedList ADT(deleteNodeFromLLinkedList): List Empty\n");
		return;
	}
	else if( pos == 1){
		L->head = head->next;
		free(p);
		L->count--;
	}
	else {
		while((p!=NULL) && (k < pos)){
			k++;
			q = p;
			p = p->next;
		}
		if(p == NULL){
			printf("LinkedList ADT(deleteNodeFromLLinkedList): Position does not exist\n");
		}
		else{
			q->next = p->next;
			free(p);
			L->count--;
		}

	}
}


/**
 * Prints all of the data items in the Linked List
 * 
 * @param L is a Pointer to a LinkedList instance
 *
 * @returns	void
 */
void printLList(LinkedListPtr_t L) {
	
	ListNodePtr_t p = L->head;

    if (L == NULL) {
        printf("ERROR: LinkedList ADT(printLList): Linked List does not exist\n");
		return;
    }
	
	while(p != NULL){
		printf("%lf ", p->data);
		p = p->next;
	}
	printf("\n");
}


/**
 * Deletes all of the nodes in the linked list and then the LinkedList instance
 * 
 * @param L is a Pointer to a LinkedList instance
 *
 * @returns	void
 */
void deleteLList(LinkedListPtr_t L) {
    ListNodePtr_t p = L->head, temp = NULL;
    
    if (L == NULL) {
        printf("ERROR: LinkedList ADT(deleteLList): Linked List does not exist\n");
		return;
    }
	
	while(p != NULL){
        // delete the node and move on until end of list
        temp = p;
        p = p->next;
        free(temp);
	}
    // free the LinkedLlist instance
	free(L);
}



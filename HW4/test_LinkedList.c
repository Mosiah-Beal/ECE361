/**
 * test_LinkedList.c - Test program for the Linked List ADT
 *
 * @author Roy Kravitz (roy.kravitz@pdx.edu)
 * @date   07-Nov-2022
 * 
 * This is the source code file for a  test program for a Link List ADT.
 * Although it shouldn't matter as long as the API doesn't change, this
 * test if based on Karumanchi's SinglyLinkedList example.
 *
 * @note Code is based on DynamicStack.c from Narasimha Karumanchi
 * Data Structures and Algorithms Made Easy, Career Monk Publishers, 2016
 */

#include <stdlib.h>
#include <stdio.h>
#include "LinkedList.h"

int main(){  
	printf("Linked List ADT test program (RK)\n\n");
	
	// create a Linked List
	LinkedListPtr_t LL = createLList();
	printf("Created a new Linked List\n");
	printf("Number of nodes in List: %d\n", LListLength(LL));
		
	// insert a few items in the list
	printf("Inserting 5 and 2 into list...\n");
	insertNodeInLList(LL, 5, 5);
	insertNodeInLList(LL, 2, 5);
    
    // get the data from the nodes
    long d1 = getNodeDataInLList(LL, 1); 
    long d2 = getNodeDataInLList(LL, 2);
    printf(" Data from the Linked list nodes are:  node(1)= %ld, node(2)= %ld\n",
        d1, d2);
        
    // get a node that's not in the list.  Watch for error message
    getNodeDataInLList(LL, 3); 
	
	// check that the number of elements is correct
	// and then print them
	printf("Number of nodes in List: %d\n", LListLength(LL));
	printf("List contents: ");
	printLList(LL);
	
	// delete the first item on the list and
	// check the list to make sure it has been removed
	printf("Deleting a node from list...\n");
	deleteNodeFromLLinkedList(LL, 1);
	printf("Number of nodes in List: %d\n", LListLength(LL));
	printf("List contents: ");
	printLList(LL);
    
    //  delete the entire list
    deleteLList(LL);
    if (LL == NULL) {
        printf("The linked list has been deleted\n");
    }
	return 0;
}

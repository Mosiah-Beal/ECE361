/**
 * test_stackADT_LL.c - Starter code for a program to test your stack ADT
 *
 * @author: <your name> (<your email address>)
 * @date:   <date>
 *
 * This is the a test program for the linked list-based stack that you are writing.  You may find
 * it useful for testing your stack ADT implementation. 
 * 
 * You do not need to execute this or submit results.  It's yours to use/modify if you want too.
 *
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <errno.h>

#include "stackADT_LL.h"

int main(){
    int i = 0;
    struct Stack *stk = createStack();
    
    // display a greeting and the current working directory
    printf("Minimal test program for the stack ADT\n");
    errno = 0;
    char *buf = getcwd(NULL, 0);    // allocates a buffer large enough to hold the path
    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    }
    else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
    printf("\n\n");

    for(i = 0; i <= 10; i++){
        push(stk, i);
    }

    printf("Top element is %ld\n", peek(stk));
    printf("Stack size is %d\n", size(stk));

    for (i = 0; i <= 10; i++){
        printf("Popped element is %ld\n", pop(stk));
    }

    if (isEmpty(stk))
        printf("Stack is empty");
    else
        printf("Stack is not empty");

    deleteStack(stk);
    return 0;
 }

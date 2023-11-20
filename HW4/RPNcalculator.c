/**
 * RPNcalculator.c
 *
 * Author: Mosiah Beal (mosiah@pdx.edu)
 * Date:   Nov. 12, 2023
 *
 * Description: This program is a reverse polish notation calculator. It takes
 *             in a string of numbers and operators and returns the result of
 *             the calculation.
 */
 
// include files
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <unistd.h>
#include <math.h>
#include <string.h>
#include <errno.h>
#include <assert.h>

#include "stackADT_LL.h"

// prototypes
void print_dir(void);
int calculateRPN(char* input, struct Stack* stack);
Stack* getNewStack(Stack** stack)

int main() {
    // print the current working directory
    print_dir();

    // create a stack
    struct Stack* stack;
    stack = createStack();
    printf("initial stack pointer: %p\n", (void *) stack);

    char* result7 = "1 2 3 * + =";
    char* result_n8 = "5 8 * 4 9 - / =";
    
	char* result8 = "5 8 * 9 4 - / =";
    
    assert(calculateRPN(result7, stack) == 7);
	stack = getNewStack(&stack);
    
    assert(calculateRPN(result_n8, stack) == -8);
    stack = getNewStack(&stack);


	calculateRPN(result8, stack); 
	
    char *input = malloc(100 * sizeof(char));
    printf("Enter a string of numbers and operators: ");
    
    //scanf("%s", input);


    // loop through the string of numbers and operators 
    //check that integer division doesn't break it
	   
    //calculateRPN(input, stack);

    // check if there is only one number on the stack //head and result
    if (size(stack) != 1) {
        printf("Invalid expression\n");
        printf("Size = %d\nRemaining elements:\n", size(stack));
        
        while(size(stack)) {
        printf("%ld \n", pop(stack));
        }
        
        return 1;
    }

    // print the result
    printf("Result: %ld\n", pop(stack));
    return 0;

}


void print_dir(void) {
    errno = 0;
    char *buf = getcwd(NULL, 0);    // allocates a buffer to hold the path   
    if (buf == NULL) {
        perror("getcwd");
        printf("Could not display the path\n");
    }
    else {
        printf("Current working directory: %s\n", buf);
        free(buf);
    }
    printf("\n");
}

int calculateRPN(char* input, struct Stack* stack) {
     //echo input
     //printf("You input: %s\n", input);
     printf("stack pointer on entry: %p\n", (void *) stack);
     
     // loop through the string of numbers and operators 
     //check that integer division doesn't break it
    for (int i = 0; i < strlen(input); i++) {
    
    	// Ignore whitespace
        if (isspace(input[i])) {
        	continue;
    	}
        
        // if the character is a number, push it onto the stack
        else if (input[i] >= '0' && input[i] <= '9') {
            push(stack, input[i] - '0');
        }
        
        else if (input[i] == '=') {
        	//printf("Finished Calculating\n");
        	break;
        }
        // if the character is an operator, pop two numbers off the stack and
        // perform the operation
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
                 input[i] == '/' || input[i] == '^') {
            
            // check if user is adding a negative number to the stack
            if (input[i] == '-' && input[i+1] >= '0' && input[i+1] <= '9') {
                push(stack, (input[i+1] - '0') * -1);
                i++;    // skip the next character (added to stack)
                continue;
            }

            // check if there are at least two numbers on the stack
            if (size(stack) < 2) {
                printf("Invalid expression\n");
                return INT_MIN;
            }
            
            // pop the two numbers off the stack
            int num2 = pop(stack);	//added to stack second
            int num1 = pop(stack);	//added to stack first
            
            // perform the operation
            switch (input[i]) {
                case '+':
                	printf("%d + %d = %d\n", num1, num2, num1+num2);
                    push(stack, num1 + num2);
                    break;
                case '-':
                	printf("%d - %d = %d\n", num1, num2, num1-num2);
                    push(stack, num1 - num2);
                    break;
                case '*':
                printf("%d * %d = %d\n", num1, num2, num1*num2);
                    push(stack, num1 * num2);
                    break;
                case '/':
                printf("%d / %d = %d\n", num1, num2, num1/num2);
                    push(stack, num1 / num2);
                    break;
                case '^':
                printf("%d ^ %d = %lf\n", num1, num2, pow(num1, num2));
                    push(stack, pow(num1, num2));
                    break;
            }
        }
        // if the character is not a number or operator, print an error
        else {
            printf("Invalid character found: %c\n", input[i]);
            printf("Has value: %d\n", input[i]);
            
            //return INT_MIN;
        }
    }
    
	//completed loop successfully
	//printf("stack pointer on exit: %p\n", (void *) stack);
	//printf("Peeked: %ld\n", peek(stack));
	return peek(stack);
    
    //done processing string, return result
    return peek(stack);
}

Stack* getNewStack(Stack** stack) {
    deleteStack(*stack);
    *stack = createStack();
    return *stack;
    }
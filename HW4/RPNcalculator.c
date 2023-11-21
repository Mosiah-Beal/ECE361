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
#include <ctype.h>


#include "stackADT_LL.h"

// prototypes
void print_dir(void);
int calculateRPN(char* input, struct Stack* stack);
struct Stack* getNewStack(struct Stack** stack);

int main() {
    // print the current working directory
    print_dir();

    // create a stack
    struct Stack* stack;
    stack = createStack();
    //printf("initial stack pointer: %p\n", (void *) stack);

    // simple tests
    char* result7 = "1 2 3 * + =";
    char* result10= "1 2 + 3 4 + + =";
    
    assert(calculateRPN(result7, stack) == 7);
	//printf("%s %d\n", result7, calculateRPN(result7, stack)); 
	stack = getNewStack(&stack);
	
	assert(calculateRPN(result10, stack) == 10);
	//printf("%s %d\n", result10, calculateRPN(result10, stack)); 
	stack = getNewStack(&stack);
    
    // sign tests
    char* result_n8 = "5 8 * 4 9 - / =";
	char* result8 = "5 8 * 9 4 - / =";
	char* result8_2 = "5 -8 * 4 9 - / =";
	
	assert(calculateRPN(result_n8, stack) == -8);
	//printf("%s %d\n", result_n8, calculateRPN(result_n8, stack)); 
    stack = getNewStack(&stack);

	assert(calculateRPN(result8, stack) == 8);
	//printf("%s %d\n", result8, calculateRPN(result8, stack)); 
    stack = getNewStack(&stack);

	calculateRPN(result8_2, stack); 
	//printf("%s %d\n", result8_2, calculateRPN(result8_2, stack)); 
    stack = getNewStack(&stack);
	
	// fractional tests
	char* result1 = " 2 2 4 / * =";		// 2/4 -> 0 : 2*0 -> 0
	char* result_n3 = " 3 2 / 9 2 / - =";	// 9/2 -> 4 : 1-4 -> -3
	
	//assert(calculateRPN(result1, stack) == 1);
	//assert(calculateRPN(result1, stack) == 1);	
	// I realized that push is demoting the data from a double into a long int :( 
	//fractional results are not possible with the given prototypes in the stackADT header.
	

    // power tests
    char* result25 = " 5 2 ^ = ";
    char* result27 = " 3 3 ^ = ";
    
    assert(calculateRPN(result25, stack) == 25);
    //printf("%s %d\n", result25, calculateRPN(result25, stack)); 
    stack = getNewStack(&stack);
    
    assert(calculateRPN(result27, stack) == 27);
    //printf("%s %d\n", result27, calculateRPN(result27, stack)); 
	stack = getNewStack(&stack);
	

    char *input = malloc(100 * sizeof(char));
    do{
    printf("Enter a string of numbers and operators: ");
    scanf("%s", input);
	} while(strcmp(*input, "q") != 0)

    // loop through the string of numbers and operators 
    //check that integer division doesn't break it
	   
    //calculateRPN(input, stack);
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
     //printf("stack pointer on entry: %p\n", (void *) stack);
     bool debug = false;
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
            double num2 = pop(stack);	//added to stack second
            double num1 = pop(stack);	//added to stack first
            double quotient;
            //printf("num1: %lf num2: %lf\n", num1, num2);
            
            //printf("Step %d:  ", i);
            // perform the operation
            // math works with doubles, printf("%g") uses smallest representation of number 
            switch (input[i]) {
                case '+':
                	(!debug) ? 1+1 :printf("%g + %g = %g\n", num1, num2, num1+num2);
                    push(stack, num1 + num2);
                    break;
                case '-':
                	(!debug) ? 1+1 :printf("%g - %g = %g\n", num1, num2, num1-num2);
                    push(stack, num1 - num2);
                    break;
                case '*':
                	(!debug) ? 1+1 :printf("%g * %g = %g\n", num1, num2, num1*num2);
                    push(stack, num1 * num2);
                    break;
                case '/':
                	quotient = (double) num1 / num2;
                	(!debug) ? 1+1 :printf("%g / %g = %g\n", num1, num2, quotient);
                	//printf("Pre-push: %lf\n", quotient);
                    push(stack, (double) quotient);
                    //printf("post-push: %ld\n", peek(stack));
                    
                    break;
                case '^':
                	(!debug) ? 1+1 :printf("%g ^ %g = %g\n", num1, num2, pow(num1, num2));
                    push(stack, pow(num1, num2));
                    break;
            }
        }
        // if the character is not a number or operator, print an error
        else {
            printf("Invalid character found: %c\n", input[i]);
            printf("Has value: %d\n", input[i]);
            
        }
    }
    
	//completed loop successfully, return result
	//printf("stack pointer on exit: %p\n", (void *) stack);
	//printf("Peeked: %ld\n", peek(stack));
	return pop(stack);

}

struct Stack* getNewStack(struct Stack** stack) {
    deleteStack(*stack);
    *stack = createStack();
    return *stack;
    }

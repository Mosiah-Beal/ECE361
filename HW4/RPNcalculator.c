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
double calculateRPN(char* input, struct Stack* stack);
struct Stack* getNewStack(struct Stack** stack);

// global debug variable
bool debug = false;

int main() {
    // print the current working directory
    print_dir();

    // create a stack
    struct Stack* stack;
    stack = createStack();
    //printf("initial stack pointer: %p\n", (void *) stack);




	debug ? printf("Showing output of asserts\n\n"): 0; 
		
	// simple tests
	char* result7 = "1 2 3 * + =";
	char* result10= "1 2 + 3 4 + + =";

	(debug) ? (printf("%s\n", result7), printf("result = %g\n\n", calculateRPN(result7, stack))) : 
	assert(calculateRPN(result7, stack) == 7);
	stack = getNewStack(&stack);

	(debug) ? (printf("%s\n", result10), printf("result = %g\n\n", calculateRPN(result10, stack))) : 
	assert(calculateRPN(result10, stack) == 10);
	stack = getNewStack(&stack);

	// sign tests
	char* result_n8 = "5 8 * 4 9 - / =";
	char* result8 = "5 8 * 9 4 - / =";
	char* result8_2 = "5 -8 * 4 9 - / =";
	char* result_n15 = "-5 -10 + -5 -5- + ="; 

	(debug) ? (printf("%s\n", result_n8), printf("result = %g\n\n", calculateRPN(result_n8, stack))) : 
	assert(calculateRPN(result_n8, stack) == -8);
	stack = getNewStack(&stack);

	(debug) ? (printf("%s\n", result8), printf("result = %g\n\n", calculateRPN(result8, stack))) : 
	assert(calculateRPN(result8, stack) == 8);
	stack = getNewStack(&stack);

	(debug) ? (printf("%s\n", result8_2), printf("result = %g\n\n", calculateRPN(result8_2, stack))) : 
	assert(calculateRPN(result8_2, stack) == 8);
	stack = getNewStack(&stack);

	(debug) ? (printf("%s\n", result_n15), printf("result = %g\n\n", calculateRPN(result_n15, stack))) : 
	assert(calculateRPN(result_n15, stack) == -15);
	stack = getNewStack(&stack);

	// fractional tests
	char* result1 = " 2 2 4 / * =";		
	char* result_n3 = " 3 2 / 9 2 / - =";	

	(debug) ? (printf("%s\n", result1), printf("result = %g\n\n", calculateRPN(result1, stack))) : 
	assert(calculateRPN(result1, stack) == 1);
	stack = getNewStack(&stack);

	(debug) ? (printf("%s\n", result_n3), printf("result = %g\n\n", calculateRPN(result_n3, stack))) : 
	assert(calculateRPN(result_n3, stack) == -3);
	stack = getNewStack(&stack);


	// power tests
	char* result25 = " 5 2 ^ = ";
	char* result27 = " 3 3 ^ = ";

	(debug) ? (printf("%s\n", result25), printf("result = %g\n\n", calculateRPN(result25, stack))) : 
	assert(calculateRPN(result25, stack) == 25);
	stack = getNewStack(&stack);

	(debug) ? (printf("%s\n", result27), printf("result = %g\n\n", calculateRPN(result27, stack))) : 
	assert(calculateRPN(result27, stack) == 27);
	stack = getNewStack(&stack);
	
	
	// User test cases
    char *input = malloc(100 * sizeof(char));
    do{
		// Get input from user
		printf("Enter a string of numbers and operators: ");
		fgets(input, 100, stdin);
		
		// remove newline
		input[strcspn(input, "\n")] = 0;
		
		// Perform the calculations
		printf("%s %g\n", input, calculateRPN(input, stack)); 
		stack = getNewStack(&stack);
	} while((strcmp(input, "q") != 0) && (strcmp(input, "Q") != 0)); //exit on q/Q

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

double calculateRPN(char* input, struct Stack* stack) {
     //echo input
     //printf("You input: %s\n", input);
     
     //debug = true;
     
     // Check if user is trying to quit
	if ((strcmp(input, "q") == 0) || (strcmp(input, "Q") == 0)){
		return 0;
	}
    	
     // loop through the string of numbers and operators 
     //check that integer division doesn't break it
    for (int i = 0; i < strlen(input); i++) {
    	
    	// Ignore whitespace
     	if (isspace(input[i])) {
    		continue;
    	}
        
        // if the character is a number, push it onto the stack
        else if (input[i] >= '0' && input[i] <= '9') {
            
    		double number = (input[i] - '0');
    		i++; //look at next character
			while (input[i] >= '0' && input[i] <= '9') {
		    	number = number * 10 + (input[i] - '0');
		   	 	i++;
			}
			
			// Finished getting multi-digit number, push to stack
			//printf("%lf\n", number);
			push(stack, (double) number);
			//printf("post-push (initial): %lf\n", peek(stack));
			i--; // decrement i because the outer loop will increment it
			continue;
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
                
                // store initial number 
                double number = (input[++i] - '0');
                
    			i++; //look at next character
				while (input[i] >= '0' && input[i] <= '9') {
		    		number = number * 10 + (input[i] - '0');
		   		 	i++;
					//printf("num: %d\n", number);
		    		
				}
                
                push(stack, (double) number * -1);	// Store result as negative number
                i--;    // decrement i because the outer loop will increment it
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
                    //printf("post-push: %lf\n", peek(stack));
                    
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
	//printf("Peeked: %ld\n", peek(stack));
	return pop(stack);

}

struct Stack* getNewStack(struct Stack** stack) {
    deleteStack(*stack);
    *stack = createStack();
    return *stack;
    }

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

int main() {
    // print the current working directory
    print_dir();

    // create a stack
    struct Stack* stack;
    stack = createStack();

    char* result7 = "1 2 3 * + =";
    char* result_n8 = "5 8 * 4 9 - / =";

    assert(calculateRPN(result7, stack) == 7);
    assert(calculateRPN(result_n8, stack) == -8);


    char *input = malloc(100 * sizeof(char));
    printf("Enter a string of numbers and operators: ");
    scanf("%s", input);

    // input validation
    /*
    for (int i = 0; i < strlen(input); i++) {
        if (input[i] >= '0' && input[i] <= '9') {
            continue;
        }
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
                 input[i] == '/' || input[i] == '^') {
            continue;
        }
        else {
            printf("Invalid character: %c\n", input[i]);
            return 1;
        }
    }
    */

    // loop through the string of numbers and operators //check that integer division doesn't break it
    calculateRPN(input, stack);

    // check if there is only one number on the stack
    if (size(stack) != 1) {
        printf("Invalid expression\n");
        return 1;
    }

    // print the result
    printf("Result: %ld\n", pop(stack));
    return 0;

}


void print_dir(void)
{
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
     
     // loop through the string of numbers and operators 
     //check that integer division doesn't break it
    for (int i = 0; i < strlen(input); i++) {
        
        // if the character is a number, push it onto the stack
        if (input[i] >= '0' && input[i] <= '9') {
            push(stack, input[i] - '0');
        }
        
        else if (input[i] == '=') {
        	printf("Finished Calculating");
        	return peek(stack);
        }
        // if the character is an operator, pop two numbers off the stack and
        // perform the operation
        else if (input[i] == '+' || input[i] == '-' || input[i] == '*' ||
                 input[i] == '/' || input[i] == '^') {
            
            // check if there are at least two numbers on the stack
            if (size(stack) < 2) {
                printf("Invalid expression\n");
                return INT_MIN;
            }
            
            // pop the two numbers off the stack
            int num1 = pop(stack);
            int num2 = pop(stack);
            
            // perform the operation
            switch (input[i]) {
                case '+':
                    push(stack, num1 + num2);
                    break;
                case '-':
                    push(stack, num1 - num2);
                    break;
                case '*':
                    push(stack, num1 * num2);
                    break;
                case '/':
                    push(stack, num1 / num2);
                    break;
                case '^':
                    push(stack, pow(num1, num2));
                    break;
            }
        }
        // if the character is not a number or operator, print an error
        else {
            printf("Invalid character found: %c\n", input[i]);
            return INT_MIN;
        }
    }
    //done processing string, return result
    return pop(stack);
}

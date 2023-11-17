/**
 * STARTER CODE
 *
 * sort_words.c() - sorts a list of words
 *
 * @author     Mosiah Beal (mosiah@pdx.edu)
 * @date       Oct 23, 2023
 *
 *  Uses malloc() and free() to allocate space for the words.  Words are stored
 *  in an array of pointers to the character strings containing the words.  Does
 *  the sort using the C library qsort() function.  Compare function is provided
 *  in the starter code.
 *
 *  Original problem from C Programming: A Modern Approach:2e by K.N. King.  Modified
 *  by Roy Kravitz.
 *
 *  NOTE:  You do not need to follow my program flow in your application.  I based the starter
 *  code on my solution which may take a different approach than you had in mind.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

// ADD YOUR #INCLUDES (IF ANY) HERE

/***** enums, constants, and typedefs *****/
#define MAX_WORDS 50
#define WORD_LEN 20

// ADD YOUR ENUMS, CONSTANTS, AND TYPEDEFS (IF ANY) HERE

/***** global variables *****/
// ADD YOUR GLOBAL VARIABLES HERE

/***** Function prototypes *****/
int compare_strings(const void *p, const void *q);

// ADD YOUR FUNCTION PROTOYPES (IF ANY) HERE

/***** main() *****/
int main(void)
{
    char *words[MAX_WORDS];     // array of pointers to strings containing words
    int num_words = 0;          // number of words currently in the words[]
  
    // ADD YOUR LOCAL VARIABLES HERE
    char* break_string = "\n";
    
    // Greet the user and display the working directory for the application
    // TODO:  Personalize the greeting message.  Note:  you need to be running
    // the gcc command line tools on a shell like bash.
    printf("Sort up to %d words of length %d at a time (mosiah@pdx.edu)\n", MAX_WORDS, WORD_LEN);
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
    printf("\n");
    
    // ADD YOUR CODE FOR ENTERING WORDS, ALLOCATING SPACE FOR THE STRING
    // CONTAINING THE WORD AND PUTTING THE WORD IN THE WORDS ARRAY HERE
    //may be unneeded 
    for(int i=0; i< MAX_WORDS; i++)
    {
        words[i] = NULL;    // Point all pointers in array to NULL
    }
    
    printf("Input Stream:\n");
    do{
    // check if there is an index available for the word to be stored at
    if(num_words >= MAX_WORDS)
    {
        printf("You may only put in %d words at a time\n", MAX_WORDS);
        break;
    }
    // try to allocate a string of size WORD_LEN + 1 (21)
    else if((words[num_words] = malloc(WORD_LEN+1)) == NULL)
    {
        printf("Error: Not enough space to allocate string of size %d\n", WORD_LEN);
        break;
    }
    
    if((fgets(words[num_words], WORD_LEN+1, stdin)) == NULL)
    {
        printf("Error: Unable to process input from stdin\n");
        continue;
    }
    } while(compare_strings(&words[num_words++], &break_string) != 0);
    // user entered an empty string
    
    // all the words are in the array so sort them
    qsort(words, num_words, sizeof(char *), compare_strings);

    // display the sorted list
    printf("\nIn sorted order:");
    for (int i = 0; i < num_words; i++) {
        printf(" %s", words[i]);
        free(words[i]);
        words[i] = NULL;
    }
    printf("\n");

    printf("Exiting word sorting application\n");
    return 0;
}

/**
 * compare_strings() - compares to strings.  Used by qsort()
 *
 * @param   pointer to the first string
 * @param   pointer to the string to compare it to
 *
 * @returns 0 if the strings are equal, < or > to compare strings
 */
int compare_strings(const void *p, const void *q)
{
    return strcmp(*(char **)p, *(char **)q);
}




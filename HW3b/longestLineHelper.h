/**
 * longestLineHelper.h - Header file for the helper functions for longestLine.c
 *
 * @author:     Roy Kravitz (roy.kravitz@pdx.edu)
 * @date:       08-Oct-2023
 * @version:    1.0
 *
 * Based on longestLine.c (as implemented by Roy Kravitz) from K & R Chapter 1
 *
 */

#ifndef _LONGESTLINEHELPER_H
#define _LONGESTLINEHELPER_H

// define constants
#define MAXLINE 1000    // maximum input line length (no error checking)

// no global variables in this implementation

// function prototypes
/**
  * getaline() - read a line into s, return length
  * 
  * @param  s[]     The character array holding the line
  * @ param lim     The maximum number of characters read
  *
  * @return The length of the line or 0 if EOF or an empty line
  */
 int getaline(char s[],int lim);
 
/**
 * copy() - copy 'from' into 'to'.  Assume to is big enough
 *
 * @param   from    character array to copy from
 * @param   to      character array to copy to 
 *
 * @note:  WARNING - There is no bounds checking so make sure to[] is large enough
 * to hold the entire string
 */
 void copy(char to[], char from[]);
 
 #endif

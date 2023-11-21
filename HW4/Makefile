# Makefile for HW4
CFLAGS = -Wall -std=c99 -lm

HEADERS = LinkedList.h stackADT_LL.h colors.h float_rndm.h iom361_r2.h
OBJECTS = LinkedList.o stackADT_LL.o colors.o float_rndm.o iom361_r2.o

# All .c files in the directory
SRCS = $(wildcard *.c)

# Object files (one for each source file)
OBJS = $(SRCS:.c=.o)

# Problem Dependencies
PROBLEM1 = hw4_p1.o LinkedList.o
PROBLEM2 = RPNcalculator.o $(PROBLEM1)
PROBLEM3 = hw4_p3.o float_rndm.o iom361_r2.o colors.o $(PROBLEM1)


# Problems
problem1: $(PROBLEM1) test_stackADT_LL.o
	gcc $(CFLAGS) -o $@ $^

problem2: $(PROBLEM2) float_rndm.o
	gcc $(CFLAGS) -o $@ $^

problem3: $(PROBLEM3)
	gcc $(CFLAGS) -o $@ $^


# Rule to make object files out of c files
%.o: %.c
	gcc $(CFLAGS) -c $<


# Test cases
test_problem1: test_stackADT_LL.o $(PROBLEM1)
	gcc $(CFLAGS) -o $@ $^

test_stackADT_LL.o: test_stackADT_LL.c
	gcc $(CFLAGS) -c $<

test_LinkedList.o: test_LinkedList.c
	gcc $(CFLAGS) -c $< 


clean:
	rm -f $(OBJS) $(PROBLEM1) $(PROBLEM2) $(PROBLEM3) problem1 problem2 problem3
    	
$(OBJECTS) : $(HEADERS)






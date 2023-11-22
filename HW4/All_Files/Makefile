# Makefile for HW4
CFLAGS = -Wall -std=c99 -lm

# Problem Dependencies
PROBLEM1 = hw4_p1.o LinkedList.o
PROBLEM2 = RPNcalculator.o $(PROBLEM1)
PROBLEM3 = hw4_p3.o float_rndm.o iom361_r2.o colors.o $(PROBLEM1)


# Rule to make object files out of c files
%.o: %.c
	gcc $(CFLAGS) -c $<


# Default rule to make all 3 problems
all: problem1 problem2 problem3


# Problems
problem1: $(PROBLEM1) test_stackADT_LL.o
	gcc $(CFLAGS) -o $@ $^

problem2: $(PROBLEM2) float_rndm.o
	gcc $(CFLAGS) -o $@ $^

problem3: $(PROBLEM3) hw4_p3.o
	gcc $(CFLAGS) -o $@ $^


# Test cases
test_problem1a: test_LinkedList.o $(PROBLEM1)
	gcc $(CFLAGS) -o $@ $^

test_problem1b: test_stackADT_LL.o $(PROBLEM1)
	gcc $(CFLAGS) -o $@ $^

test_problem3: test_iom361_r2.o float_rndm.o iom361_r2.o colors.o $(PROBLEM1)
	gcc $(CFLAGS) -o $@ $^


clean:
	rm -f *.o problem1 problem2 problem3 test_problem1a test_problem1b test_problem3


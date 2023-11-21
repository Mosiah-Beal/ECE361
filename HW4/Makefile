# Makefile for HW4
CFLAGS = -Wall -std=c99 -lm

HEADERS = LinkedList.h stackADT_LL.h
OBJECTS = hw4_p1.o test_stackADT_LL.o

# All .c files in the directory
SRCS = $(wildcard *.c)

# Object files (one for each source file)
OBJS = $(SRCS:.c=.o)

PROBLEM1 = hw4_p1.o LinkedList.o
PROBLEM2 = RPNcalculator.o hw4_p1.o LinkedList.o float_rndm.o
PROBLEM3 = hw4_p3.o float_rndm.o iom361_r2.o colors.o $(PROBLEM1)

all: $(PROBLEM3)

problem1: $(PROBLEM1) test_stackADT_LL.o
	gcc $(CFLAGS) -o $@ $^

problem2: $(PROBLEM2)
	gcc $(CFLAGS) -o $@ $^

problem3: $(PROBLEM3)
	gcc $(CFLAGS) -o $@ $^


LinkedList.o: LinkedList.c
	gcc $(CFLAGS) -c $<

float_rndm.o: float_rndm.c
	gcc $(CFLAGS) -c $<

colors.o: colors.c
	gcc $(CFLAGS) -c $<

hw4_p1.o: hw4_p1.c
	gcc $(CFLAGS) -c $<

RPNcalculator.o: RPNcalculator.c 
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
    	
#$(OBJECTS) : $(HEADERS)


$(OUTPUT): $(OBJS)
	gcc $(CFLAGS) -o $@ $^

%.o: %.c
	gcc $(CFLAGS) -c $<



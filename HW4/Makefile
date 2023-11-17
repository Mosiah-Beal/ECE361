# Makefile for HW4
CFlags = -Wall -std=c99
MathFlag = -lm

HEADERS = LinkedList.h stackADT_LL.h
OBJECTS = hw4_p1.o test_stackADT_LL.o

problem1: hw4_p1.o
	gcc $(CFlags) -o $@ hw4_p1.o

hw4_p1.o: hw4_p1.c
	gcc $(CFlags) -c $<

test_stackADT_LL.o: test_stackADT_LL.c
	gcc $(CFlags) -c $<

test_LinkedList.o: test_LinkedList.c
	gcc $(CFlags) -c $<
	
$(OBJECTS) : $(HEADERS)

clean: 
	rm problem1 hw4_p1.o test_stackADT_LL.o

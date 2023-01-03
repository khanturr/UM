# Makefile for um (Comp 40 Assignment 6)
# 
# Includes build rules for a2test and ppmtrans.
#
# This Makefile is more verbose than necessary.  In each assignment
# we will simplify the Makefile using more powerful syntax and implicit rules.
#
# Last updated: Nov 23, 2022

############## Variables ###############

CC = gcc # The compiler being used

# Updating include path to use Comp 40 .h files and CII interfaces
IFLAGS = -I/comp/40/include -I/usr/sup/cii40/include/cii

# Compile flags
# Set debugging information, allow the c99 standard,
# max out warnings, and use the updated include path
CFLAGS = -g -O2 -std=c99 -Wall -Wextra -Werror -Wfatal-errors -pedantic $(IFLAGS)

# Linking flags
# Set debugging information and update linking path
# to include course binaries and CII implementations
LDFLAGS = -g -L/comp/40/lib64 -L/usr/sup/cii40/lib64

# Libraries needed for linking
# Both programs need cii40 (Hanson binaries) and *may* need -lm (math)
# Only brightness requires the binary for pnmrdr.
LDLIBS = -lnetpbm -lcii40-O2 -lm -lrt -lbitpack


LDFLAGS = -g -L/comp/40/build/lib -L/usr/sup/cii40/lib64
LDLIBS  = -l40locality -lcii40-O2 -lm -lbitpack

# Collect all .h files in your directory.
# This way, you can never forget to add
# a local .h file in your dependencies.
#
# This bugs Mark, who dislikes false dependencies, but
# he agrees with Noah that you'll probably spend hours 
# debugging if you forget to put .h files in your 
# dependency list.
INCLUDES = $(shell echo *.h)

############### Rules ###############

all: um writetests

## Compile step (.c files -> .o files)

# To get *any* .o file, compile its .c file with the following rule.
%.o: %.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

## Linking step (.o -> executable program)
test.o: test.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

um.o: um.c $(INCLUDES)
	$(CC) $(CFLAGS) -c $< -o $@

# cputiming.o: cputiming.h cputiming_impl.h cputiming.c $(INCLUDES)
# 	$(CC) $(CFLAGS) -c $< -o $@ 

test: test.o segment.o instruction.o word.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

um: bitpack.o segment.o stack.o memory.o instruction.o word.o run.o um.o
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

writetests: bitpack.o umlabwrite.o umlab.o 
	$(CC) $(LDFLAGS) $^ -o $@ $(LDLIBS)

clean:
	rm -f test *.o
/********************************************************************
 *
 *                     instruction.c
 *
 *     Assignment: um
 *     Authors:  Brandon Shih (bshih01), Hunter Purevbayar (hpurev01)
 *     Date:     11/23/2022
 *
 *     Summary: Implementation of the instruction module. This file
 *              contains the functions dedicated to each 13 instruction
 *
 *     
 *
 ********************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "instruction.h"
#include "segment.h"
#include "stack.h"

uint32_t conditional_move(uint32_t A, uint32_t B, uint32_t C)
{
        /* using register C as the conditonal to move or not move B to A */
	if (C != 0) {
		return B;
        }
	return A;
}

uint32_t add(uint32_t B, uint32_t C)
{
	return B + C;
}

uint32_t multiply(uint32_t B, uint32_t C)
{
	return B * C;
}

uint32_t divide(uint32_t B, uint32_t C)
{
        /* assering that C is not 0 to catch floating exception */
	assert(C);
	return B / C;
}

uint32_t nand(uint32_t B, uint32_t C)
{
	return ~(B & C);
}

void halt(Memory segments, Stack IDs)
{
	Segment segment;
	int length = segments->size;
	/*get segments until length of sequence */
	for (int i = 0; i < length; i++) {
		segment = (segments->segArr)[i];
		if (segment) {
			/* if remaining, free */
			free(segment->words);
			free(segment);
		}
	}
        /* freeing the container of sequence */
	free(segments->segArr);
	free(segments);
        /* freeing all the malloc'd uint32_t inside */
	free(IDs->stackArr);
	free(IDs);
}

void output(uint32_t C)
{
        /* making sure that that the ASCii is printable */
	assert(C <= 255);	
	putchar(C);
}

uint32_t get_input()
{
        /* retreives the char and returns as a word */
        return (uint32_t)getchar();
}

Segment load_prog(uint32_t ID, Memory segments)
{
	/* getting the segment to be copied */
	Segment segment = (segments->segArr)[ID];
        /* making sure the segment is not NULL */
	assert(segment);
        /* creating new segment0 and allocating memory to return */
        Segment segment0;
	segment0 = malloc(sizeof(struct Segment));
	segment0->words = malloc(segment->size * sizeof(uint32_t));
	segment0->size = segment->size;
        /* copying the data over to the segment0 */
	for (uint32_t i = 0; i < segment->size; i++) {
		segment0->words[i] = segment->words[i];
	}
	return segment0;
}

uint32_t load_value(uint32_t word)
{
        /* shifting the opcode and register off */
	return (word << 7) >> 7;
}

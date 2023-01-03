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

uint32_t conditional_move(uint32_t A, uint32_t B, uint32_t C)
{
        /* using register C as the conditonal to move or not move B to A */
	if (C != 0) {
		return B;
        }
	return A;
}

uint32_t segmented_load(uint32_t index, uint32_t ID, Seq_T memory)
{
        /* using the load_word function in the segment module */
	return load_word(index, ID, memory);
}

void segmented_store(uint32_t index, uint32_t newWord, uint32_t ID, 
                     Seq_T memory)
{
        /* using the store_word function in the segment module */
	store_word(index, newWord, ID, memory);
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

void halt(Seq_T segments, Stack_T IDs)
{
	Segment segment;
	/*get segments until length of sequence */
	for (int i = 0; i < Seq_length(segments); i++) {
		segment = Seq_get(segments, i);
		if (segment) {
			/* if remaining, free */
			free(segment->words);
			free(segment);
		}
	}
        /* freeing the container of sequence */
	Seq_free(&segments);
        /* freeing all the malloc'd uint32_t inside */
	while (!Stack_empty(IDs)) {
		free(Stack_pop(IDs));
	}
        /* freeing the container of stack */
	Stack_free(&IDs);
}

uint32_t map_seg(Seq_T segments, uint32_t size, Stack_T IDs)
{      
        /* using the map function in the segment module */
	return map(segments, size, IDs);
}

void unmap_seg(Seq_T segments, uint32_t id)	
{
        /* using the unmap function in the segment module */
	unmap(segments, id);
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

Segment load_prog(uint32_t id, Seq_T segments)
{
	/* getting the segment to be copied */
	Segment segment = Seq_get(segments, id);
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

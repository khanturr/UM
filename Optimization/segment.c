/**************************************************************
 *
 *                     instruction.c
 *
 *     Assignment: um
 *     Authors:  Brandon Shih (bshih01),  Hunter Purevbayar (hpurev01)
 *     Date:     11/23/2022
 *
 *     Summary: 
 *
 *     
 *
 **************************************************************/

#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "segment.h"
#include "memory.h"
#include "stack.h"

uint32_t map(Memory segments, int size, Stack IDs)
{
        /* allocating memory for struct segment */
	Segment segment = malloc(sizeof(struct Segment));
        /* allocating memory for the segment of words */
	segment->words = malloc(size * sizeof(uint32_t));
	segment->size = size;
        /* initializing everything in the segment as 0*/
	for(int i = 0; i < size; i++) {
		segment->words[i] = 0;
	}
	uint32_t ID;
	Segment *memory = segments->segArr;
        /* checking if a new ID needs to me made */
	if (IDs->size == 0) {
		ID = append(segments, segment);
        /* case when ID can be recycled from stack of IDs */
	} else {
		ID = pop(IDs);
		//fprintf(stderr, "ID: %u\n", ID);
		memory[ID] = segment;
	}
	/* return id of mapped segment */
	return ID;
}

void unmap(Memory segments, uint32_t ID)	
{
	Segment segment = (segments->segArr)[ID];
	/* assert that segment isn't NULL */
	assert(segment);
	/* free memory */
	free(segment->words);
	free(segment);
	(segments->segArr)[ID] = NULL;
}

uint32_t load_word(uint32_t index, uint32_t ID, Memory segments)
{
	Segment segment = (segments->segArr)[ID];
	/* assert segment != NULL and index is less than the segment size */
	assert(segment);
	assert(index < segment->size);
	/* return words at index */
	return segment->words[index];
}

void store_word(uint32_t index, uint32_t newWord, uint32_t ID, Memory segments)
{
	Segment *memory = segments->segArr;
        /* assering that segment is not NULL*/
	assert(memory[ID]);
        /* asserting that the index is a valid index */
	assert(index < memory[ID]->size);
	(memory[ID])->words[index] = newWord;		
}
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

uint32_t map(Seq_T segments, int size, Stack_T IDs)
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
        /* checking if a new ID needs to me made */
	if (Stack_empty(IDs)) {
		ID = (uint32_t)Seq_length(segments);
		Seq_addhi(segments, segment);
        /* case when ID can be recycled from stack of IDs */
	} else {
		uint32_t *IDp = Stack_pop(IDs);
                ID = *IDp;
		Seq_put(segments, ID, segment);
		free(IDp);
	}
	/* return id of mapped segment */
	return ID;
}

void unmap(Seq_T segments, uint32_t ID)	
{
	Segment segment = Seq_put(segments, ID, NULL);
	/* assert that segment isn't NULL */
	assert(segment);
	/* free memory */
	free(segment->words);	
	free(segment);
}

uint32_t load_word(uint32_t index, uint32_t ID, Seq_T segments)
{
	Segment segment = Seq_get(segments, ID);
	/* assert segment != NULL and index is less than the segment size */
	assert(segment);
	assert(index < segment->size);	
	/* return words at index */
	return segment->words[index];
}

void store_word(uint32_t index, uint32_t newWord, uint32_t ID, Seq_T segments)
{
	Segment segment = Seq_get(segments, ID);
        /* assering that segment is not NULL*/
	assert(segment);
        /* asserting that the index is a valid index */
	assert(index < segment->size);
	segment->words[index] = newWord;		
}
/**************************************************************
 *
 *                     segment.h
 *
 *     Assignment: um
 *     Authors:  Brandon Shih (bshih01),  Hunter Purevbayar (hpurev01)
 *     Date:     11/23/2022
 *
 *     Summary: Implementation for segment module. This file handles
 *              the mapping and unmapping of segments, loading and
 *              storing in the segments.
 *
 *     
 *
 **************************************************************/
#ifndef SEGMENT_H
#define SEGMENT_H

#include <stdlib.h>
#include <stdint.h>
#include <seq.h>
#include <stack.h>

typedef struct Segment {
	uint32_t size;
	uint32_t *words;
} *Segment;

/*
Purpose: The purpose of this function is to store ids in the 
         sequence while creating a new array of "size" and
		 initializing to 0.
Arguments: Seq_T memory, int size, Stack_T IDs
Return: Segment ID
Effects: none 
*/
uint32_t map(Seq_T memory, int size, Stack_T IDs);

/*
Purpose: The purpose of this function is to free the mapped
         segment at "id" and set it to NULL
Arguments: Seq_T segments, uint32_t id
Return: none
Effects: none 
*/
void unmap(Seq_T segments, uint32_t id);	

/*
Purpose: The purpose is to load the word while accessing
         the sequence at "id" index and returning the value at the offset.
Arguments: uint32_t index, uint32_t B, Seq_T segments
Return: segment
Effects: none 
*/
uint32_t load_word(uint32_t index, uint32_t B, Seq_T segments);

/*
Purpose: The purpose is to store the word in the segment by storing it in the
         array at index "id"
Arguments: uint32_t index, uint32_t word, uint32_t id, Seq_T segments
Return: none
Effects: none 
*/
void store_word(uint32_t index, uint32_t word, uint32_t id, Seq_T segments);

#endif
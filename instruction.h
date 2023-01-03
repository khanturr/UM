/**************************************************************
 *
 *                     instruction.c
 *
 *     Assignment: um
 *     Authors:  Brandon Shih (bshih01),  Hunter Purevbayar (hpurev01)
 *     Date:     11/23/2022
 *
 *     Summary: Header of the instruction module. This file outlines
 *              the instructions handling functions.
 *
 *     
 *
 **************************************************************/
#ifndef INSTRUCTIONS_H
#define INSTRUCTIONS_H

#include <stdlib.h>
#include <stdint.h>
#include <seq.h>
#include <stack.h>
#include "segment.h"

/*
Purpose: The purpose of this function is to execute a move
if uint32_t type C is not equal to 0.
Arguments: uint32_t A, uint32_t B, uint32_t C
Return: uint32_t A
Effects: none 
*/
uint32_t conditional_move(uint32_t A, uint32_t B, uint32_t C); 

/*
Purpose: The purpose of this function is to load word from memory
Arguments: uint32_t index, uint32_t id, Seq_T segments
Return: 
Effects: none 
*/
uint32_t segmented_load(uint32_t index, uint32_t id, Seq_T segments);

/*
Purpose: The purpose of this function is to store words into memory
Arguments: uint32_t index, uint32_t word, uint32_t id, Seq_T segments
Return:
Effects: none 
*/
void segmented_store(uint32_t index, uint32_t word, uint32_t id,
                     Seq_T segments);

/*
Purpose: The purpose of this function is to add two specific values
Arguments: uint32_t B, uint32_t C
Return: added value of B and C
Effects: none 
*/
uint32_t add(uint32_t B, uint32_t C);

/*
Purpose: The purpose of this function is to multiply two specific values
Arguments: uint32_t B, uint32_t C
Return: multiplied value of B and C
Effects: none 
*/
uint32_t multiply(uint32_t B, uint32_t C); 

/*
Purpose: The purpose of this function is to divide two specific values
Arguments: uint32_t B, uint32_t C
Return: divided value of B and C
Effects: none 
*/
uint32_t divide(uint32_t B, uint32_t C); 

/*
Purpose: The purpose of this function is to nand two specific values.
Arguments: uint32_t B, uint32_t C
Return: nanded value of B and C
Effects: none 
*/
uint32_t nand(uint32_t B, uint32_t C); 

/*
Purpose: The purpose of this function is to free all memory left in 
the machine and terminate the program.
Arguments: Seq_T segments, Stack_T IDs
Return: none
Effects: none 
*/
void halt(Seq_T segments, Stack_T IDs);

/*
Purpose: The purpose of this function is to activate a new segment and
return the ID of said segment.
Arguments: Seq_T segments, uint32_t size, Stack_T IDs
Return: id of mapped segment
Effects: none 
*/
uint32_t map_seg(Seq_T segments, uint32_t size, Stack_T IDs);  //added stack

/*
Purpose: The purpose of this function is to deactivate a segment
Arguments: Seq_T segments, uint32_t id
Return: none
Effects: none 
*/
void unmap_seg(Seq_T segments, uint32_t id); 

/*
Purpose: The purpose of this function is to output a character
while it is less than 255
Arguments: uint32_t C
Return: none
Effects: none 
*/
void output(uint32_t C); 

/*
Purpose: The purpose of this function is to take input from stdin.
Arguments: none
Return: uint32_t input
Effects: none 
*/
uint32_t get_input(); 

/*
Purpose: The purpose of this function is to duplicate and return
the segment
Arguments: uint32_t id, Seq_T segments
Return: segment
Effects: none 
*/
Segment load_prog(uint32_t id, Seq_T segments);

/*
Purpose: The purpose of this function is to return the last 25
bits of the word
Arguments: uint32_t word
Return: value
Effects: none 
*/
uint32_t load_value(uint32_t word); 

#endif
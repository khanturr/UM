/**************************************************************
 *
 *                     run.h
 *
 *     Assignment: um
 *     Authors:  Brandon Shih (bshih01),  Hunter Purevbayar (hpurev01)
 *     Date:     11/23/2022
 *
 *     Summary: Header for run module. This file contains the declarations
 *     of the functions to run the universal machine and initialize registers.
 *
 *     
 *
 **************************************************************/
#ifndef RUN_H
#define RUN_H

#include <stdlib.h>
#include <stdint.h>
#include "segment.h"
#include "stack.h"

/*
Purpose: Run the universal machine. This function initializes
         segment zero and memory storages and uses a loop to
         execute the instructions
Arguments: input file
Return: none
Effects: none 
*/
void run(FILE *input);

/*
Purpose: The purpose of this function is to initialize registers used by
         UM while storing instructions in segment zero.
Arguments: input file
Return: segment0
Effects: updates segment0
*/
Segment init(FILE *input);

#endif
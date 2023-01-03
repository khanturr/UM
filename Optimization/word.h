/**************************************************************
 *
 *                     word.h
 *
 *     Assignment: um
 *     Authors:  Brandon Shih (bshih01),  Hunter Purevbayar (hpurev01)
 *     Date:     11/23/2022
 *
 *     Summary: Header for word module. This file contains
 *              the declarations for functions needed to handle words
 *              from an input .um file. 
 *
 **************************************************************/
#ifndef WORD_H
#define WORD_H

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
Purpose: The purpose of this function is to read in the word
         from input file and store into uint32_t.
Arguments: uint32_t id, Seq_T segments
Return: registers
Effects: none 
*/
uint32_t readInWord(FILE *input);
/*
Purpose: The purpose of this function is to get opcode from 
         uint32_t word.
Arguments: uint32_t id, Seq_T segments
Return: uint32_t opcode
Effects: none 
*/
uint32_t getOpcode(uint32_t word);
/*
Purpose: The purpose of this function is to get the register
         
Arguments: uint32_t id, Seq_T segments
Return: uint32_t register
Effects: none 
*/
uint32_t getRegister(uint32_t word, uint32_t offset);

#endif
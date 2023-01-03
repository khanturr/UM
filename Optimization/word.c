/**************************************************************
 *
 *                     word.c
 *
 *     Assignment: um
 *     Authors:  Brandon Shih (bshih01),  Hunter Purevbayar (hpurev01)
 *     Date:     11/23/2022
 *
 *     Summary: Implementation for word module. This file contains
 *              the implementations for functions needed to handle words
 *              from an input .um file.
 *
 *     
 *
 **************************************************************/
#include "word.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

uint32_t readInWord(FILE *input)
{
        /* gets the 4 chars and from file and makes a word from them */
        uint32_t a = (getc(input)) << 24;
        uint32_t b = (getc(input)) << 16;
        uint32_t c = (getc(input)) << 8;
        uint32_t d = getc(input);
        return a | b | c | d;
}

uint32_t getOpcode(uint32_t word)
{
        /* returns the 4 bits on the left */
        return word >> 28;
}

uint32_t getRegister(uint32_t word, uint32_t lsb)
{
        /* the register at the specified lsb */
        return (word << (32 - lsb)) >> 29;
}
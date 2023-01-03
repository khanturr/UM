/**************************************************************
 *
 *                     run.c
 *
 *     Assignment: um
 *     Authors:  Brandon Shih (bshih01),  Hunter Purevbayar (hpurev01)
 *     Date:     11/23/2022
 *
 *     Summary: Implementation of run module. This file contains 
 *     the implementations of the functions to run the universal 
 *     machine and initialize registers.
 *
 *     
 *
 **************************************************************/
#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include "run.h"
#include "instruction.h"
#include "segment.h"
#include "word.h"

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;

void run(FILE *input)
{
	Stack_T IDs = Stack_new(); 
	Seq_T segments = Seq_new(0);
	uint32_t registers[8] = {0};
	uint32_t ra, rb, rc, A, B, C, opcode, word;
	Segment segment0 = init(input);
	Seq_addhi(segments, segment0);
	for (uint32_t i = 0; i < segment0->size; i++) {		
		word = segment0->words[i];
                //index of registers a,b,c
		ra = getRegister(word, 9);
		rb = getRegister(word, 6);
		rc = getRegister(word, 3);
                //
                A = registers[ra]; 				
		B = registers[rb];
		C = registers[rc];
		opcode = getOpcode(word);
		assert(opcode <= 13);
		if (opcode == CMOV) {
                        //if instruction is conditional move
                        registers[ra] = conditional_move(A, B, C);
                } else if (opcode == SLOAD) {
                        //segment load
                        registers[ra] = segmented_load(C, B, segments);
                } else if (opcode == SSTORE) {
                        //segment store
                        segmented_store(B, C, A, segments);
                } else if (opcode == ADD) {
                        //add instructions
                        registers[ra] = add(B, C);
                } else if (opcode == MUL) {
                        //multiply intructions
                        registers[ra] = multiply(B, C);
                } else if (opcode == DIV) {
                        //divide instructions
                        registers[ra] = divide(B, C);
                } else if (opcode == NAND) {
                        //nand instructions
                        registers[ra] = nand(B, C);
                } else if (opcode == HALT) {
                        //halt instructions
                        halt(segments, IDs);
			return;
                } else if (opcode == ACTIVATE) {
                        //map segments
                        registers[rb] = map_seg(segments, C, IDs);
                } else if (opcode == INACTIVATE) {
                        //assert c!= 0
                        assert(C);
                        //unmap segments
                        unmap_seg(segments, C);
                        uint32_t *ID = malloc(sizeof(uint32_t));
                        *ID = C;
                        Stack_push(IDs, ID);
                } else if (opcode == OUT) {
                        //ouput instructions
                        output(C);
                } else if (opcode == IN) {
                        //input instructions
                        registers[rc] = get_input();
                } else if (opcode == LOADP) {
                        if (B != 0) {
                                //load program
                                segment0 = load_prog(B, segments);
                                unmap_seg(segments, 0);
                                Seq_put(segments, 0, segment0);
                        }
                        i = C - 1;
                } else if (opcode == LV) {
                        registers[getRegister(word, 28)] = load_value(word);
                }
	}
}

Segment init(FILE *input)
{
        //malloc segment0 and words
        Segment segment0 = malloc(sizeof(struct Segment));	
	uint32_t *words = malloc(sizeof(uint32_t) * 10);
	uint32_t size = 0;
        uint32_t capacity = 10;
        //read in word from input
	uint32_t word = readInWord(input);
        //reallocate will eof
	while (word != (unsigned)EOF) {
		if (size >= capacity) {
                        capacity *= 2;
			words = realloc(words, capacity * sizeof(uint32_t));
                }
		words[size] = word;
		size++;
		word = readInWord(input);
	}
	segment0->size = size;
        segment0->words = words;
	return segment0;
}
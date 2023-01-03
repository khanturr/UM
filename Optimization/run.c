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
#include "stack.h"
#include "word.h"

typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;

void run(FILE *input)
{
	Stack IDs = (struct Stack *)malloc(sizeof(struct Stack));
        IDs->size = 0;
        IDs->capacity = 10;
        IDs->stackArr = (uint32_t *)malloc(40);
	Memory segments = (struct Memory *)malloc(sizeof(struct Memory));
        segments->capacity = 10;
        segments->size = 0;
        segments->segArr = (struct Segment **)malloc(10 * sizeof(struct Segment));
	uint32_t registers[8] = {0};
	uint32_t ra, rb, rc, A, B, C, opcode, word;
        Segment seg;
        Segment *mem;
	Segment segment0 = init(input);
        append(segments, segment0);
        uint32_t length = segment0->size;
	for (uint32_t i = 0; i < length; i++) {	
		word = segment0->words[i];
                /* index of registers a,b,c */
                ra = (word << 23) >> 29;
		rb = (word << 26) >> 29;
		rc = (word << 29) >> 29;

                A = registers[ra]; 				
		B = registers[rb];
		C = registers[rc];
         
		opcode = word >> 28;
		assert(opcode <= 13);
                switch (opcode) {
                        case CMOV: 
                                if (C != 0) {
                                        registers[ra] = B;
                                }
                        break;
                        case SLOAD: 
                                seg = (segments->segArr)[B];
                                // assert(seg);
                                // assert(C < seg->size);
                                registers[ra] = seg->words[C];
                        break;
                        case SSTORE: 
                                mem = segments->segArr;
                                /* assering that segment is not NULL*/
                                // assert(mem[A]);
                                // /* asserting that the index is a valid index */
                                // assert(B < mem[A]->size);
                                (mem[A])->words[B] = C;	
                        break;
                        case ADD: registers[ra] = B + C;
                        break;
                        case MUL: registers[ra] = B * C;
                        break;
                        case DIV: registers[ra] = B / C;
                        break;
                        case NAND: registers[ra] = ~(B & C);
                        break;
                        case HALT: halt(segments, IDs);
                                   return;
                        break;
                        case ACTIVATE:
                                /* allocating memory for struct segment */
                                seg = malloc(sizeof(struct Segment));
                                /* allocating memory for the segment of words */
                                seg->words = calloc(C, 4);
                                seg->size = C;
                                uint32_t ID;
                                mem = segments->segArr;
                                /* checking if a new ID needs to me made */
                                if (IDs->size == 0) {
                                        ID = append(segments, seg);
                                /* case when ID can be recycled from stack of IDs */
                                } else {
                                        ID = pop(IDs);
                                        //fprintf(stderr, "ID: %u\n", ID);
                                        mem[ID] = seg;
                                }
                                /* return id of mapped segment */
                                registers[rb] = ID;
                        break;
                        case INACTIVATE:
                                        seg = (segments->segArr)[C];
                                        /* free memory */
                                        free(seg->words);
                                        free(seg);
                                        (segments->segArr)[C] = NULL;
                                        push(IDs, C);
                        break;
                        case OUT:
                                assert(C <= 255);
                                putchar(C);
                        break;
                        case IN: registers[rc] = (uint32_t)getchar();
                        break;
                        case LOADP: if (B) {
                                        /* load program */
                                        segment0 = load_prog(B, segments);
                                        unmap(segments, 0);
                                        (segments->segArr)[0] = segment0;
                                        length = segment0->size;
                                    }
                                    i = C - 1;
                        break;
                        case LV: registers[(word << 4) >> 29] = (word << 7) >> 7;
                        break;
                }
	}
}

Segment init(FILE *input)
{
        /* malloc segment0 and words */
        Segment segment0 = malloc(sizeof(struct Segment));	
	uint32_t *words = malloc(sizeof(uint32_t) * 10);
	uint32_t size = 0;
        uint32_t capacity = 10;
        /* read in word from input */
	uint32_t word = readInWord(input);
        uint32_t *wordsNew;
        /* reading in until EOF */
	while (word != (unsigned)EOF) {
		if (size >= capacity) {
                        capacity *= 2;
			wordsNew = realloc(words, capacity * sizeof(uint32_t));
                        assert(wordsNew);
                        words = wordsNew;
                }
		words[size] = word;
		size++;
		word = readInWord(input);
	}
	segment0->size = size;
        segment0->words = words;
	return segment0;
}
/*
 * umlab.c
 *
 * Functions to generate UM unit tests. Once complete, this module
 * should be augmented and then linked against umlabwrite.c to produce
 * a unit test writing program.
 *  
 * A unit test is a stream of UM instructions, represented as a Hanson
 * Seq_T of 32-bit words adhering to the UM's instruction format.  
 * 
 * Any additional functions and unit tests written for the lab go
 * here. 
 *  
 */


#include <stdint.h>
#include <stdio.h>
#include <assert.h>
#include <seq.h>
#include "bitpack.h"


typedef uint32_t Um_instruction;
typedef enum Um_opcode {
        CMOV = 0, SLOAD, SSTORE, ADD, MUL, DIV,
        NAND, HALT, ACTIVATE, INACTIVATE, OUT, IN, LOADP, LV
} Um_opcode;


/* Functions that return the two instruction types */

Um_instruction three_register(Um_opcode op, int ra, int rb, int rc)
{
        Um_instruction instruction = 0;
        instruction = Bitpack_newu(instruction, 4, 28, op);
        instruction = Bitpack_newu(instruction, 3, 6, ra);
        instruction = Bitpack_newu(instruction, 3, 3, rb);
        instruction = Bitpack_newu(instruction, 3, 0, rc);
        return instruction;
}
Um_instruction loadval(unsigned ra, unsigned val)
{
        Um_instruction instruction = 0;
        Um_opcode op = LV;
        instruction = Bitpack_newu(instruction, 4, 28, op);
        instruction = Bitpack_newu(instruction, 3, 25, ra);
        instruction = Bitpack_newu(instruction, 25, 0, val);
        return instruction;
}


/* Wrapper functions for each of the instructions */

static inline Um_instruction halt(void) 
{
        return three_register(HALT, 0, 0, 0);
}

typedef enum Um_register { r0 = 0, r1, r2, r3, r4, r5, r6, r7 } Um_register;

static inline Um_instruction add(Um_register a, Um_register b, Um_register c) 
{
        return three_register(ADD, a, b, c);
}
static inline Um_instruction mul(Um_register a, Um_register b, Um_register c) 
{
        return three_register(MUL, a, b, c);
}
static inline Um_instruction div(Um_register a, Um_register b, Um_register c) 
{
        return three_register(DIV, a, b, c);
}
static inline Um_instruction cmov(Um_register a, Um_register b, Um_register c) 
{
        return three_register(CMOV, a, b, c);
}
static inline Um_instruction nand(Um_register a, Um_register b, Um_register c) 
{
        return three_register(NAND, a, b, c);
}
static inline Um_instruction map(Um_register b, Um_register c) 
{
        return three_register(ACTIVATE, 0, b, c);
}
static inline Um_instruction unmap(Um_register c) 
{
        return three_register(INACTIVATE, 0, 0, c);
}
static inline Um_instruction segLoad(Um_register a, Um_register b, 
                                     Um_register c) 
{
        return three_register(SLOAD, a, b, c);
}
static inline Um_instruction segStore(Um_register a, Um_register b, 
                                      Um_register c) 
{
        return three_register(SSTORE, a, b, c);
}
static inline Um_instruction loadProg(Um_register b, Um_register c) 
{
        return three_register(LOADP, 0, b, c);
}
static inline Um_instruction input(Um_register c) 
{
        return three_register(IN, 0, 0, c);
}
static inline Um_instruction output(Um_register c)
{
        return three_register(OUT, 0, 0, c);
}

/* Functions for working with streams */

static inline void append(Seq_T stream, Um_instruction inst)
{
        assert(sizeof(inst) <= sizeof(uintptr_t));
        Seq_addhi(stream, (void *)(uintptr_t)inst);
}

const uint32_t Um_word_width = 32;

void Um_write_sequence(FILE *output, Seq_T stream)
{
        assert(output != NULL && stream != NULL);
        int stream_length = Seq_length(stream);
        for (int i = 0; i < stream_length; i++) {
                Um_instruction inst = (uintptr_t)Seq_remlo(stream);
                for (int lsb = Um_word_width - 8; lsb >= 0; lsb -= 8) {
                        fputc(Bitpack_getu(inst, 8, lsb), output);
                }
        }
}
      



/* Unit tests for the UM */

void build_halt_test(Seq_T stream)
{
        append(stream, halt());
}

void build_verbose_halt_test(Seq_T stream)
{
        append(stream, halt());
        append(stream, loadval(r1, 'B'));
        append(stream, output(r1));
        append(stream, loadval(r1, 'a'));
        append(stream, output(r1));
        append(stream, loadval(r1, 'd'));
        append(stream, output(r1));
        append(stream, loadval(r1, '!'));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
}

void build_add_test(Seq_T stream)
{
        append(stream, loadval(r2, 97));
        append(stream, loadval(r3, 1));
        append(stream, add(r1, r2, r3));
        /* expected output is 'b' */
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        append(stream, halt());
}
void build_multiply_test(Seq_T stream)
{
        /* standard case */
        append(stream, loadval(r2, 40));
        append(stream, loadval(r3, 3));
        append(stream, mul(r1, r2, r3));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        /* expected output is 'x' */
        append(stream, halt());
}
void build_divide_test(Seq_T stream)
{
        /* standard case */
        append(stream, loadval(r2, 194));
        append(stream, loadval(r3, 2));
        append(stream, div(r1, r2, r3));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        /* expected output is 'a' */
        append(stream, halt());
}
void build_divide0_test(Seq_T stream)
{
        /* standard case */
        append(stream, loadval(r2, 194));
        append(stream, loadval(r3, 0));
        append(stream, div(r1, r2, r3));
        /* there should be exception */
        append(stream, halt());
}
void build_conditional_move_test(Seq_T stream)
{
        /* case C == 0 */
        append(stream, loadval(r3, 0));
        append(stream, loadval(r1, 'f'));
        append(stream, loadval(r2, 't'));
        append(stream, cmov(r1, r2, r3));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        /* expected output to be 'f' */
        /* case C == 1 */
        append(stream, loadval(r3, 1));
        append(stream, loadval(r1, 'f'));
        append(stream, loadval(r2, 't'));
        append(stream, cmov(r1, r2, r3));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        /* expected output to be 't' */
        /* case C == 2 */
        append(stream, loadval(r3, 2));
        append(stream, loadval(r1, 'f'));
        append(stream, loadval(r2, 't'));
        append(stream, cmov(r1, r2, r3));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        /* expected output to be 't' */
        append(stream, halt());
}

void build_map_unmap_store_load_test(Seq_T stream)
{
        /* standard case */

        /* mapping */
        append(stream, loadval(r2, 1));
        append(stream, loadval(r3, 10));
        append(stream, map(r2, r3));
        /* putting 'c' into m[1][5] */
        append(stream, loadval(r1, 1));
        append(stream, loadval(r2, 5));
        append(stream, loadval(r3, 'c'));
        append(stream, segStore(r1, r2, r3));
        /* getting value from m[1][5] */
        append(stream, loadval(r2, 1));
        append(stream, loadval(r3, 5));
        append(stream, segLoad(r1, r2, r3));
        append(stream, output(r1));
        /* printing endline */
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        /* expected output to be 'c' */
        /* testing unmapping and ID recycling */
        append(stream, loadval(r3, 1));
        append(stream, unmap(r3));
        append(stream, loadval(r2, 1));
        append(stream, loadval(r3, 10));
        append(stream, map(r2, r3));
        append(stream, loadval(r1, 1));
        append(stream, loadval(r2, 5));
        append(stream, loadval(r3, 'e'));
        append(stream, segStore(r1, r2, r3));
        append(stream, loadval(r2, 1));
        append(stream, loadval(r3, 5));
        append(stream, segLoad(r1, r2, r3));
        append(stream, output(r1));
        append(stream, loadval(r1, '\n'));
        append(stream, output(r1));
        /* expected output to be 'e' */
        append(stream, halt());
}
void build_load_prog_test(Seq_T stream)
{
        append(stream, loadval(r1, 3));   
        append(stream, loadval(r2, 103)); 
        append(stream, loadval(r1, 6));
        append(stream, loadProg(0, r1));      
        append(stream, loadval(r1, 2));    
        append(stream, loadval(r2, 102));  
        append(stream, output(r2));       
        append(stream, loadval(r1,'\n')); 
        append(stream, output(r1));      
        append(stream, halt());           
}
void build_input_test(Seq_T stream)
{
        append(stream, input(r3));
        append(stream, output(r3));
        append(stream, loadval(r1,'\n')); 
        append(stream, output(r1)); 
        append(stream, halt());
}

void print_a_digit(Seq_T stream)
{
        append(stream, loadval(r1, 48));
        append(stream, loadval(r2, 6));
        append(stream, add(r1, r2, r3));
        append(stream, output(r3));
        append(stream, halt());
}

void build_nand_test(Seq_T stream)
{
        append(stream, loadval(r2, 10));
        append(stream, loadval(r3, 21));
        append(stream, nand(r1, r3, r2));
        append(stream, loadval(r4, 10));
        append(stream, loadval(r5, 21));
        append(stream, nand(r6, r4, r5));
        append(stream, nand(r7, r6, r1));
        append(stream, output(r7));
        append(stream, halt());
}

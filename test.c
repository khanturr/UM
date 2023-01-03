/**************************************************************
 *
 *                     test.c
 *
 *     Assignment: um
 *     Authors:  Brandon Shih (bshih01),  Hunter Purevbayar (hpurev01)
 *     Date:     11/23/2022
 *
 *     Summary: Testing functions for universal machine
 *
 *     
 *
 **************************************************************/
#include "seq.h"
#include "stack.h"
#include "segment.h"
#include "word.h"
#include "assert.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/* Testing mapping and unmapping functions */
        // int main()
        // {
        //         /* testing appending to sequence */
        //         Seq_T segments = Seq_new(10);
        //         Stack_T IDs = Stack_new();
        //         map(segments, IDs, 10);
        //         assert(Seq_length(segments) == 1);

        //         /* testing correct value after append */
        //         Segment seg = Seq_get(segments, 0);
        //         uint32_t *words = seg->words;
        //         assert(words[0] == 0);
        //         assert(words[9] == 0);

        //         /* testing unmapping and adding to the stack of used IDs */
        //         unmap(segments, IDs, 0);
        //         seg = Seq_get(segments, 0);
        //         assert(seg == NULL);
        //         uint32_t id = *(uint32_t *)Stack_pop(IDs);
        //         assert(id == 0);
        //         Stack_push(IDs, &id);

        //         /* testing recycling old IDs */
        //         map(segments, IDs, 5);
        //         assert(Seq_length(segments) == 1);
        //         assert(Stack_empty(IDs));
        //         assert(words[0] == 0);
        //         assert(words[4] == 0);
        //         return 0;
        // }

/* Testing getWord and storeWord (load value and store value) in tandem */
        // int main()
        // {
        //         /* testing get word and store word at the same time */
        //         Seq_T segments = Seq_new(10);
        //         Stack_T IDs = Stack_new();
        //         map(segments, IDs, 10);
        //         uint32_t newWord = 12;
        //         storeWord(segments, newWord, 0, 7);
        //         assert(getWord(segments, 0, 7) == 12);
        //         return 0;
        // }

/* Testing getRegisters from word module */
        // int main()
        // {
        //         /* testing the get functions */
        //         uint32_t word = 2684355013;
        //         assert(getOpcode(word) == 10);
        //         assert(getRegister(word, 0) == 5);
        //         assert(getRegister(word, 3) == 0);
        //         assert(getRegister(word, 6) == 7);
        //         return 0;
        // }

/* Testing reading in the words from stdin */
        // int main()
        // {
        //         uint32_t word = readInWord();
        //         /* a = 'a' */
        //         /* b = 'b' */
        //         /* c = 'c' */
        //         /* d = 'd' */
        //         /* 01100001 01100010 01100011 01100100 */
        //         assert(word == 1633837924);
        //         return 0;
        // }
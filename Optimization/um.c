/**************************************************************
 *
 *                  um.c
 *
 *     Assignment: um
 *     Authors:  Brandon Shih (bshih01),  Hunter Purevbayar (hpurev01)
 *     Date:     11/23/2022
 *
 *     Summary: Main file for universal machine
 *
 *     
 *
 **************************************************************/
#include <stdlib.h>
#include <stdio.h>
#include "run.h"


int main(int argc, char *argv[])
{
        if (argc < 2) {
                fprintf(stderr, "Usage: ./um prog.um\n");
                return EXIT_FAILURE;
        }
        FILE *input = fopen(argv[1], "rb");
        if (!input) {
                fprintf(stderr, "Filename is invalid.\n");
                return EXIT_FAILURE;
        }
        run(input);
        fclose(input);
        return 0;
}
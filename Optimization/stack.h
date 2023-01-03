#ifndef STACK_H
#define STACK_H

#include <stdlib.h>
#include <stdint.h>

typedef struct Stack {
        uint32_t size;
        uint32_t capacity;
	uint32_t *stackArr;
} *Stack;

void push(Stack stack, uint32_t elem);
uint32_t pop(Stack stack);

#endif
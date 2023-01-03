#include "stack.h"
#include "assert.h"
#include <stdint.h>
#include <stdlib.h>

void push(Stack stack, uint32_t elem)
{
        uint32_t size = stack->size;
        uint32_t cap = stack->capacity;
        uint32_t *stackArr = stack->stackArr;
        uint32_t *stackArrNew;
        if (size >= cap) {
                cap *= 2;
                stackArrNew = realloc(stackArr, cap * 4);
                assert(stackArrNew);
                stackArr = stackArrNew;
        }
        stackArr[size] = elem;
        stack->size++;
        stack->capacity = cap;
        stack->stackArr = stackArr;
}
uint32_t pop(Stack stack)
{
        return stack->stackArr[--stack->size];
}
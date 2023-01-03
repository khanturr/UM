#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>
#include "segment.h"
#include "memory.h"
#include "assert.h"

uint32_t append(Memory segments, Segment segment)
{
        assert(segments);
        assert(segment);
        uint32_t size = segments->size;
        uint32_t cap = segments->capacity;
        Segment *memory = segments->segArr;
        Segment *memoryNew;
        if (size >= cap) {
                cap *= 2;
                memoryNew = realloc(memory, cap * sizeof(struct Segment));
                assert(memoryNew);
                memory = memoryNew;
        }
        memory[size] = segment;
        segments->size++;
        segments->capacity = cap;
        segments->segArr = memory;
        return size;
}
#ifndef MEMORY_H
#define MEMORY_H

#include <stdlib.h>
#include <stdint.h>
#include "segment.h"

typedef struct Segment {
	uint32_t size;
	uint32_t *words;
} *Segment;

typedef struct Memory {
	uint32_t size;
        uint32_t capacity;
	Segment *segArr;
} *Memory;

uint32_t append(Memory segments, Segment segment);

#endif
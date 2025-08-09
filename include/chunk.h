#pragma once

#include "common.h"
#include "value.h"
#include <stdint.h>

typedef enum {
  OP_CONSTANT,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_DIV,
  OP_NEG,
  OP_RETURN,
} OpCode;

typedef struct {
  int count;
  int capacity;
  uint8_t *code;
  int *lines;
  ValueArray constants;
} Chunk;

void initChunk(Chunk *chunk);

void writeChunk(Chunk *chunk, uint8_t byte, int lineNumber);

void freeChunk(Chunk *chunk);

int addConstant(Chunk *chunk, Value constant);

#pragma once

#include "common.h"
#include "value.h"
#include <stdint.h>

typedef enum {
  OP_CONSTANT,
  OP_NIL,
  OP_TRUE,
  OP_FALSE,
  OP_ADD,
  OP_SUB,
  OP_MUL,
  OP_PRINT,
  OP_DIV,
  OP_POP,
  OP_DEFINE_GLOBAL,
  OP_GET_LOCAL,
  OP_SET_LOCAL,
  OP_GET_GLOBAL,
  OP_SET_GLOBAL,
  OP_NEG,
  OP_NOT,
  OP_EQUAL,
  OP_GREATER,
  OP_LESSER,
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

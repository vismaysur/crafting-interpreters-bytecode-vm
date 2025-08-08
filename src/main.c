#include "chunk.h"
#include "common.h"
#include "debug.h"

int main(int argc, const char *argv[]) {
  Chunk chunk;

  initChunk(&chunk);

  // A single instruction contains an opcode and operand(s).
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 5);
  writeChunk(&chunk, constant, 5);

  writeChunk(&chunk, OP_RETURN, 5);

  disassembleChunk(&chunk, "Test Chunk");

  freeChunk(&chunk);

  return 0;
}

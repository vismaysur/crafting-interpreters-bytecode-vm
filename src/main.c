#include "chunk.h"
#include "common.h"
#include "debug.h"

int main(int argc, const char *argv[]) {
  Chunk chunk;

  initChunk(&chunk);

  // A single instruction contains an opcode and operand(s).
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT);
  writeChunk(&chunk, constant);

  writeChunk(&chunk, OP_RETURN);

  disassembleChunk(&chunk, "Test Chunk");

  freeChunk(&chunk);

  return 0;
}

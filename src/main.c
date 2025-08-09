#include "chunk.h"
#include "common.h"
#include "debug.h"
#include "vm.h"

int main(int argc, const char *argv[]) {
  // Init
  Chunk chunk;
  initChunk(&chunk);
  initVM();

  // A single instruction contains an opcode and operand(s).
  int constant = addConstant(&chunk, 1.2);
  writeChunk(&chunk, OP_CONSTANT, 5);
  writeChunk(&chunk, constant, 5);

  constant = addConstant(&chunk, 3.4);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_ADD, 123);

  constant = addConstant(&chunk, 5.6);
  writeChunk(&chunk, OP_CONSTANT, 123);
  writeChunk(&chunk, constant, 123);

  writeChunk(&chunk, OP_DIV, 123);
  writeChunk(&chunk, OP_NEG, 123);

  // Next instruction
  writeChunk(&chunk, OP_RETURN, 5);

  // run VM!
  interpret(&chunk);

  // Clean up
  freeVM();
  freeChunk(&chunk);

  return 0;
}

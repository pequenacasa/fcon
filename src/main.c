#include "cola.h"

int main() {

  COLA_Context *ctx = COLA_CreateContext(3);

  COLA_LoadFile(ctx, "samples/a.txt", 0);
  COLA_LoadContent(ctx, "-", 1);
  COLA_LoadFile(ctx, "samples/b.txt", 2);
  COLA_Compile(ctx, "samples/fizzbuzz.txt");
  COLA_Free(ctx);

  return 0;
}

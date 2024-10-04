#include "src/fcon.h"

int main() {
  FCON_Context *ctx = FCON_CreateContext(2);

  FCON_LoadContent(ctx, "samples/a.txt", 0);
  FCON_LoadContent(ctx, "samples/b.txt", 1);
  FCON_Conpile(ctx, "samples/fizzbuzz.txt");
  FCON_FreeContext(ctx);

  return 0;
}

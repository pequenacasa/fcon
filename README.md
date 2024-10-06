# cola (glue in english)

It is a small library for concatenating file contents.

### How to use:
``` c
  COLA_Context *ctx = COLA_CreateContext(3);

  COLA_LoadFile(ctx, "samples/a.txt", 0);
  COLA_LoadContent(ctx, "-", 1);
  COLA_LoadFile(ctx, "samples/b.txt", 2);

  // Will create another file in folder samples and your content will be "fizz-buzz"
  COLA_Compile(ctx, "samples/fizzbuzz.txt");

  // Philosophy: malloc once, free once. XD
  COLA_Free(ctx);
```

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cola.h"

COLA_Context *COLA_CreateContext(const int max_content_buffers) {
  COLA_Context *ctx = malloc(sizeof(COLA_Context));
  if (ctx == NULL) {
    // TODO: warning
    return ctx;
  }

  ctx->contents = malloc(sizeof(COLA_ContentBuffer) * max_content_buffers);
  if (ctx == NULL) {
    // TODO: warning
    return ctx;
  }

  ctx->content_count = max_content_buffers;
  for (int i = 0; i < max_content_buffers; i++) {
    ctx->contents[i].content_loaded = 0;
  }

  return ctx;
}

int COLA_LoadContent(COLA_Context *ctx, const char *content, const int index) {
  COLA_ContentBuffer *c = (ctx->contents + index);
  char *buffer;
  int size = sizeof(content);

  buffer = malloc(size);
  if (buffer == NULL) {
    // TODO: warning
    return 1;
  }

  strcpy(buffer, content);
  c->content = buffer;
  c->content_loaded = 1;

  return 0;
}

int COLA_LoadFile(COLA_Context *ctx, const char *filepath, const int index) {
  COLA_ContentBuffer *c = (ctx->contents + index);
  FILE *f = fopen(filepath, "r");
  if (f == NULL) {
    // TODO: warning
    return 1;
  }

  char *buffer;
  int size;

  fseek(f, 0, SEEK_END);
  size = ftell(f);
  rewind(f);

  buffer = malloc(size);
  if (buffer == NULL) {
    // TODO: warning
    return 1;
  }

  fread(buffer, 1, size, f);

  c->content = buffer;
  c->content_loaded = 1;

  fclose(f);
  return 0;
}

int COLA_Compile(COLA_Context *ctx, const char *filepath) {
  FILE *f = fopen(filepath, "w");
  if (f == NULL) {
    // TODO: warning
    return 1;
  }

  int buffer_empty = 0;
  for (int i = 0; i < ctx->content_count; i++) {
    if (!ctx->contents[i].content_loaded) {
      buffer_empty = i;
      continue;
    }

    fprintf(f, "%s", ctx->contents[i].content);
  }

  if (buffer_empty > 0) {
    // TODO: warning
    return 1;
  }

  fclose(f);
  return 0;
}

void COLA_UnloadContent(COLA_Context *ctx, const int index) {
  COLA_ContentBuffer *c = (ctx->contents + index);
  free(c->content);
  c->content_loaded = 0;
}

void COLA_Free(COLA_Context *ctx) {
  for (int i = 0; i < ctx->content_count; i++) {
    if (ctx->contents[i].content_loaded) {
      free(ctx->contents[i].content);
    }
  }

  free(ctx->contents);
  free(ctx);
}

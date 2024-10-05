
#include "fcon.h"
#include <stdio.h>
#include <stdlib.h>

#define ERROR_LABEL "ERROR: "
#define WARNING_LABEL "WARNING: "

FCON_Context *FCON_CreateContext(const int content_count) {
  FCON_Context *ctx = malloc(sizeof(FCON_Context));
  if (ctx == NULL) {
    printf("%s%s\n", ERROR_LABEL, "cannot create context");
    return NULL;
  }

  ctx->file_contents = malloc(sizeof(FCON_FileContent) * content_count);
  ctx->content_count = content_count;

  for (int i = 0; i < content_count; i++) {
    ctx->file_contents[i].content_loaded = 0;
  }

  return ctx;
}

void FCON_FreeContext(FCON_Context *ctx) {

  for (int i = 0; i < ctx->content_count; i++) {
    if (ctx->file_contents[i].content_loaded) {
      free(ctx->file_contents[i].content);
    }
  }

  free(ctx->file_contents);
  free(ctx);
}

void FCON_LoadContent(FCON_Context *ctx, const char *filename,
                      const int index) {
  FILE *f = fopen(filename, "r");

  if (f == NULL) {
    printf("%s%s (%s)\n", ERROR_LABEL, "cannot load file content", filename);
    return;
  }

  char *content;
  int size;

  fseek(f, 0, SEEK_END);
  size = ftell(f);
  rewind(f);

  content = malloc(size);
  if (content == NULL) {
    printf("%s%s\n", ERROR_LABEL, "cannot make content buffer");
    fclose(f);
    return;
  }

  fread(content, 1, size, f);

  ctx->file_contents[index].content = content;
  ctx->file_contents[index].content_loaded = 1;

  fclose(f);
}

void FCON_UnloadContent(FCON_Context *ctx, const int index) {
  free(ctx->file_contents[index].content);
  ctx->file_contents[index].content = 0;
}

void FCON_Conpile(FCON_Context *ctx, const char *filename) {
  FILE *f = fopen(filename, "w");
  int buffer_empty = -1;

  for (int i = 0; i < ctx->content_count; i++) {
    if (!ctx->file_contents[i].content_loaded) {
      buffer_empty = 1;
      continue;
    }

    fprintf(f, "%s", ctx->file_contents[i].content);
  }

  if (buffer_empty >= 0) {
    printf("%s%s; index[%d]\n", WARNING_LABEL, "some content buffer are empty",
           buffer_empty);
  }

  fclose(f);
}


typedef struct {
  char *content;
  int content_loaded;
} COLA_ContentBuffer;

typedef struct {
  COLA_ContentBuffer *contents;
  int content_count;
} COLA_Context;

COLA_Context *COLA_CreateContext(const int max_content_buffers);
int COLA_LoadContent(COLA_Context *ctx, const char *content, const int index);
int COLA_LoadFile(COLA_Context *ctx, const char *filepath, const int index);
int COLA_UnloadContent(COLA_Context *ctx, const int index);
int COLA_Compile(COLA_Context *ctx, const char *filepath);
void COLA_Free(COLA_Context *ctx);

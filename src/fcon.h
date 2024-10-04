
typedef struct {
  char *content;
  char content_loaded;
} FCON_FileContent;

typedef struct {
  FCON_FileContent *file_contents;
  int content_count;
} FCON_Context;

FCON_Context *FCON_CreateContext(const int content_count);
void FCON_FreeContext(FCON_Context *ctx);
void FCON_LoadContent(FCON_Context *ctx, const char *filename, const int index);
void FCON_UnloadContent(FCON_Context *ctx, const int index);
void FCON_Conpile(FCON_Context *ctx, const char *filename);

typedef struct TextBuffer TextBuffer;

TextBuffer *tb_new();
void tb_free(TextBuffer *tb);
void tb_debug(TextBuffer *tb);
void tb_read_from_file(TextBuffer *tb, char *path);
void tb_write_to_file(TextBuffer *tb, char *path);

#include <stdio.h>
#include <stdlib.h>

typedef struct TextBuffer TextBuffer;

TextBuffer *tb_new();
void tb_free(TextBuffer *tb);
void tb_debug(TextBuffer *tb);

void tb_load_file(TextBuffer *tb, char *path);
void tb_save_file(TextBuffer *tb, char *path);

size_t tb_length(TextBuffer *tb);
void tb_insert(TextBuffer *tb, size_t idx, char *str);
void tb_insert_ch(TextBuffer *tb, size_t idx, char ch);
void tb_remove(TextBuffer *tb, size_t start, size_t end);
void tb_remove_ch(TextBuffer *tb, size_t idx);

size_t tb_find(TextBuffer *tb, char *str);
size_t tb_findr(TextBuffer *tb, char *str);
size_t tb_find_ch(TextBuffer *tb, char ch);
size_t tb_findr_ch(TextBuffer *tb, char ch);

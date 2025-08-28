#include "text_buffer.h"
#include <stdlib.h>
#include <stdio.h>

struct TextBuffer {
    char *data;
};

TextBuffer *tb_new()
{
    TextBuffer *tb = malloc(sizeof(TextBuffer));

    tb->data = "Hello, World!\n";

    return tb;
}

void tb_free(TextBuffer *tb)
{
    free(tb);
}

void tb_debug(TextBuffer *tb)
{
    printf("%s", tb->data);
}

void tb_read_from_file(TextBuffer *tb, char *path)
{
    fprintf(stderr, "TODO: implement tb_read_from_file");
    exit(1);
}

void tb_write_to_file(TextBuffer *tb, char *path)
{
    fprintf(stderr, "TODO: implement tb_write_to_file");
    exit(1);
}

#include "text_buffer.h"

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

void tb_load_file(TextBuffer *tb, char *path)
{
    fprintf(stderr, "TODO: implement tb_read_from_file");
    exit(1);
}

void tb_save_file(TextBuffer *tb, char *path)
{
    fprintf(stderr, "TODO: implement tb_write_to_file");
    exit(1);
}

size_t tb_length(TextBuffer *tb)
{
    fprintf(stderr, "TODO: implement tb_length");
    exit(1);
}

void tb_insert(TextBuffer *tb, size_t idx, char *str)
{
    fprintf(stderr, "TODO: implement tb_insert");
    exit(1);
}

void tb_insert_ch(TextBuffer *tb, size_t idx, char ch)
{
    fprintf(stderr, "TODO: implement tb_insert_ch");
    exit(1);
}

void tb_remove(TextBuffer *tb, size_t start, size_t end)
{
    fprintf(stderr, "TODO: implement tb_remove");
    exit(1);
}

void tb_remove_ch(TextBuffer *tb, size_t idx)
{
    fprintf(stderr, "TODO: implement tb_remove_ch");
    exit(1);
}

size_t tb_find(TextBuffer *tb, char *str)
{
    fprintf(stderr, "TODO: implement tb_find");
    exit(1);
	return 0;
}

size_t tb_findr(TextBuffer *tb, char *str)
{
    fprintf(stderr, "TODO: implement tb_findr");
    exit(1);
	return 0;
}

size_t tb_find_ch(TextBuffer *tb, char ch)
{
    fprintf(stderr, "TODO: implement tb_find_ch");
    exit(1);
	return 0;
}

size_t tb_findr_ch(TextBuffer *tb, char ch)
{
    fprintf(stderr, "TODO: implement tb_findr_ch");
    exit(1);
	return 0;
}


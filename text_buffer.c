#include "text_buffer.h"
#include <string.h>
#include <unistd.h>

#define TB_INIT_CAPACITY 16
#define TB_GROWTH_RATE 2

struct TextBuffer {
    char *data;
    size_t size;
    size_t gap_start;           // First empty char
    size_t gap_end;             // First occupied char
};

void tb_move_gap(TextBuffer *tb, size_t idx) {
    if (idx < tb->gap_start) {
        size_t moved = tb->gap_start - idx;
        memmove(tb->data + tb->gap_end -
            moved, tb->data + idx, moved);
        tb->gap_start -= moved;
        tb->gap_end -= moved;
    } else {
        size_t moved = idx - tb->gap_start;
        memmove(tb->data +
            tb->gap_start, tb->data + tb->gap_end, moved);
        tb->gap_start += moved;
        tb->gap_end += moved;
    }
}

void tb_reserve(TextBuffer *tb, size_t additional) {
    if (additional > tb->gap_end - tb->gap_start) {
        size_t old_end = tb->gap_end;

        while (additional > tb->gap_end - tb->gap_start) {
            if (tb->size == 0) {
                tb->gap_end = TB_INIT_CAPACITY;
                tb->size = TB_INIT_CAPACITY;
            } else {
                tb->gap_end += tb->size;
                tb->size *= TB_GROWTH_RATE;
            }
        }

        tb->data = realloc(tb->data, tb->size);
        memmove(tb->data + tb->gap_end,
            tb->data + old_end, tb->size - tb->gap_end);
    }
}

TextBuffer *tb_new() {
    TextBuffer *tb = malloc(sizeof(TextBuffer));
   	tb->data = NULL;
    tb->size = 0;
    tb->gap_start = 0;
    tb->gap_end = 0;
    return tb;
}

void tb_free(TextBuffer *tb) {
	free(tb->data);
    free(tb);
}

void tb_debug(TextBuffer *tb) {
    for (size_t i = 0; i < tb->size; i++) {
        if (i < tb->gap_start || i >= tb->gap_end) {
            printf("%c", tb->data[i]);
        } else {
            printf("-");
        }
    }
    printf("\n");
}

size_t tb_length(TextBuffer *tb) {
    return tb->size - (tb->gap_end - tb->gap_start);
}

char tb_get(TextBuffer *tb, size_t idx) {
    if (idx >= tb_length(tb)) {
        exit(1);
    } else if (idx < tb->gap_start) {
        return tb->data[idx];
    } else {
        return tb->data[idx + tb->gap_end - tb->gap_start];
    }
}

void tb_load_file(TextBuffer *tb, char *path) {
    char *line = NULL;
    size_t size = 0;

    FILE *fd = fopen(path, "r");
    if (fd == NULL) {
        return;
    }

    while (getline(&line, &size, fd) != -1) {
        tb_insert(tb, tb_length(tb), line);
    }

    free(line);
    fclose(fd);
}

void tb_save_file(TextBuffer *tb, char *path) {
	FILE *fd = fopen(path, "w+");

    for (size_t i = 0; i < tb_length(tb); i++) {
        fputc(tb_get(tb, i), fd);
    }

    fclose(fd);
}

void tb_insert(TextBuffer *tb, size_t idx, char *str) {
    size_t len = strlen(str);
    tb_move_gap(tb, idx);
    tb_reserve(tb, len);
    memcpy(tb->data + tb->gap_start, str, len);
    tb->gap_start += len;
}

void tb_insert_ch(TextBuffer *tb, size_t idx, char ch) {
    tb_move_gap(tb, idx);
    tb_reserve(tb, 1);
    tb->data[tb->gap_start++] = ch;
}

void tb_remove(TextBuffer *tb, size_t start, size_t end) {
    if (end < tb_length(tb)) {
        tb_move_gap(tb, end);
        tb->gap_start -= end - start;
    }
}

void tb_remove_ch(TextBuffer *tb, size_t idx) {
    if (idx < tb_length(tb)) {
        tb_move_gap(tb, idx);
        tb->gap_start--;
    }
}

bool tb_find(TextBuffer *tb, size_t *idx, char *str) {
	size_t len = strlen(str);
	size_t i = *idx;

	if (len == 0) {
		return true;
	}

	while (tb_find_ch(tb, &i, str[0])) {
		size_t j = 1;

		while (j < len && str[j] == tb_get(tb, i + j)) {
			j++;
		}

		if (j == len) {
			*idx = i;
			return true;
		}
	}

	return false;
}

bool tb_findr(TextBuffer *tb, size_t *idx, char *str) {
	size_t len = strlen(str);
	size_t i = *idx;

	if (len == 0) {
		return true;
	}

	while (tb_findr_ch(tb, &i, str[len - 1])) {
		int j = len - 2;

		while (j > 0 && str[j] == tb_get(tb, i - j)) {
			j--;
		}

		if (j == 0) {
			*idx = i - len;
			return true;
		}
	}

	return false;
}

bool tb_find_ch(TextBuffer *tb, size_t *idx, char ch) {
	for (size_t i = *idx + 1; i < tb_length(tb); i++) {
		if (tb_get(tb, i) == ch) {
			*idx = i;
			return true;
		}
	}

	return false;
}

bool tb_findr_ch(TextBuffer *tb, size_t *idx, char ch) {
	for (int i = *idx - 1; i >= 0; i--) {
		if (tb_get(tb, i) == ch) {
			*idx = i;
			return true;
		}
	}

	return false;
}

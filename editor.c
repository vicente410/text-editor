#include <stdarg.h>
#include <stdio.h>
#include "text_buffer.h"
#include "user_interface.h"
#include "custom.h"

struct {
    TextBuffer *tb;
    Mode mode;
    char msg[50];
    size_t cursor;
    size_t draw_off, col_off;
} editor;

void ed_set_mode(Mode mode) {
    editor.mode = mode;
}

void ed_message(const char *fmt, ...) {
    va_list args;
    va_start(args, fmt);
    vsnprintf(editor.msg, sizeof(editor.msg), fmt, args);
    va_end(args);
}

void ed_process_key(Key key) {
    for (size_t i = 0; i < num_binds; i++) {
        if (editor.mode == keybinds[i].mode &&
            key == keybinds[i].key) {
            keybinds[i].function();
        }
    }
}

void ed_render() {
    size_t x = 0, y = 0;
    size_t i = editor.draw_off + editor.col_off;

    while (i < tb_length(editor.tb) && y < ui_rows() - 1) {
        char ch = tb_get(editor.tb, i);

        if (i == editor.cursor) {
            ui_set_cursor(y, x);
        }

        if (ch == '\n' || x == ui_cols() - 1) {
            if (x < ui_cols() - 1) {
                ui_draw("\n\r");
            }
            x = 0;
            y++;
            i += editor.col_off;
        } else {
            ui_draw_ch(ch);
            x++;
        }

        i++;
    }

    ui_draw(editor.msg);
}

void ed_next_char() {
    if (editor.cursor < tb_length(editor.tb)) {
        editor.cursor++;
    }
}

void ed_prev_char() {
    if (editor.cursor > 0) {
        editor.cursor--;
    }
}

void ed_init() {
    ui_init();
    editor.tb = tb_new();
    editor.mode = NORMAL;
    editor.draw_off = 0;
    editor.col_off = 0;
}

void ed_exit() {
    ui_exit();
    tb_free(editor.tb);
}

int main(int argc, char **argv) {
    char key;
    ed_init();

    if (argc > 1) {
        tb_load_file(editor.tb, argv[1]);
        //tb_debug(editor.tb);
    }

    do {
        ed_render();
        ui_update();
        key = ui_read_key();
        ed_process_key(key);
    } while (key != CTRL('q'));

    ed_exit();
    return 0;
}

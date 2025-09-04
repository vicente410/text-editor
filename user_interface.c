#include "user_interface.h"

typedef struct {
    char *data;
    size_t len;
    size_t cap;
} AppendBuffer;

AppendBuffer ab;
struct termios cooked;
struct winsize ws;

void enable_raw_mode() {
    struct termios raw;

    tcgetattr(STDIN_FILENO, &cooked);
    raw = cooked;
    cfmakeraw(&raw);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disable_raw_mode() {
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &cooked);
}

void ab_reserve(size_t additional) {
    if (additional > ab.cap - ab.len) {
        while (additional > ab.cap - ab.len) {
            if (ab.cap == 0) {
                ab.cap = AB_INIT_SIZE;
            } else {
                ab.cap *= AB_GROWTH_RATE;
            }
        }

        ab.data = realloc(ab.data, ab.cap);
    }
}

void ui_init() {
    write(STDIN_FILENO, "\x1b[?1049h", 8);
    enable_raw_mode();

    ab.data = NULL;
    ab.len = 0;
    ab.cap = 0;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
}

void ui_exit() {
    write(STDIN_FILENO, "\x1b[?1049l", 8);
    disable_raw_mode();

    free(ab.data);
}

size_t ui_rows() {
    return ws.ws_row;
}

size_t ui_cols() {
    return ws.ws_col;
}

Key ui_read_key() {
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}

void ui_draw(char *str) {
    size_t len = strlen(str);
    ab_reserve(len);
    memcpy(ab.data + ab.len, str, len);
    ab.len += len;
}

void ui_draw_ch(char ch) {
    ab_reserve(1);
    ab.data[ab.len++] = ch;
}

void ui_update() {
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &ws);
    write(STDOUT_FILENO, CLEAR_SCREEN MOVE_CURSOR_0_0, 7);
    write(STDOUT_FILENO, ab.data, ab.len);
    ab.len = 0;
}

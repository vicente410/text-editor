#include <termios.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define AB_INIT_SIZE 16
#define AB_GROWTH_RATE 2

#define CLEAR_SCREEN "\x1b[2J"
#define MOVE_CURSOR_0_0 "\x1b[H"

typedef char Key;

void ui_init();
void ui_exit();

size_t ui_rows();
size_t ui_cols();

Key ui_read_key();
void ui_draw(char *str);
void ui_draw_ch(char ch);
void ui_update();

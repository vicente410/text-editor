#include <termios.h>
#include <sys/ioctl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define AB_INIT_SIZE 16
#define AB_GROWTH_FACTOR 2

typedef char Key;

void ui_init();
void ui_exit();

size_t ui_rows();
size_t ui_cols();

Key ui_read_key();
void ui_draw(char *str);
void ui_update();

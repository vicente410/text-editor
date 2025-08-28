#include <stdio.h>
#include "text_buffer.h"

int main()
{
    TextBuffer *tb = tb_new();
    tb_debug(tb);
    return 0;
}

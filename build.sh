#!/usr/bin/bash

gcc -o editor editor.c text_buffer.c user_interface.c custom.c -Wall -Wextra -Wno-unused-parameter -ggdb

#pragma once
#include <stddef.h>

typedef enum {
    NORMAL,
    INSERT,
} Mode;

typedef struct {
    Mode mode;
    char key;
    void (*function)();
} Keybind;

extern const Keybind keybinds[];
extern const size_t num_binds;

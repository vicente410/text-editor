#include "custom.h"
#include "editor.h"

void greet() {
    ed_message("Hello World!");
}

void greet_ed() {
    ed_message("Hello Editor!");
}

void insert_mode() {
    ed_set_mode(INSERT);
    ed_message("INSERT");
}

void normal_mode() {
    ed_set_mode(NORMAL);
    ed_message("NORMAL");
}

const Keybind keybinds[] = {
    {NORMAL, 'i', insert_mode},
    {INSERT, 'n', normal_mode},
    {NORMAL, 'g', greet},
    {INSERT, 'g', greet_ed},
};

const size_t num_binds = sizeof(keybinds) / sizeof(Keybind);

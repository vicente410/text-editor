#include <stdio.h>

typedef enum {
	NORMAL,
	INSERT,
} Mode;

Mode mode = NORMAL;

typedef struct {
	Mode mode;
	char key;
	void (*function)();
} Keybind;

void succ_n() {
	printf("%d\n", 1);
}

void double_n() {
	printf("%d\n", 2);
}

void quadruple() {
	printf("%d\n", 4);
}

void insert_mode() {
	mode = INSERT;
}

void normal_mode() {
	mode = NORMAL;
}

Keybind keybinds[] = {
	{ NORMAL, 's', succ_n },
	{ NORMAL, 'd', double_n },
	{ INSERT, 'd', quadruple },
	{ NORMAL, 'i', insert_mode },
	{ INSERT, 'n', normal_mode },
};

int main() {
	char key;
	size_t num_binds = sizeof(keybinds)/sizeof(Keybind);

	while (key != 'q') {
		key = getchar();

		for (size_t i = 0; i < num_binds; i++) {
			if (mode == keybinds[i].mode && 
				key == keybinds[i].key) {
				keybinds[i].function();
			}
		}
	}
}

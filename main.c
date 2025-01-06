#include "create_files.c"
#include "option_handler.c"
#include <stdio.h>

int main(int argv, char* argc[]) {
    int options = parse_options(argv, argc);

    switch (options) {
        case HELP:
            printf("Usage: nudge [-s] \"./file/path/\"\n");
            return 0;
        case SAFE_MODE:
            mode = 's';
            break;
    }

    for(int i = 1; i < argv; i++) {
        if(argc[i][0] == '-') {
            continue;
        }

        CreateFiles(argc[i]);
    }

    return 0;
}

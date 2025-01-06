#include <stdio.h>
#include <string.h>

#define HELP -1
#define SAFE_MODE 1

#define HELP_OPTION "--help"
#define HELP_OPTION_SHORT "-h"

#define SAFE_MODE_OPTION "--safe"
#define SAFE_MODE_OPTION_SHORT "-s"


int parse_options(int argv, char* argc[]) {
    int safe_mode = 0;

    if(argv == 1) {
        return HELP;
    }

    for(int i = 0; i < argv; i++) {
        if(argc[i][0] == '-') {
            if(strcmp(SAFE_MODE_OPTION, argc[i]) == 0 || strcmp(SAFE_MODE_OPTION_SHORT, argc[i]) == 0) {
                safe_mode = SAFE_MODE;
            }
            else if(strcmp(HELP_OPTION, argc[i]) == 0 || strcmp(HELP_OPTION_SHORT, argc[i]) == 0) {
                return HELP;
            }
            else {
                printf("Invalid option: %s\n", argc[i]);
                return HELP;
            }
        }
    }

    return safe_mode;
}
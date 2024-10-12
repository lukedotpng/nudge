#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

// Global mode 
// n (normal) -> Create all directories requested
// s (safe) -> Error if enclosing directories do not exist
char mode = 'n';

int SplitStringAtChar(char* string, char split_char, char*** substring_arr) {
    int string_len = strlen(string);

    int substring_cnt = 0;

    for(int i = 0; i < string_len; i++) {
        if(string[i] == split_char) {
            substring_cnt++;
        }
    }

    if(string[string_len - 1] != '/') {
        substring_cnt++;
    }

    char** substrings_result = malloc(sizeof(char*) * substring_cnt);

    int curr_substring_start_index = 0;
    int curr_substring_len = 0;
    int substring_result_index = 0;
    for(int i = 0; i < string_len; i++) {
        curr_substring_len++;
        if(string[i] == split_char || i == string_len - 1) {
            substrings_result[substring_result_index] = malloc(sizeof(char) * curr_substring_len);

            strncpy(substrings_result[substring_result_index], string + curr_substring_start_index, curr_substring_len);

            curr_substring_start_index += curr_substring_len;
            curr_substring_len = 0;
            substring_result_index++;
        }
    }
    
    *substring_arr = substrings_result;

    return substring_cnt;
}

int DirectoryExists(char* path) {
    struct stat stat_buf;

    int stat_res = stat(path, &stat_buf);  

    return stat_res;
}

int CreateFiles(char* file_path) {
    char** substring_arr = NULL;
    int substring_cnt = SplitStringAtChar(file_path, '/', &substring_arr);


    char curr_file_path[1024] = {0};

    for(int i = 0; i < substring_cnt; i++) {
        strcat(curr_file_path, substring_arr[i]);

        char* curr_substring = substring_arr[i];
        int curr_substring_len = strlen(curr_substring);

        if(curr_substring[curr_substring_len - 1] == '/') {
            if(DirectoryExists(curr_file_path) != 0) {
                if(mode == 's') {
                    printf("Error: Directory \"%s\" does not exist. Remove \"-s\" to automatically create non-existent directories.\n", curr_substring);
                    return -1;
                }
                mkdir(curr_file_path, S_IRWXU | S_IRGRP | S_IXGRP | S_IROTH | S_IXOTH); // drwxr-x--x
            }
        } else {
            FILE* new_file = fopen(curr_file_path, "a");
            fclose(new_file);
        }
    }

    return 0;
}

int main(int argv, char* argc[]) {
    if(argv == 1) {
        printf("Usage: nudge [-s] file_path\n");
        return 0;
    }

    for(int i = 1; i < argv; i++) {
        if(strcmp(argc[i], "-s") == 0) {
            mode = 's';
            continue;
        }

        if(i == argv - 1) mode = 'n'; // Turn off safe mode for last item so it will make non-existent directory

        CreateFiles(argc[i]);
    }

    return 0;
}

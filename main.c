#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "token.h"

int main(int argc, char* argv[]) {
    srand(time(NULL));

    // Interactive REPL Mode
    if (argc < 2) {
        char line[1024];
        printf("BinukLang v1.0 Interactive Shell (Type 'exit' to quit)\n");
        while (1) {
            printf("bnk>>> ");
            if (!fgets(line, sizeof(line), stdin)) break;
            if (strncmp(line, "exit", 4) == 0) break;
            run_code(line);
        }
        return 0;
    }

    // File Execution Mode (.bnk)
    FILE* file = fopen(argv[1], "r");
    if (!file) {
        printf("Error: Could not open file '%s'\n", argv[1]);
        return 1;
    }

    char code[20000];
    size_t n = fread(code, 1, sizeof(code) - 1, file);
    code[n] = '\0';
    fclose(file);

    run_code(code);
    return 0;
}
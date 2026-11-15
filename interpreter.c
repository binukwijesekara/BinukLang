#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "token.h"

typedef struct {
    char name[64];
    int value;
} Variable;

static Variable variables[100];
static int var_count = 0;

void set_variable(const char* name, int value) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            variables[i].value = value;
            return;
        }
    }
    strcpy(variables[var_count].name, name);
    variables[var_count].value = value;
    var_count++;
}

int get_variable(const char* name) {
    for (int i = 0; i < var_count; i++) {
        if (strcmp(variables[i].name, name) == 0) {
            return variables[i].value;
        }
    }
    printf("Runtime Error: Undefined variable '%s'\n", name);
    return 0;
}

void skip_block() {
    if (tokens[current_token].type == TOKEN_LBRACE) {
        current_token++;
        int brace_depth = 1;
        while (brace_depth > 0 && tokens[current_token].type != TOKEN_EOF) {
            if (tokens[current_token].type == TOKEN_LBRACE) brace_depth++;
            else if (tokens[current_token].type == TOKEN_RBRACE) brace_depth--;
            current_token++;
        }
    }
}

void execute_statement();

void execute_block() {
    if (tokens[current_token].type == TOKEN_LBRACE) {
        current_token++;
        while (tokens[current_token].type != TOKEN_RBRACE && tokens[current_token].type != TOKEN_EOF) {
            execute_statement();
        }
        if (tokens[current_token].type == TOKEN_RBRACE) current_token++;
    }
}

void execute_statement() {
    Token t = tokens[current_token];

    if (t.type == TOKEN_DANNA) {
        current_token++;
        char var_name[64];
        strcpy(var_name, tokens[current_token].value);
        current_token++;
        if (tokens[current_token].type == TOKEN_ASSIGN) current_token++;
        int val = parse_expression();
        set_variable(var_name, val);
        if (tokens[current_token].type == TOKEN_SEMICOLON) current_token++;
    }
    else if (t.type == TOKEN_IDENTIFIER && tokens[current_token + 1].type == TOKEN_ASSIGN) {
        char var_name[64];
        strcpy(var_name, t.value);
        current_token += 2;
        int val = parse_expression();
        set_variable(var_name, val);
        if (tokens[current_token].type == TOKEN_SEMICOLON) current_token++;
    }
    else if (t.type == TOKEN_PENWANNA) {
        current_token++;
        if (tokens[current_token].type == TOKEN_LPAREN) current_token++;
        if (tokens[current_token].type == TOKEN_STRING) {
            printf("%s\n", tokens[current_token].value);
            current_token++;
        } else {
            int val = parse_expression();
            printf("%d\n", val);
        }
        if (tokens[current_token].type == TOKEN_RPAREN) current_token++;
        if (tokens[current_token].type == TOKEN_SEMICOLON) current_token++;
    }
    else if (t.type == TOKEN_NAM) {
        current_token++;
        if (tokens[current_token].type == TOKEN_LPAREN) current_token++;
        int cond = parse_condition();
        if (tokens[current_token].type == TOKEN_RPAREN) current_token++;

        if (cond) {
            execute_block();
            if (tokens[current_token].type == TOKEN_NATHTHAN) {
                current_token++;
                skip_block();
            }
        } else {
            skip_block();
            if (tokens[current_token].type == TOKEN_NATHTHAN) {
                current_token++;
                execute_block();
            }
        }
    }
    else if (t.type == TOKEN_THURU) {
        int loop_start = current_token;
        current_token++;
        if (tokens[current_token].type == TOKEN_LPAREN) current_token++;
        int cond = parse_condition();
        if (tokens[current_token].type == TOKEN_RPAREN) current_token++;

        if (cond) {
            execute_block();
            current_token = loop_start;
        } else {
            skip_block();
        }
    }
    else {
        printf("Syntax Error: Unknown command '%s'\n", t.value);
        exit(1);
    }
}

void run_code(const char* code) {
    tokenize(code);
    current_token = 0;
    while (tokens[current_token].type != TOKEN_EOF) {
        execute_statement();
    }
}
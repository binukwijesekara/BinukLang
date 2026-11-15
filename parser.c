#include <stdio.h>
#include <stdlib.h>
#include "token.h"

// External function from interpreter.c
int get_variable(const char* name);

int parse_factor() {
    Token t = tokens[current_token];
    if (t.type == TOKEN_NUMBER) {
        current_token++;
        return atoi(t.value);
    } else if (t.type == TOKEN_IDENTIFIER) {
        current_token++;
        return get_variable(t.value);
    } else if (t.type == TOKEN_GANNA) {
        current_token++;
        if (tokens[current_token].type == TOKEN_LPAREN) current_token++;
        if (tokens[current_token].type == TOKEN_RPAREN) current_token++;
        int input_val = 0;
        printf(">> ");
        scanf("%d", &input_val);
        return input_val;
    } else if (t.type == TOKEN_AHAMBEN) {
        current_token++;
        if (tokens[current_token].type == TOKEN_LPAREN) current_token++;
        int min_val = parse_expression();
        if (tokens[current_token].type == TOKEN_COMMA) current_token++;
        int max_val = parse_expression();
        if (tokens[current_token].type == TOKEN_RPAREN) current_token++;
        
        if (max_val < min_val) { int tmp = min_val; min_val = max_val; max_val = tmp; }
        return (rand() % (max_val - min_val + 1)) + min_val;
    } else if (t.type == TOKEN_LPAREN) {
        current_token++;
        int val = parse_expression();
        if (tokens[current_token].type == TOKEN_RPAREN) current_token++;
        return val;
    }
    printf("Syntax Error: Unexpected token '%s'\n", t.value);
    exit(1);
}

int parse_term() {
    int left = parse_factor();
    while (tokens[current_token].type == TOKEN_MUL || tokens[current_token].type == TOKEN_DIV) {
        TokenType op = tokens[current_token].type;
        current_token++;
        int right = parse_factor();
        if (op == TOKEN_MUL) left *= right;
        else {
            if (right == 0) { printf("Runtime Error: Division by zero!\n"); exit(1); }
            left /= right;
        }
    }
    return left;
}

int parse_expression() {
    int left = parse_term();
    while (tokens[current_token].type == TOKEN_PLUS || tokens[current_token].type == TOKEN_MINUS) {
        TokenType op = tokens[current_token].type;
        current_token++;
        int right = parse_term();
        if (op == TOKEN_PLUS) left += right;
        else left -= right;
    }
    return left;
}

int parse_condition() {
    int left = parse_expression();
    TokenType op = tokens[current_token].type;
    if (op == TOKEN_EQ || op == TOKEN_NEQ || op == TOKEN_LT || 
        op == TOKEN_GT || op == TOKEN_LTE || op == TOKEN_GTE) {
        current_token++;
        int right = parse_expression();
        switch (op) {
            case TOKEN_EQ: return left == right;
            case TOKEN_NEQ: return left != right;
            case TOKEN_LT: return left < right;
            case TOKEN_GT: return left > right;
            case TOKEN_LTE: return left <= right;
            case TOKEN_GTE: return left >= right;
            default: return 0;
        }
    }
    return left != 0;
}
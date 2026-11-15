#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "token.h"

Token tokens[2000];
int token_count = 0;
int current_token = 0;

void tokenize(const char* source) {
    int i = 0;
    int len = strlen(source);
    token_count = 0;

    while (i < len) {
        if (isspace(source[i])) { i++; continue; }

        // Single-line comments (//)
        if (source[i] == '/' && source[i+1] == '/') {
            while (i < len && source[i] != '\n') i++;
            continue;
        }

        // String literals ("...")
        if (source[i] == '"') {
            i++;
            Token token;
            token.type = TOKEN_STRING;
            int j = 0;
            while (i < len && source[i] != '"') {
                token.value[j++] = source[i++];
            }
            token.value[j] = '\0';
            if (source[i] == '"') i++;
            tokens[token_count++] = token;
            continue;
        }

        // Numeric literals
        if (isdigit(source[i])) {
            Token token;
            token.type = TOKEN_NUMBER;
            int j = 0;
            while (i < len && isdigit(source[i])) {
                token.value[j++] = source[i++];
            }
            token.value[j] = '\0';
            tokens[token_count++] = token;
            continue;
        }

        // Keywords & Identifiers
        if (isalpha(source[i])) {
            Token token;
            int j = 0;
            while (i < len && (isalnum(source[i]) || source[i] == '_')) {
                token.value[j++] = source[i++];
            }
            token.value[j] = '\0';

            if (strcmp(token.value, "danna") == 0) token.type = TOKEN_DANNA;
            else if (strcmp(token.value, "penwanna") == 0) token.type = TOKEN_PENWANNA;
            else if (strcmp(token.value, "nam") == 0) token.type = TOKEN_NAM;
            else if (strcmp(token.value, "naththan") == 0) token.type = TOKEN_NATHTHAN;
            else if (strcmp(token.value, "thuru") == 0) token.type = TOKEN_THURU;
            else if (strcmp(token.value, "ganna") == 0) token.type = TOKEN_GANNA;
            else if (strcmp(token.value, "ahamben") == 0) token.type = TOKEN_AHAMBEN;
            else token.type = TOKEN_IDENTIFIER;

            tokens[token_count++] = token;
            continue;
        }

        // Two-character relational operators
        Token token;
        if (source[i] == '=' && source[i+1] == '=') {
            token.type = TOKEN_EQ; strcpy(token.value, "=="); i += 2;
            tokens[token_count++] = token; continue;
        }
        if (source[i] == '!' && source[i+1] == '=') {
            token.type = TOKEN_NEQ; strcpy(token.value, "!="); i += 2;
            tokens[token_count++] = token; continue;
        }
        if (source[i] == '<' && source[i+1] == '=') {
            token.type = TOKEN_LTE; strcpy(token.value, "<="); i += 2;
            tokens[token_count++] = token; continue;
        }
        if (source[i] == '>' && source[i+1] == '=') {
            token.type = TOKEN_GTE; strcpy(token.value, ">="); i += 2;
            tokens[token_count++] = token; continue;
        }

        // Single-character operators & delimiters
        token.value[0] = source[i];
        token.value[1] = '\0';
        switch (source[i]) {
            case '=': token.type = TOKEN_ASSIGN; break;
            case '+': token.type = TOKEN_PLUS; break;
            case '-': token.type = TOKEN_MINUS; break;
            case '*': token.type = TOKEN_MUL; break;
            case '/': token.type = TOKEN_DIV; break;
            case '<': token.type = TOKEN_LT; break;
            case '>': token.type = TOKEN_GT; break;
            case ',': token.type = TOKEN_COMMA; break;
            case ';': token.type = TOKEN_SEMICOLON; break;
            case '(': token.type = TOKEN_LPAREN; break;
            case ')': token.type = TOKEN_RPAREN; break;
            case '{': token.type = TOKEN_LBRACE; break;
            case '}': token.type = TOKEN_RBRACE; break;
            default: token.type = TOKEN_UNKNOWN; break;
        }
        tokens[token_count++] = token;
        i++;
    }

    Token eof_token = {TOKEN_EOF, "EOF"};
    tokens[token_count++] = eof_token;
}
#ifndef TOKEN_H
#define TOKEN_H

typedef enum {
    TOKEN_DANNA,      // danna (var)
    TOKEN_PENWANNA,   // penwanna (print)
    TOKEN_NAM,        // nam (if)
    TOKEN_NATHTHAN,   // naththan (else)
    TOKEN_THURU,      // thuru (while)
    TOKEN_GANNA,      // ganna (input)
    TOKEN_AHAMBEN,    // ahamben (random)
    TOKEN_IDENTIFIER,
    TOKEN_NUMBER,
    TOKEN_STRING,
    TOKEN_ASSIGN,     // =
    TOKEN_PLUS,       // +
    TOKEN_MINUS,      // -
    TOKEN_MUL,        // *
    TOKEN_DIV,        // /
    TOKEN_EQ,         // ==
    TOKEN_NEQ,        // !=
    TOKEN_LT,         // <
    TOKEN_GT,         // >
    TOKEN_LTE,        // <=
    TOKEN_GTE,        // >=
    TOKEN_COMMA,      // ,
    TOKEN_SEMICOLON,  // ;
    TOKEN_LPAREN,     // (
    TOKEN_RPAREN,     // )
    TOKEN_LBRACE,     // {
    TOKEN_RBRACE,     // }
    TOKEN_EOF,
    TOKEN_UNKNOWN
} TokenType;

typedef struct {
    TokenType type;
    char value[256];
} Token;

// Global Token Stream
extern Token tokens[2000];
extern int token_count;
extern int current_token;

// Module Functions
void tokenize(const char* source);
int parse_expression();
int parse_condition();
void run_code(const char* code);

#endif
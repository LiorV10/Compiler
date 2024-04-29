// Token.h

#define _TOKEN_H

typedef enum {
              STRING_LITERAL, IDENTIFIER, VOID, MAIN, INT, 
              FLOAT, LONG, DOUBLE, SHORT, CHAR, UNSIGNED, STRUCT, FOR,
              IF, ELSE, WHILE, RETURN, PLUS, MINUS, GT, LT, EQ, GE, LE, EEQ, NEQ, STAR, SLASH, MOD, DOT, ARROW,
              COMMA, SEMI_COLON, LEFT_BRACKET, RIGHT_BRACKET, LEFT_CURLY, RIGHT_CURLY, LEFT_PAREN, RIGHT_PAREN, 
              AMPERSAND, FLOAT_LITERAL, INTEGER_LITERAL, WHITESPACE, EOD
            } TokenType;

typedef struct
{
    char *lexeme;
    TokenType type;
} Token;
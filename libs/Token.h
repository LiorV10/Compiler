// Token.h

#define _TOKEN_H

typedef enum {
              STRING_LITERAL, IDENTIFIER, VOID, MAIN, INT, 
              FLOAT, LONG, DOUBLE, SHORT, CHAR, UNSIGNED, FOR, 
              IF, ELSE, WHILE, PLUS, MINUS, GT, LT, EQ, STAR, SLASH, MOD, 
              COMMA, SEMI_COLON, LEFT_CURLY, RIGHT_CURLY, LEFT_PAREN, RIGHT_PAREN, 
              AMPERSAND, FLOAT_LITERAL, INTEGER_LITERAL, WHITESPACE
            } TokenType;

typedef struct
{
    char *lexeme;
    TokenType type;
} Token;
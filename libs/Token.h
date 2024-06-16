// Token.h

#define _TOKEN_H

typedef unsigned short TokenType;

typedef struct
{
    char *lexeme;
    TokenType type;
} Token;

void FreeToken(Token *token);
// Token.c

#include "Token.h"

void FreeToken(Token *token)
{
    free(token->lexeme);
    free(token);
}
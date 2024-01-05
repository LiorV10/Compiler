// main.c

#include "Lexer.c"
#include <string.h>

char* TypeToString(unsigned short type)
{
    switch(type)
    {
        case IDENTIFIER : return "identifier";
        case KEYWORD    : return "keyword";
        case SEPERATOR  : return "seperator"; 
        case OPERATOR   : return "operator"; 
        case LITERAL    : return "literal";
    }
}

void main(void)
{
    char *_s = "  float x = 5.3 + 3, y = 8    ,    z  =    9.9922 + 4.3232;";
    char *s = strdup(_s);
    LinearLinkedListNode *tokens;

    tokens = SplitStatmentIntoTokens(s);

    while (tokens)
    {
        printf("[%s] '%s'\n", TypeToString(tokens->info.tokenType), tokens->info.tokenInfo);
        tokens = tokens->nextNode;
    }
}
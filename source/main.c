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
    char *_s = "my first lexer 34";
    char *s = strdup(_s);
    LinearLinkedListNode *tokens;

    tokens = SplitStatmentsIntoTokens(s);

    while (tokens)
    {
        printf("[%s] %s\n", TypeToString(tokens->info.tokenType), tokens->info.tokenInfo);
        tokens = tokens->nextNode;
    }
}
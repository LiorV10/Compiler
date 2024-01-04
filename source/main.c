// main.c

#include "Lexer.c"
#include <string.h>

void main(void)
{
    char *_s = "my first lexer";
    char *s = strdup(_s);
    LinearLinkedListNode *tokens;

    tokens = SplitStatmentsIntoTokens(s);

    while (tokens)
    {
        puts(tokens->info.tokenInfo);
        tokens = tokens->nextNode;
    }
}
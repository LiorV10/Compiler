// main.c

#include "Lexer.h"
#include "Parser.h"
#include "viewer.h"

void PrintMatch(Match *match)
{
    const char *ptr = match->start;

    for (; ptr < match->end; ptr++)
    {
        printf("%c", *ptr);
    }
}

CircularLinearLinkedListNode* TokenizeSource(Stream *sourceStream)
{
    Lexer lexer;              
    CircularLinearLinkedListNode *tokens;
    CircularLinearLinkedListNode *current;

    InitLexer(&lexer);

    tokens = Tokenize(&lexer, NextLine(sourceStream));

    while (!EndOfStream(sourceStream))
    {
        current = Tokenize(&lexer, NextLine(sourceStream));
        current ? ConcatCircularLinearLinkedLists(&tokens, current) : ZERO;
    }

    FreeLexer(&lexer);
    ResetStream(sourceStream);

    return (tokens);
}

void FreeAllTokens(CircularLinearLinkedListNode **tokens)
{
    CircularLinearLinkedListNode *ptr = *tokens;

    do
    {
        FreeMatch(((Token*)ptr->info)->info);
        free(ptr->info);

        ptr = ptr->nextNode;
    }
    while (ptr != *tokens);

    EmptyCircularLinearLinkedList(tokens);
}

void main(unsigned short argumentsCount, char* arguments[])
{    
    Stream sourceStream;
    CircularLinearLinkedListNode *tokens;
    
    argumentsCount < TWO ? ExitWithError("Source file was not specified.") : ZERO;

    InitStream(&sourceStream, arguments[ONE]);
    tokens = TokenizeSource(&sourceStream);
    CloseStream(&sourceStream);

    /* TESTING */

    CircularLinearLinkedListNode *ptr = tokens->nextNode;
    Token *token;

    do
    {
        token = ptr->info;
        PrintMatch(token->info);
        printf(" -> %d\n", token->type);

        ptr = ptr->nextNode;
    }
    while (ptr != tokens->nextNode);

    /* TESTING */

    FreeAllTokens(&tokens);
}
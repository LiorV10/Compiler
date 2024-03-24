// main.c

#include "Lexer.c"
#include "Parser.h"
#include "Viewer.h"

/* FOR TESTING */
#include <sys/time.h>

/* FOR TESTING */
void PrintMatch(Match *match)
{
    char *ptr = match->start;

    for (; ptr < match->end; ptr++)
    {
        printf("%c", *ptr);
    }

    printf("\t");
}

/* FOR TESTING */
char* TypeStr(TokenType type)
{
    switch(type)
    {
        case STRING_LITERAL_TOKEN:
            return "String literal";
        case KEYOWRD_TOKEN:
            return "Keyword";
        case IDENTIFIER_TOKEN:
            return "Identifier";
        case OPERATOR_LITERAL_TOKEN:
            return "Operator";
        case FLOAT_LITERAL_TOKEN:
            return "Float literal";
        case INTEGER_LITERAL_TOKEN:
            return "Int literal";
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

    struct timeval stop, st;
    gettimeofday(&st, NULL);

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
        printf("\t->\t%s\n", TypeStr(token->type));

        ptr = ptr->nextNode;
    }
    while (ptr != tokens->nextNode);

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - st.tv_sec) * 1000000 + stop.tv_usec - st.tv_usec);
    printf("took %lu s\n", stop.tv_sec - st.tv_sec);

    /* TESTING */

    FreeAllTokens(&tokens);
}
// main.c

#include "Lexer.h"
#include "Parser.c"
#include "Viewer.h"

#pragma region TESTING
#include <sys/time.h>

#define TO_STR(x) [x] = #x

const char* typeStr[] = {
              TO_STR(STRING_LITERAL), TO_STR(IDENTIFIER), TO_STR(VOID), TO_STR(MAIN), TO_STR(INT), 
              TO_STR(FLOAT), TO_STR(LONG), TO_STR(DOUBLE), TO_STR(SHORT), TO_STR(CHAR), TO_STR(UNSIGNED), TO_STR(STRUCT),
              TO_STR(FOR), TO_STR(IF), TO_STR(ELSE), TO_STR(WHILE), TO_STR(RETURN), TO_STR(PLUS), TO_STR(MINUS), TO_STR(GT), 
              TO_STR(LT), TO_STR(EQ), TO_STR(GE), TO_STR(LE), TO_STR(EEQ), TO_STR(NEQ), TO_STR(STAR), TO_STR(SLASH), TO_STR(MOD), 
              TO_STR(DOT), TO_STR(ARROW), TO_STR(COMMA), TO_STR(SEMI_COLON), TO_STR(LEFT_BRACKET), TO_STR(RIGHT_BRACKET), 
              TO_STR(LEFT_CURLY), TO_STR(RIGHT_CURLY), TO_STR(LEFT_PAREN), TO_STR(RIGHT_PAREN), TO_STR(AMPERSAND), 
              TO_STR(FLOAT_LITERAL), TO_STR(INTEGER_LITERAL), TO_STR(WHITESPACE), TO_STR(EOD)
            };

void PrintMatch(struct Match *match)
{
    char *ptr = match->start;

    for (; ptr < match->end; ptr++)
    {
        printf("%c", *ptr);
    }

    printf("\t");
}

struct timeval stop, start;
#pragma endregion

CircularLinearLinkedListNode* TokenizeStream(Stream *sourceStream)
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

    InsertEndCircularLinearLinkedList(&tokens);
    tokens->info = malloc(sizeof(Token));
    ((Token*)tokens->info)->type = EOD;
    ((Token*)tokens->info)->lexeme = NULL; // just for printing

    FreeLexer(&lexer);
    ResetStream(sourceStream);

    return (tokens);
}

void FreeToken(Token *token)
{
    free(token->lexeme);
    free(token);
}

void FreeAllTokens(CircularLinearLinkedListNode **tokens)
{
    // CircularLinearLinkedListNode *ptr = *tokens;

    // do
    // {
    //     free(((Token*)ptr->info)->lexeme);
    //     free(ptr->info);

    //     ptr = ptr->nextNode;
    // }
    // while (ptr != *tokens);

    EmptyCircularLinearLinkedList(tokens, FreeToken);
}

void main(unsigned short argumentsCount, char* arguments[])
{
    Stream sourceStream;
    CircularLinearLinkedListNode *tokens;

    argumentsCount < TWO ? ExitWithError("Source file was not specified.") : ZERO;

    InitStream(&sourceStream, arguments[ONE]);
    tokens = TokenizeStream(&sourceStream);
    CloseStream(&sourceStream);

    /* TESTING */
    
    CircularLinearLinkedListNode *ptr = tokens->nextNode;
    Token *token;

    do
    {
        token = ptr->info;
        if (token->lexeme)
        printf("%s\t->\t%s\n", token->lexeme, typeStr[token->type]);

        ptr = ptr->nextNode;
    }
    while (ptr != tokens->nextNode);

    /*     PARSING      */
    gettimeofday(&start, NULL);
    Parser parser;
    InitParser(&parser, typeStr);
    puts("");
    Parse(&parser, tokens);
    FreeParser(&parser);
    gettimeofday(&stop, NULL);

    /*     PARSING      */

    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    printf("took %lu s\n", stop.tv_sec - start.tv_sec);

    /* TESTING */

    FreeAllTokens(&tokens);
}
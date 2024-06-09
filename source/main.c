// main.c

#include "Viewer.h"
#include "Lexer.c"
#include "Parser.c"
#include "CodeGenerator.c"
#include "SemanticAnalyzer.c"

#pragma region TESTING

#define TO_STR(x) [x] = #x

const char* typeStr[] = {
              TO_STR(STRING_LITERAL), TO_STR(MAIN), TO_STR(IDENTIFIER), TO_STR(VOID), TO_STR(INT), 
              TO_STR(FLOAT), TO_STR(LONG), TO_STR(DOUBLE), TO_STR(SHORT), TO_STR(CHAR), TO_STR(UNSIGNED), TO_STR(STRUCT),
              TO_STR(FOR), TO_STR(IF), TO_STR(ELSE), TO_STR(WHILE), TO_STR(RETURN), TO_STR(PLUS), 
              TO_STR(PLUS_PLUS), TO_STR(MINUS), TO_STR(MINUS_MINUS), TO_STR(PLUS_EQ), TO_STR(MINUS_EQ), 
              TO_STR(STAR_EQ), TO_STR(SLASH_EQ), TO_STR(MOD_EQ), TO_STR(GT), TO_STR(LT), TO_STR(EQ),
              TO_STR(GE), TO_STR(LE), TO_STR(EEQ), TO_STR(NEQ), TO_STR(STAR), TO_STR(SLASH), TO_STR(MOD), 
              TO_STR(DOT), TO_STR(ARROW), TO_STR(COMMA), TO_STR(SEMI_COLON), TO_STR(LEFT_BRACKET), TO_STR(RIGHT_BRACKET), 
              TO_STR(LEFT_CURLY), TO_STR(RIGHT_CURLY), TO_STR(LEFT_PAREN), TO_STR(RIGHT_PAREN), TO_STR(AMPERSAND), 
              TO_STR(FLOAT_LITERAL), TO_STR(INTEGER_LITERAL), TO_STR(LOG_NOT), TO_STR(TYPEDEF), TO_STR(LSHIFT), TO_STR(LOG_AND),
              TO_STR(RSHIFT), TO_STR(WHITESPACE), TO_STR(EOD)
            };

#include <sys/time.h>
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
    ((Token*)tokens->info)->lexeme = NULL;

    FreeLexer(&lexer);
    ResetStream(sourceStream);

    return (tokens);
}

void FreeToken(Token *token)
{
    free(token->lexeme);
    free(token);
}

void EmitFunc(void *stream, char *buffer, va_list args)
{
    vfprintf(stream, buffer, args);
}

void main(unsigned short argumentsCount, char* arguments[])
{
    Stream sourceStream;
    CircularLinearLinkedListNode *tokens;

    Parser parser;
    AbstractSyntaxTreeNode *ast;

    CodeGenerator generator;

    argumentsCount < THREE ? ExitWithError("Source/Dest file was not specified.") : ZERO;

    InitStream(&sourceStream, arguments[ONE], "rt");
    tokens = TokenizeStream(&sourceStream);
    CloseStream(&sourceStream);

    gettimeofday(&start, NULL);

    InitParser(&parser, typeStr);

    ast = Parse(&parser, tokens);

    Semantics(&ast);

    FILE *p = fopen(arguments[TWO], "wt");
    InitCodeGenerator(&generator, EmitFunc, p);
    GenerateCode(&generator, ast);
    fclose(p);

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    printf("took %lu s\n", stop.tv_sec - start.tv_sec);

    /*      TESTING      */
    system("gcc out.s -o out.o && ./out.o ; echo $?");

    FreeParser(&parser);
    EmptyCircularLinearLinkedList(&tokens, FreeToken);
}
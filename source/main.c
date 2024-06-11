// main.c

#include "Viewer.h"
#include "Construction.h"
#include "Lexer.h"
#include "Parser.h"
#include "SemanticAnalyzer.h"
#include "CodeGenerator.h"

#include <sys/time.h>
struct timeval stop, start;

CircularLinearLinkedListNode* TokenizeStream(Stream *sourceStream, Stack *errors)
{
    Lexer lexer;
    CircularLinearLinkedListNode *tokens;
    CircularLinearLinkedListNode *current;
    unsigned int currentLine = ONE;

    InitLexer(&lexer);

    tokens = Tokenize(&lexer, NextLine(sourceStream), errors, currentLine++);
    
    while (!EndOfStream(sourceStream))
    {
        InsertEndCircularLinearLinkedList(&tokens);
        tokens->info = malloc(sizeof(Token));
        ((Token*)tokens->info)->type = WHITESPACE;
        ((Token*)tokens->info)->lexeme = NULL;

        current = Tokenize(&lexer, NextLine(sourceStream), errors, currentLine++);
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
    va_list tmp;
    va_copy(tmp, args);

    vfprintf(stream, buffer, args);
    // vfprintf(stdout, buffer, tmp);

    va_end(tmp);
}

void FreeNode(AbstractSyntaxTreeNode *astRoot)
{
    EmptyCircularLinearLinkedList(&astRoot->childrenManager, NULL);
    free(astRoot);
}

void FreeAbstractSyntaxTree(AbstractSyntaxTreeNode *astRoot)
{
    if (!astRoot->childrenManager)
    {
        FreeNode(astRoot);
        return;
    }

    CircularLinearLinkedListNode *child = astRoot->childrenManager->nextNode;

    do
    {
        FreeAbstractSyntaxTree(child->info);
        child = child->nextNode;
    } 
    while (child != astRoot->childrenManager->nextNode);
    
    FreeNode(astRoot);
}

void main(unsigned short argumentsCount, char* arguments[])
{
    Stack errors;
    Grammar grammar;

    Stream sourceStream;
    CircularLinearLinkedListNode *tokens;

    Parser parser;
    AbstractSyntaxTreeNode *ast;

    CodeGenerator generator;

    argumentsCount < THREE ? ExitWithError("Source/Dest file was not specified.") : ZERO;

    InitStack(&errors);
    InitGrammar(&grammar);
    BuildGrammarFromFile(&grammar);
    AssignActions(&grammar);

    InitStream(&sourceStream, arguments[ONE], "rt");
    tokens = TokenizeStream(&sourceStream, &errors);
    CloseStream(&sourceStream);

    gettimeofday(&start, NULL);

    InitParser(&parser, &grammar);

    ast = Parse(&parser, tokens, &errors);

    if (IsEmptyStack(&errors))
        Semantics(&ast);

    if (IsEmptyStack(&errors)) {
    FILE *p = fopen(arguments[TWO], "wt");
    InitCodeGenerator(&generator, EmitFunc, p);
    GenerateCode(&generator, ast);
    fclose(p);
    }

    gettimeofday(&stop, NULL);
    printf("took %lu us\n", (stop.tv_sec - start.tv_sec) * 1000000 + stop.tv_usec - start.tv_usec);
    printf("took %lu s\n", stop.tv_sec - start.tv_sec);

    /*      TESTING      */
    if (IsEmptyStack(&errors))
    system("gcc out.s -o out.o && ./out.o ; echo $?");

    while (!IsEmptyStack(&errors))
    {
        Error *error = PopStack(&errors);

        printf("Error in line %d: ", error->line);
        printf(error->error);
        printf("\n");

        free(error);
    }

    // FreeCodeGenerator(&generator);
    FreeParser(&parser);
    EmptyCircularLinearLinkedList(&tokens, FreeToken);
    FreeAbstractSyntaxTree(ast);
}
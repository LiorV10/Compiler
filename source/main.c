// main.c

#include "Lexer.h"
#include "Parser.h"
#include <stdio.h>

void PrintMatch(MatchType *match)
{
    const char *ptr = match->start;

    for (; ptr < match->end; ptr++)
    {
        printf("%c", *ptr);
    }
}

void PrintList(CircularLinearLinkedListNode *lst)
{
    if (!lst)
    {
        puts("");
        return;
    };

    CircularLinearLinkedListNode *ptr = lst->nextNode;

    do
    {
        printf("[%p:%c]->", ((Transition *)ptr->info)->dest, ((Transition *)ptr->info)->symbol);
        ptr = ptr->nextNode;
    } while (ptr != lst->nextNode);

    puts("");
}

void PrintStateMachine(StateMachine *stateMachine)
{
    CircularLinearLinkedListNode *ptr = stateMachine->statesManager->nextNode;

    do
    {
        printf("[%d][%d][%p]:", ((State *)ptr->info)->isAccepting, ((State *)ptr->info)->visited, ((State *)ptr->info));
        PrintList(((State *)ptr->info)->transitionsManager);
        ptr = ptr->nextNode;
    } while (ptr != stateMachine->statesManager->nextNode);

    puts("");
}

void main(void)
{    
    const char *code = "float variable = 1637.48 + 25;       \n\
                  float *ptr = &variable;                     \n\
                  void func(void)                              \n\
                  {                                             \n\
                        puts(\"hello, world!\");                 \n\
                        for (unsigned int i = 0; i < 7; i++)      \n\
                        {                                          \n\
                            printf(\"%d\", i);                      \n\
                        }                                            \n\
                  }";
                  
    CircularLinearLinkedListNode *tokens = Tokenize(code);
    CircularLinearLinkedListNode *ptr = tokens->nextNode;
    Token *token;

    do
    {
        token = ptr->info;

        PrintMatch(token->info);
        printf(" -> %d\n", token->type);

        free(token->info);
        free(token);

        ptr = ptr->nextNode;
    }
    while (ptr != tokens->nextNode);

    EmptyCircularLinearLinkedList(&tokens);
}
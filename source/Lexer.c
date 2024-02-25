// Lexer.h

#define _LEXER_H

#include "../libs/Graph.h"
#include <stdio.h>

BOOL cmp(char a, char b) {return a == b;}

void PrintList(LinearLinkedListNode *lst)
{
    while (lst)
    {
        printf("[%d:%c]->", ((Edge*)lst->info)->dest->info, ((Edge*)lst->info)->weight);
        lst = lst->nextNode;
    }

    puts("");
}

void FromEpsilon(Graph *graph)
{
    JoinWeight(graph, AddVertex(graph, NULL, FALSE), AddVertex(graph, NULL, TRUE), NULL);
}

void FromSymbol(Graph *graph, char symbol)
{
    JoinWeight(graph, AddVertex(graph, NULL, FALSE), AddVertex(graph, NULL, TRUE), symbol);
}

void Concat(Graph *first, Graph *second)
{
    LinearLinkedListNode *vertices = second->verticesManager;

    for (; vertices; vertices = vertices->nextNode)
    {
        PushLinearLinkedList(&first->verticesManager);
        first->verticesManager->info = vertices->info;
    }
    JoinWeight(first, );
    free(second);
}

void Union(Graph *first, Graph *second)
{

}

void PrintGraph(Graph *graph)
{
    for (LinearLinkedListNode* v = graph->verticesManager; v; v = v->nextNode)
    {
        printf("%d:", ((Vertex*)v->info)->info);
        PrintList(((Vertex*)v->info)->edgesManager);
    }
}

void main(void)
{
    Graph *first = malloc(sizeof(Graph));
    Graph *second = malloc(sizeof(Graph));

    InitGraph(first, cmp);
    InitGraph(second, cmp);

    AddVertex(first, 1, FALSE);
    AddVertex(first, 2, FALSE);

    AddVertex(second, 3, FALSE);
    AddVertex(second, 4, FALSE);

    JoinWeight_(first, 1, 2, NULL);
    JoinWeight_(second, 3, 4, NULL);

    PrintGraph(first);
    PrintGraph(second);
    puts("");
    Concat(first, second);
    PrintGraph(first);
}


void main_(void)
{
    Graph *regex = malloc(sizeof(Graph));
    InitGraph(regex, cmp);

    char *pattern = "a*b*c";//"a*b*c";
    //char previous = 's';
    unsigned short state = ZERO;

    AddVertex(regex, state++, FALSE);

    for(; *pattern; pattern++)
    {
        switch (*pattern)
        {
            case '+':
                JoinWeight(regex, state - ONE, state - ONE, *(pattern - ONE));
                break;
            default:
                if (*(pattern + 1) != '*')
                {
                    AddVertex(regex, state, FALSE);
                    JoinWeight(regex, state - ONE, state, *pattern);
                    state++;
                }
                else
                {
                    JoinWeight(regex, state - ONE, state - ONE, *pattern);
                    pattern++;
                }
                break;
        }
    }

    for (LinearLinkedListNode* v = regex->verticesManager; v; v = v->nextNode)
    {
        printf("%d:", ((Vertex*)v->info)->info);
        PrintList(((Vertex*)v->info)->edgesManager);
    }

    char *str = "abbabbc";
    char *p = str;
    Vertex *current = FindVertex(regex, ZERO);
    LinearLinkedListNode *edge;
    BOOL terminated = FALSE;
    BOOL found = FALSE;

    while (!terminated && !found)
    {
        edge = current->edgesManager;
        
        while ((((Edge*)edge->info)->weight != *str && ((Edge*)edge->info)->weight != '.') &&
               (edge = edge->nextNode));

        str++;
        current = edge ? ((Edge*)edge->info)->dest : current;
        found = current->info == state - ONE;
        terminated = !edge || !*str;
    }

    printf("states: %d\n", state);
    printf("%d\n", found);
    printf("match: ");
    for (; p != str; p++)
    {
        printf("%c", *p);
    }
    puts("");
}

// #ifndef _LINEAR_LINKED_LIST_H
// #include "../libs/LinearLinkedList.h"
// #endif

// #include <string.h>

// //------------------------------------------------------
// BOOL IsLetter(char ch)
// {
//     return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
// }

// BOOL IsDigit(char ch)
// {
//     return (ch >= '0' && ch <= '9');
// }

// BOOL IsAlphaNumeric(char ch)
// {
//     return (IsLetter(ch) || IsDigit(ch));
// }

// BOOL IsNumericLiteral(char ch)
// {
//     return (IsDigit(ch) || ch == '.');
// }

// BOOL IsOperator(char ch)
// {
//     return (ch == '=' || ch == '+');
// }

// BOOL IsSeperator(char ch)
// {
//     return (ch == ',' || ch == ';');
// }
// //------------------------------------------------------

// void SkipWhitespaces(char **statement)
// {
//     while (*(*statement)++ == ' ');
//     (*statement)--;
// }

// BOOL GetNextToken(char **statement, Token *token, token_type type, BOOL(*Condition)(char))
// {
//     char *ptr = *statement;
//     token->tokenType = type;

//     while (Condition(*(*statement)++));
//     (*statement)--;

//     return (ptr != *statement);
// }

// LinearLinkedListNode* SplitStatmentIntoTokens(char *statement)
// {
//     LinearLinkedListNode *tokens = NULL;
//     LinearLinkedListNode *tokensPtr;
//     Token currentToken;
//     char *currentTokenInfo;

//     SkipWhitespaces(&statement);
//     PushLinearLinkedList(&tokens);
//     tokensPtr = tokens;

//     while (*statement)
//     {
//         AddAfterLinearLinkedList(tokensPtr);
//         tokensPtr = tokensPtr->nextNode;
//         currentTokenInfo = statement;

//         GetNextToken(&statement, &currentToken, LITERAL, IsNumericLiteral) || 
//         GetNextToken(&statement, &currentToken, IDENTIFIER, IsAlphaNumeric) || 
//         GetNextToken(&statement, &currentToken, OPERATOR, IsOperator) || 
//         GetNextToken(&statement, &currentToken, SEPERATOR, IsSeperator);

//         currentToken.tokenInfo = (char*)malloc(sizeof(char) * (statement - currentTokenInfo));
//         strncpy(currentToken.tokenInfo, currentTokenInfo, (statement - currentTokenInfo));

//         tokensPtr->info = currentToken;
//         SkipWhitespaces(&statement);
//     }

//     PopLinearLinkedList(&tokens);

//     return (tokens);
// }
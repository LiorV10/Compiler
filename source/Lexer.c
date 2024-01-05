// Lexer.h

#define _LEXER_H

#ifndef _LINEAR_LINKED_LIST_H
#include "../libs/LinearLinkedList.h"
#endif

#include <string.h>

//------------------------------------------------------
BOOL IsLetter(char ch)
{
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

BOOL IsDigit(char ch)
{
    return (ch >= '0' && ch <= '9');
}

BOOL IsAlphaNumeric(char ch)
{
    return (IsLetter(ch) || IsDigit(ch));
}

BOOL IsNumericLiteral(char ch)
{
    return (IsDigit(ch) || ch == '.');
}

BOOL IsOperator(char ch)
{
    return (ch == '=' || ch == '+');
}

BOOL IsSeperator(char ch)
{
    return (ch == ',' || ch == ';');
}
//------------------------------------------------------

void SkipWhitespaces(char **statement)
{
    while (*(*statement)++ == ' ');
    (*statement)--;
}

BOOL GetNextToken(char **statement, Token *token, token_type type, BOOL(*Condition)(char))
{
    char *ptr = *statement;
    token->tokenType = type;

    while (Condition(*(*statement)++));
    (*statement)--;

    return (ptr != *statement);
}

LinearLinkedListNode* SplitStatmentIntoTokens(char *statement)
{
    LinearLinkedListNode *tokens = NULL;
    LinearLinkedListNode *tokensPtr;
    Token currentToken;
    char *currentTokenInfo;

    SkipWhitespaces(&statement);
    PushLinearLinkedList(&tokens);
    tokensPtr = tokens;

    while (*statement)
    {
        AddAfterLinearLinkedList(tokensPtr);
        tokensPtr = tokensPtr->nextNode;
        currentTokenInfo = statement;

        GetNextToken(&statement, &currentToken, LITERAL, IsNumericLiteral) || 
        GetNextToken(&statement, &currentToken, IDENTIFIER, IsAlphaNumeric) || 
        GetNextToken(&statement, &currentToken, OPERATOR, IsOperator) || 
        GetNextToken(&statement, &currentToken, SEPERATOR, IsSeperator);

        currentToken.tokenInfo = (char*)malloc(sizeof(char) * (statement - currentTokenInfo));
        strncpy(currentToken.tokenInfo, currentTokenInfo, (statement - currentTokenInfo));

        tokensPtr->info = currentToken;
        SkipWhitespaces(&statement);
    }

    PopLinearLinkedList(&tokens);

    return (tokens);
}
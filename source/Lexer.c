// Lexer.h

#define _LEXER_H

#ifndef _LINEAR_LINKED_LIST_H
#include "../libs/LinearLinkedList.h"
#endif

#define IDENTIFIER 0x0
#define KEYWORD 0x1
#define SEPERATOR 0x2
#define OPERATOR 0x3
#define LITERAL 0x4

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
//------------------------------------------------------

BOOL GetNextIdentifier(char **statement, Token *token)
{
    char *ptr = *statement;
    unsigned short type = token->tokenType;

    token->tokenType = IDENTIFIER;

    while (IsAlphaNumeric(*(*statement)++));
    (*statement)--;

    ptr != *statement ? *(*statement)++ = '\0' : (token->tokenType = type);

    return (ptr != *statement);
}

BOOL GetNextNumericLiteral(char **statement, Token *token)
{
    char *ptr = *statement;
    unsigned short type = token->tokenType;

    token->tokenType = LITERAL;

    while (IsNumericLiteral(*(*statement)++));
    (*statement)--;

    ptr != *statement ? *(*statement)++ = '\0' : (token->tokenType = type);

    return (ptr != *statement);
}

LinearLinkedListNode* SplitStatmentsIntoTokens(char *statement)
{
    LinearLinkedListNode *tokens = NULL;
    LinearLinkedListNode *tokensPtr;
    Token currentToken;

    PushLinearLinkedList(&tokens);
    tokensPtr = tokens;

    while (*statement)
    {
        AddAfterLinearLinkedList(tokensPtr);
        tokensPtr = tokensPtr->nextNode;

        currentToken.tokenInfo = statement;

        GetNextNumericLiteral(&statement, &currentToken) ||
        GetNextIdentifier(&statement, &currentToken);

        tokensPtr->info = currentToken;
    }

    return (tokens->nextNode);
}
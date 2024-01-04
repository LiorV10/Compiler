// Lexer.h

#define _LEXER_H

#ifndef _LINEAR_LINKED_LIST_H
#include "../libs/LinearLinkedList.h"
#endif

#define IDENTIFIER 0x0
#define KEYWORD 0x1
#define SEPERATORS 0x2
#define OPERATORS 0x3

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
//------------------------------------------------------

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

        while (IsAlphaNumeric(*statement))
        {
            statement++;
        }

        *statement++ = '\0';
        currentToken.tokenType = IDENTIFIER;
        
        tokensPtr->info = currentToken;
    }

    return (tokens->nextNode);
}
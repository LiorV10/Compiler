// Lexer.h

#ifndef _REGEX_H
    #include "../libs/Regex.h"
#endif

#ifndef _CIRCULAR_LINEAR_LINKED_LIST_H
    #include "../libs/CircularLinearLinkedList.h"
#endif

#define STRING_LITERAL_TOKEN 0
#define KEYOWRD_TOKEN 1
#define IDENTIFIER_TOKEN 2
#define OPERATOR_LITERAL_TOKEN 3
#define FLOAT_LITERAL_TOKEN 4
#define INTEGER_LITERAL_TOKEN 5
#define WHITESPACE_TOKEN 6

typedef unsigned short TokenType;

typedef struct
{
    MatchType *info;
    TokenType type;
} Token;

CircularLinearLinkedListNode* Tokenize(const char *source);
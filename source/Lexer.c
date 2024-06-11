// Lexer.c

#include "Lexer.h"

Token* CreateToken(struct Match *info, TokenType type)
{
    Token *token = malloc(sizeof(Token));
    
    *token = (Token){.lexeme = info->start, .type = type};

    return (token);
}

Token* NextToken(char **source, Stack *errors, unsigned int currentLine, StateMachine *nfa)
{
    struct Match *currentMatch;
    TokenType type;
    Token *token = NULL;

    currentMatch = ExecuteRegex(nfa, *source);

    if (currentMatch)
    {
        type = currentMatch->matchType;

        *source += (currentMatch->end - currentMatch->start);

        type != WHITESPACE ? 
            token = CreateToken(currentMatch, type): 
            free(currentMatch->start);

        free(currentMatch);
    }
    else
    {
        PushStack(errors, MakeError("Unknown token `%c`", currentLine, **source));
        (*source)++;
    }

    return (token);
}

void InitLexer(Lexer *lexer)
{
    TokenType tokenType;
    unsigned short patternsSize;
    
    char *patterns[] = PATTERNS;

    patternsSize = TOKENS_NUM - ONE;
    lexer->nfa = RegexToNFA(*patterns, ZERO);

    for (tokenType = ONE; tokenType < patternsSize; tokenType++)
    {
        lexer->nfa = Union(lexer->nfa, RegexToNFA(patterns[tokenType], tokenType));
    }
}

void FreeLexer(Lexer *lexer)
{
    EmptyStateMachine(lexer->nfa);
}

CircularLinearLinkedListNode* Tokenize(Lexer *lexer, char *source, Stack *errors, unsigned int currentLine)
{
    CircularLinearLinkedListNode *tokens;
    
    InitCircularLinearLinkedList(&tokens);

    while (*source)
    {
        tokens ? 
            InsertEndCircularLinearLinkedList(&tokens) : 
            InsertLastCircularLinearLinkedList(&tokens);

        while(*source && !(tokens->info = NextToken(&source, errors, currentLine, lexer->nfa)));
    }

    if (!tokens->info)
    {
        tokens == tokens->nextNode ? 
            DeleteLastCircularLinearLinkedList(&tokens) : 
            DeleteEndCircularLinearLinkedList(&tokens);
    }

    return (tokens);
}
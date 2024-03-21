// Lexer.c

#include "Lexer.h"

#define PATTERNS_NUM 7

Token* CreateToken(Match *info, TokenType type)
{
    Token *token = malloc(sizeof(Token));
    
    *token = (Token){.info = info, .type = type};
    
    return (token);
}

Token* NextToken(char **source, StateMachine *nfas)
{
    Match *currentMatch;
    TokenType type = ZERO;
    Token *token = NULL;

    type = (TokenType)ExecuteRegex(nfas, *source, &currentMatch);

    *source += (currentMatch->end - currentMatch->start);

    type != WHITESPACE_TOKEN ?
        token = CreateToken(currentMatch, type) : 
        FreeMatch(currentMatch);

    return (token);
}

void InitLexer(Lexer *lexer)
{
    TokenType offset;

    char *patterns[PATTERNS_NUM] = 
    {
        "\"\001\006\002\"\002",  
        "wh\002i\002l\002e\002fo\002r\002vo\002i\002d\002ch\002a\002r\002un\002\007s\002i\002g\002n\002e\002d\002in\002t\002fl\002o\002a\002t\002sh\002o\002r\002t\002\010\010\010\010\010\010\010 *(){}\n\r\t\010\010\010\010\010\010\010\010\002",                    
        "_\003\010_\003\010\004\010\005\002",
        "->\002!?:,;=.-+/*&(){}[]<>\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010",                                                
        "\004\006.\002\004\006\002",   
        "\004\006",                                   
        " \n\r\t\010\010\010\006"                                            
    };

    lexer->nfa = RegexToNFA(patterns[(offset = STRING_LITERAL_TOKEN)], (void*)offset);

    for (; offset < PATTERNS_NUM; offset++)
    {
        lexer->nfa = Union(lexer->nfa, RegexToNFA(patterns[offset], (void*)offset));
    }
}

void FreeLexer(Lexer *lexer)
{
    unsigned short offset;

    for (offset = ZERO; offset < PATTERNS_NUM; offset++)
    {
       // EmptyStateMachine(lexer->nfas[offset]);
    }

    EmptyStateMachine(lexer->nfa);
}

CircularLinearLinkedListNode* Tokenize(Lexer *lexer, char *source)
{
    CircularLinearLinkedListNode *tokens;
    
    InitCircularLinearLinkedList(&tokens);

    while (*source)
    {
        tokens ? 
            InsertEndCircularLinearLinkedList(&tokens) : 
            InsertLastCircularLinearLinkedList(&tokens);

        while(*source && !(tokens->info = NextToken(&source, lexer->nfa)));
    }

    if (!tokens->info)
    {
        tokens == tokens->nextNode ? 
            DeleteLastCircularLinearLinkedList(&tokens) : 
            DeleteEndCircularLinearLinkedList(&tokens);
    }

    return (tokens);
}
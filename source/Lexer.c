// Lexer.c

#include "Lexer.h"

#define PATTERNS_NUM 7

Token* CreateToken(MatchType *info, TokenType type)
{
    Token *token = malloc(sizeof(Token));
    
    *token = (Token){.info = info, .type = type};
    
    return (token);
}

Token *NextToken(const char **source, StateMachine *nfas[PATTERNS_NUM])
{
    MatchType *currentMatch;
    TokenType type = ZERO;
    Token *token = NULL;

    while (!(currentMatch = Match(nfas[type++], *source)));

    *source = currentMatch->end;

    --type != WHITESPACE_TOKEN ? 
        token = CreateToken(currentMatch, type) : 
        free(currentMatch);

    return (token ? token : NextToken(source, nfas));
}

void InitNFAs(StateMachine *nfas[PATTERNS_NUM])
{
    unsigned short offset;

    const char *patterns[PATTERNS_NUM] = 
    {
        "\"\001\006\002\"\002",         
        "wh\002i\002l\002e\002fo\002r\002vo\002i\002d\002ch\002a\002r\002un\002\007s\002i\002g\002n\002e\002d\002in\002t\002fl\002o\002a\002t\002sh\002o\002r\002t\002\010\010\010\010\010\010\010 *(){}\n\r\t\010\010\010\010\010\010\010\010\002",                    
        "_\003\010_\003\010\004\010\005\002",
        ",;=.-+/*&(){}[]<>\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010",                                                
        "\004\006.\002\004\006\002",   
        "\004\006",                                   
       " \n\r\t\010\010\010\006"                                            
    };

    for (offset = ZERO; offset < PATTERNS_NUM; offset++)
    {
        nfas[offset] = RegexToNFA(patterns[offset]);
    }
}

CircularLinearLinkedListNode* Tokenize(const char *source)
{
    CircularLinearLinkedListNode *tokens;
    StateMachine *nfas[PATTERNS_NUM];
    unsigned short offset;
    
    InitNFAs(nfas);
    InitCircularLinearLinkedList(&tokens);

    while (*source)
    {
        tokens ? 
            InsertEndCircularLinearLinkedList(&tokens) : 
            InsertLastCircularLinearLinkedList(&tokens);

        tokens->info = NextToken(&source, nfas);
    }

    for (offset = ZERO; offset < PATTERNS_NUM; offset++)
    {
        EmptyStateMachine(nfas[offset]);
    }

    return (tokens);
}
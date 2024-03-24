// Lexer.c

#include "Lexer.h"

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
        printf("[%p:%c]->", ((Transition *)ptr->info)->dest, ((Transition *)ptr->info)->symbol == ANY_SYMBOL ? '.' : ((Transition *)ptr->info)->symbol);
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

Token* CreateToken(Match *info, TokenType type)
{
    Token *token = malloc(sizeof(Token));
    
    *token = (Token){.info = info, .type = type};
    
    return (token);
}

static TokenType type = STRING_LITERAL_TOKEN;

Token* NextToken(char **source, StateMachine *nfas[PATTERNS_NUM])
{
    Match *currentMatch;
    Token *token = NULL;
    type = ZERO;
    while (!(currentMatch = ExecuteRegex(nfas[type++], *source)));

    *source += (currentMatch->end - currentMatch->start);

    --type != WHITESPACE_TOKEN ? 
        token = CreateToken(currentMatch, type) : 
        FreeMatch(currentMatch);

    return (token);
}

void InitNFAs(StateMachine *nfas[PATTERNS_NUM])
{
    unsigned short offset;

    char *patterns[PATTERNS_NUM] = 
    {
        "\"\001\005\002\"\002",         
        "wh\002i\002l\002e\002fo\002r\002vo\002i\002d\002ch\002a\002r\002un\002\007s\002i\002g\002n\002e\002d\002in\002t\002fl\002o\002a\002t\002sh\002o\002r\002t\002\010\010\010\010\010\010\010 *(){}\n\r\t\010\010\010\010\010\010\010\010\002",                    
        "_\003\010_\003\010\004\010\005\002",
        ",;=.-+/*&(){}[]<>#\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010",                                                
        "\004\006.\002\004\006\002",  
        "\004\006",                                   
       " \n\r\t\010\010\010\006"                                            
    };

    for (offset = ZERO; offset < PATTERNS_NUM; offset++)
    {
        nfas[offset] = RegexToNFA(patterns[offset]);
    }
}

void InitLexer(Lexer *lexer)
{
    InitNFAs(lexer->nfas);
}

void FreeLexer(Lexer *lexer)
{
    unsigned short offset;

    for (offset = ZERO; offset < PATTERNS_NUM; offset++)
    {
        EmptyStateMachine(lexer->nfas[offset]);
    }
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

        while(*source && !(tokens->info = NextToken(&source, lexer->nfas)));
    }

    if (!tokens->info)
    {
        tokens == tokens->nextNode ? 
            DeleteLastCircularLinearLinkedList(&tokens) : 
            DeleteEndCircularLinearLinkedList(&tokens);
    }

    return (tokens);
}
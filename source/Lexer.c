// Lexer.c

#include "Lexer.h"
/*
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
        printf("[%d][%d][%p]:", ((State *)ptr->info)->info, ((State *)ptr->info)->visited, ((State *)ptr->info));
        PrintList(((State *)ptr->info)->transitionsManager);
        ptr = ptr->nextNode;
    } while (ptr != stateMachine->statesManager->nextNode);

    puts("");
}
*/

Token* CreateToken(struct Match *info, TokenType type)
{
    Token *token = malloc(sizeof(Token));
    
    *token = (Token){.lexeme = info->start, .type = type};

    return (token);
}

Token* NextToken(char **source, StateMachine *nfa)
{
    struct Match *currentMatch;
    TokenType type;
    Token *token = NULL;

    currentMatch = ExecuteRegex(nfa, *source);
    type = currentMatch->matchType;

    *source += (currentMatch->end - currentMatch->start);

    type != WHITESPACE ? 
        token = CreateToken(currentMatch, type) : 
        free(currentMatch->start);

    free(currentMatch);

    return (token);
}

void InitLexer(Lexer *lexer)
{
    TokenType tokenType;
    unsigned short patternsSize;
    char *patterns[] = 
    {
        "\"\001\005\002\"\002",
        "_\003\010_\003\010\004\010\005\002",
        "vo\002i\002d\002",
        "ma\002i\002n\002",
        "in\002t\002",
        "fl\002o\002a\002t\002",
        "lo\002n\002g\002",
        "do\002u\002b\002l\002e\002",
        "sh\002o\002r\002t\002",
        "ch\002a\002r\002",
        "un\002s\002i\002g\002n\002e\002d\002",
        "fo\002r\002",
        "if\002",
        "el\002s\002e\002",
        "wh\002i\002l\002e\002",
        "+",
        "-",
        ">",
        "<",
        "=",
        "*",
        "/",
        "%",
        ",",
        ";",
        "{",
        "}",
        "(",
        ")",
        "&",
        //"wh\002i\002l\002e\002fo\002r\002vo\002i\002d\002ch\002a\002r\002un\002\007s\002i\002g\002n\002e\002d\002in\002t\002fl\002o\002a\002t\002sh\002o\002r\002t\002\010\010\010\010\010\010\010",             
        //",;=.-+/*&(){}[]<>#\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010",                                                
        "\004\006.\002\004\006\002",  
        "\004\006",
       " \n\r\t\010\010\010\006"                                            
    };

    patternsSize = sizeof(patterns)/sizeof(char*);
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
// main.c

#include "../libs/Regex.h"
#include <stdio.h>

void PrintMatch(MatchType *match)
{
    const char *ptr = match->start;

    for (; ptr < match->end; ptr++)
    {
        printf("%c", *ptr);
    }
}

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
        printf("[%p:%c]->", ((Transition *)ptr->info)->dest, ((Transition *)ptr->info)->symbol);
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

#define PATTERNS_NUM 7

void main(void)
{
    MatchType *currentMatch;
    StateMachine *nfas[PATTERNS_NUM];
    char *patterns[PATTERNS_NUM] = 
    {
         // ".+"
        "\"\001\006\002\"\002",         

        // (while|for|void|(un)?signed|int|float|short)[^a-zA-Z\d_]
        "wh\002i\002l\002e\002fo\002r\002vo\002i\002d\002ch\002a\002r\002un\002\007s\002i\002g\002n\002e\002d\002in\002t\002fl\002o\002a\002t\002sh\002o\002r\002t\002\010\010\010\010\010\010\010 *(){}\n\r\t\010\010\010\010\010\010\010\010\002",
        
        // [_a-zA-Z][_a-zA-Z\d]*                              
        "_\003\010_\003\010\004\010\005\002",
        
        // operators
        ",;=.-+/*&(){}[]<>\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010\010",  

        // \d+.\d+                                                    
        "\004\006.\002\004\006\002",

        // \d+        
        "\004\006",

         // \s+                                      
       " \n\r\t\010\010\010\006"                                            
    };

    const char *types[PATTERNS_NUM] = 
    {
        "string literal",
        "keyword",
        "identifier",
        "operator",
        "float literal",
        "integer literal",
        "whitespace"
    };
    
    const char *code = "float variable = 1637.48 + 25;       \n\
                  float *ptr = &variable;                     \n\
                  void func(void)                              \n\
                  {                                             \n\
                        puts(\"hello, world!\");                 \n\
                        for (unsigned int i = 0; i < 7; i++)      \n\
                        {                                          \n\
                            printf(\"%d\", i);                      \n\
                        }                                            \n\
                  }";

    for (int i = ZERO; i < PATTERNS_NUM; i++)
    {
        nfas[i] = RegexToNFA(patterns[i]);
    }

    /* TESTING TOKENS */
    puts("\n------- Tokens: -------\n");

    typedef struct
    {
        MatchType *match;
        const char *type;
    } Token;

    unsigned short offset = ZERO;
    CircularLinearLinkedListNode *tokens;

    InitCircularLinearLinkedList(&tokens);

    while (*code)
    {
        while ((currentMatch = Match(nfas[offset], code)))
        {
            code = currentMatch->end;

            if (strcmp(types[offset], "whitespace"))
            {
                !tokens ?
                    InsertLastCircularLinearLinkedList(&tokens) :
                    InsertEndCircularLinearLinkedList(&tokens);

                tokens->info = malloc(sizeof(Token));
                *(Token*)tokens->info = (Token){.match = currentMatch, .type = types[offset]};
            }
            else
            {
                free(currentMatch);
            }
            
            offset = ZERO;
        }

        offset++;
    }

    CircularLinearLinkedListNode *ptr = tokens->nextNode;
    Token *token;

    do
    {
        token = ptr->info;

        PrintMatch(token->match);
        printf(" -> %s\n", token->type);

        free(token->match);
        free(token);

        ptr = ptr->nextNode;
    }
    while (ptr != tokens->nextNode);

    EmptyCircularLinearLinkedList(&tokens);

    for (int i = ZERO; i < PATTERNS_NUM; i++)
    {
        EmptyStateMachine(nfas[i]);
    }
}
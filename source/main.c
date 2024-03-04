// main.c

#include "../libs/Regex.h"
#include <stdio.h>

void PrintRange(char *start, char *end)
{
    for (; start < end; start++)
    {
        printf("%c", *start);
    }
}

#define PATTERNS_NUM 7

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

void PrintGraph(StateMachine *graph)
{
    CircularLinearLinkedListNode *ptr = graph->statesManager->nextNode;

    do
    {
        printf("[%d][%d][%p]:", ((State *)ptr->info)->isAccepting, ((State *)ptr->info)->visited, ((State *)ptr->info));
        PrintList(((State *)ptr->info)->transitionsManager);
        ptr = ptr->nextNode;
    } while (ptr != graph->statesManager->nextNode);

    puts("");
}

void main(void)
{
    MatchType *currentMatch;
    StateMachine *nfas[PATTERNS_NUM];
    char *patterns[PATTERNS_NUM] = 
    {
         // ".+"
        "\"\001\006\002\"\002",         

        // (void|unsigned|int|float|short)[^a-zA-Z\d_]
        "vo\002i\002d\002ch\002a\002r\002un\002s\002i\002g\002n\002e\002d\002in\002t\002fl\002o\002a\002t\002sh\002o\002r\002t\002\010\010\010\010\010 *({\n\r\t\010\010\010\010\010\010\002",
        
        // [_a-zA-Z][_a-zA-Z\d]*                              
        "_\003\010_\003\010\004\010\005\002",
        
        // [;=.-]
        ";=.-+/*&\010\010\010\010\010\010\010",  

        // \d+.\d+                                                    
        "\004\006.\002\004\006\002",

        // \d+        
        "\004\006",

         // \s+                                      
        " \n\r\t\010\010\010\006"                                            
    };

    char *type[PATTERNS_NUM] = 
    {
        "string literal",
        "keyword",
        "identifier",
        "operator",
        "float literal",
        "integer literal",
        "whitespace"
    };
    
    char *code = "float variable = 2343.48 + 25;\nchar *ptr = &variable;";

    for (int i = 0; i < PATTERNS_NUM; i++)
    {
        nfas[i] = RegexToNFA(patterns[i]);
    }

    puts("\n------- Tokens: -------\n");

    unsigned short offset = ZERO;

    while (*code)
    {
        while ((currentMatch = Match(nfas[offset], code)))
        {
            if (strcmp(type[offset], "whitespace"))
            {
                PrintRange(currentMatch->start, currentMatch->end);
                printf(" -> %s\n", type[offset]);
            }
            code = currentMatch->end;
            offset = ZERO;
        }

        offset++;
        free(currentMatch);
    }
}
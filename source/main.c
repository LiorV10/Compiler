// main.c


#include "../libs/Regex.h"
#include <stdio.h>

#define PATTERNS_NUM 7

void print_range(char *s, char *e)
{
    for (; s < e; s++)
    {
        printf("%c", *s);
    }
}

void main(void)
{
    MatchType *currentMatch;
    StateMachine *nfas[PATTERNS_NUM];
    char *patterns[PATTERNS_NUM] = 
    {
         // ".+"
        "\"\001+\002\"\002",         

        // int|float|[^a-zA-Z\d_]
        "in\002t\002fl\002o\002a\002t\002| \n|\002",
        
        // [_a-zA-Z][_a-zA-Z\d]*                                      
        "_\003|\003\004|*\002",//"_abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ||||||||||||||||||||||||||||||||||||||||||||||||||||+",
        
        // [;=]
        ";=.||",  

        // \d+.\d+                                                    
        "\004+.\002\004+\002",//"0123456789|||||||||+.\0020123456789|||||||||+\002",

        // \d+        
        "\004+",//"01|2|3|4|5|6|7|8|9|+",

         // \s+                                      
        " \n\r\t|||+"                                              
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

    char *code = "float x\n = 2343.48;";

    for (int i = 0; i < PATTERNS_NUM; i++)
    {
        nfas[i] = RegexToNFA(patterns[i]);
    }

    puts("\n------- Tokens: -------\n");

    while (*code)
    {
        for (int i = 0; i < PATTERNS_NUM; i++)
        {
            if ((currentMatch = Match(nfas[i], code)))
            {
                print_range(currentMatch->start, currentMatch->end);
                printf(" -> %s\n", type[i]);
                code = currentMatch->end;
                i = 0;
            }

            free(currentMatch);
        }
    }
}
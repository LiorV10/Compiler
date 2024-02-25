#include <stdlib.h>
#include <stdio.h>
#include "CommonMacros.h"

#define ANY_CHAR '.'
#define ANY_LETTER '@'
#define ANY_DIGIT '$'
#define WHITESPACE '#'
#define ZERO_OR_ONE '?'
#define ZERO_OR_MORE '*'
#define MATCH_RANGE '^'
#define NEGEATE_OPTIONS '!'
#define START_OPTIONS '['
#define END_OPTIONS ']'
#define ESCAPE_CHAR '~'

BOOL IsLetter(char ch)
{
    return ((ch >= 'a' && ch <= 'z') || (ch >= 'A' && ch <= 'Z'));
}

BOOL IsWhitespace(char ch)
{
    return (ch == ' ' || ch == '\n' || ch == '\t' || ch == '\r');
}

BOOL MatchChar(char plainChar, char patternChar, BOOL escape)
{
    if (escape) return plainChar == patternChar;

    switch(patternChar)
    {
        case ANY_CHAR:
            return TRUE;
        case WHITESPACE:
            return IsWhitespace(plainChar);
        case ANY_LETTER:
            return IsLetter(plainChar);
        case ANY_DIGIT:
            return IS_DIGIT(plainChar);
        default:
            return plainChar == patternChar;
    }

    // return plainChar == patternChar ||
    //     (!escape && (patternChar == ANY_CHAR ||
    //     (patternChar == WHITESPACE && IsWhitespace(plainChar)) ||
    //     (patternChar == ANY_LETTER && IsLetter(plainChar)) || 
    //     (patternChar == ANY_DIGIT && IS_DIGIT(plainChar))));
}

BOOL MatchClass(char plainChar, char *patternClass)
{
    BOOL match = FALSE;
    BOOL negate;

    patternClass++;
    negate = *patternClass == NEGEATE_OPTIONS && *patternClass++;

    while (!(match = (negate ^ MatchChar(plainChar, *patternClass++, FALSE))) && *patternClass != END_OPTIONS);

    return (match);
}

typedef struct
{
    char *start;
    char *end;
} Match;

BOOL MatchesStart(char *plain, char *pattern, Match** matches, int* matchesCount)
{
    BOOL escape;
    char *p;

    if (!*pattern) return TRUE;
    escape = *pattern == ESCAPE_CHAR;
    pattern += escape;

    p = pattern;

    if (*pattern == START_OPTIONS && !escape)
    {
        while (*pattern++ != END_OPTIONS);
        pattern--;
    }

    if (*(pattern + ONE) == ZERO_OR_MORE)
    {
        while (*plain && (*pattern == END_OPTIONS ? MatchClass(*plain, p) : MatchChar(*plain, *pattern, escape)) &&
              (!*(pattern + TWO + (*(pattern + TWO) == MATCH_RANGE) + (*(pattern + THREE) == ESCAPE_CHAR)) || 
              !MatchesStart(plain, pattern + TWO + (*(pattern + TWO) == MATCH_RANGE) + (*(pattern + THREE) == ESCAPE_CHAR), matches, matchesCount))) 
              //(!MatchChar(*plain, *(pattern + TWO + (*(pattern + TWO) == MATCH_RANGE) + (*(pattern + THREE) == ESCAPE_CHAR)), 
              //  *(pattern + THREE) == ESCAPE_CHAR))))
        {
            plain++;
        }

        return MatchesStart(plain, pattern + TWO, matches, matchesCount);
    }

    if (*(pattern + ONE) == ZERO_OR_ONE)
    {
        return MatchesStart(plain + ONE * ((*pattern == END_OPTIONS ? MatchClass(*plain, p) : MatchChar(*plain, *pattern, escape))), pattern + TWO, matches, matchesCount);
    }
    
    if (*pattern == MATCH_RANGE && !escape && matches)
    {
        Match* match = *matches + *matchesCount - ONE;

        if (*matchesCount && match->end == NULL)
        {
            match->end = plain;
        }
        else
        {
            *matches = (Match*)realloc(*matches, ++*matchesCount * sizeof(Match));
            match = *matches + (*matchesCount - ONE);
            match->start = plain;
            match->end = NULL;
        }

        return MatchesStart(plain, pattern + ONE, matches, matchesCount);
    }
    
    char *ptr = plain;
    while (*plain && (*pattern == END_OPTIONS ? MatchClass(*plain, p) : MatchChar(*plain, *pattern, escape)) &&
            (*(pattern + ONE) != ZERO_OR_MORE && *(pattern + ONE) != ZERO_OR_ONE))
    {
        plain++;
        pattern++;
    }

    return (ptr != plain) && MatchesStart(plain, pattern, matches, matchesCount);
    
}

void PrintMatch(Match* match)
{
    printf("'");
    for (; match->start < match->end; match->start++)
    {
        printf("%c", *match->start);
    }

    puts("'");
}

// TODO: Implement found matches using (double?)linear linked list
void main(void)
{
    char *s = "for (int i = 0; i < 10; i++) { print(i); print(2i); }";//"int _x4 = 4434.33423;";//"int x = 5.4;";   //"33043aaaaabeeeeeegefe";
    char *p = "for#*(^[!;]*^;#*^[!;]*^;#*^[!;]*^)#{ ^print(i);^";//"^w*^s*^[w_].*^s*=s*^d*~.?d*^;";   // "~*.~*": Floating number;
    Match *result = NULL;
    int count = 0;

    printf("%d\n", MatchesStart(s, p, &result, &count));
    
    for (; count; count--)
    {
        PrintMatch(result++);
    }
}
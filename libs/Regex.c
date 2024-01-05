#include <stdlib.h>
#include "CommonMacros.h"

#define ANY_CHAR '.'
#define ANY_LETTER 'w'
#define ANY_DIGIT 'd'
#define WHITESPACE 's'
#define ZERO_OR_ONE '?'
#define ZERO_OR_MORE '*'
#define MATCH_RANGE '^'
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
    return plainChar == patternChar ||
        (!escape && (patternChar == ANY_CHAR ||
        (patternChar == WHITESPACE && IsWhitespace(plainChar)) || 
        (patternChar == ANY_LETTER && IsLetter(plainChar)) || 
        (patternChar == ANY_DIGIT && IS_DIGIT(plainChar))));
}

typedef struct
{
    char *start;
    char *end;
} Match;

BOOL MatchesStart(char *plain, char *pattern, Match** matches, int* matchesCount)
{
    BOOL escape;

    if (!*pattern) return TRUE;
    escape = *pattern == ESCAPE_CHAR;
    pattern += escape;

    if (*(pattern + ONE) == ZERO_OR_MORE)
    {
        while (*plain && MatchChar(*plain, *pattern, escape) &&
              (!*(pattern + TWO) || 
              (!MatchChar(*plain, *(pattern + TWO + (*(pattern + TWO) == '^') + (*(pattern + THREE) == ESCAPE_CHAR)), 
                *(pattern + THREE) == ESCAPE_CHAR)))) // || 1 || !MatchesStart(plain, pattern + TWO))))
        {
            plain++;
        }

        return MatchesStart(plain, pattern + TWO, matches, matchesCount);
    }
    else if (*(pattern + ONE) == ZERO_OR_ONE)
    {
        return MatchesStart(plain + ONE * (MatchChar(*plain, *pattern, escape)), pattern + TWO, matches, matchesCount);
    }
    else if (*pattern == MATCH_RANGE)
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
    else
    {
        char *ptr = plain;
        while (*plain && MatchChar(*plain, *pattern, escape) &&
              (*(pattern + ONE) != ZERO_OR_MORE && *(pattern + ONE) != ZERO_OR_ONE))
        {
            plain++;
            pattern++;
        }

        return (ptr != plain) && MatchesStart(plain, pattern, matches, matchesCount);
        //return (*pattern == *plain || !*pattern || *pattern == ANY_CHAR || (*pattern == WHITESPACE && IsWhitespace(*plain)) || (*pattern == ANY_LETTER && IsLetter(*plain)) || (*pattern == ANY_DIGIT && IS_DIGIT(*plain))) && MatchesStart(plain, pattern);
    }
}

void PrintMatch(Match* match)
{
    for (; match->start < match->end; match->start++)
    {
        printf("%c", *match->start);
    }

    puts("");
}

void main(void)
{
    char *s = "w";//"int x = 4434.33423;";//"int x = 5.4;";   //"33043aaaaabeeeeeegefe";
    char *p = "^~w^";//"^w*^s*^w_.*^s*=s*^d*/.?d*^;";   // "~*.~*": Floating number;
    Match *result = NULL;
    int count = 0;

    printf("\n%d\n", MatchesStart(s, p, &result, &count));
    
    for (; count; count--)
    {
        PrintMatch(result++);
    }
}
void PrintMatch(Match *match)
{
    char *ptr = match->start;

    for (; ptr < match->end; ptr++)
    {
        printf("%c", *ptr);
    }

    printf("\t");
}
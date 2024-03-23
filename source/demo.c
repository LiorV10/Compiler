#include <stdio.h>

void main(void)
{
    int a = 5;
    int *p = &a;

    puts("output: ");
    printf("%d", *p);
    puts("");
}
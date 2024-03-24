#include <stdio.h>

void main(void)
{
    int b = 4;
    int *p = &b;
    int a = 5 + 3 * *p;
    
    p = &a;

    puts("output: ");
    printf("%d", *p);
    puts("");
}
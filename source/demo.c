void main(void)
{
    int intv;
    int b = 4;
    int *p = &b;
    int a = 15 + 3 * *p;
    
    p = &a;

    puts("output: ");
    printf("%d", *p);
    puts("");
}
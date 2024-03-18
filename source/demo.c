void func(int num)
{
    puts("hello world!");
    for (unsigned int i = 0; i < num; i++)
    {
        printf("%d\n", i);
    }
}

void main(void)
{
    int variable = 10;
    int *ptr = &variable;

    func(*ptr);
}
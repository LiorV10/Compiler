int printf();
int puts();
long malloc();
void free();
long strdup();

struct MOSHE
{
    long aa;
    long *bb;
    long *bbb;
    int xx;
    int yy;
    int *zz;
    int **mm;
    int ***dd;
    int q;
    int *qq;
    long k;
};

struct MOSHE2
{
    int x;
    int y;
    struct MOSHE mozs;
    struct MOSHE *pmozs;
};

struct Node;

struct Node
{
    int info;
    struct Node *next;
};

void init(struct Node **lst)
{
    (*lst) = 0;
}

void push(struct Node **lst, int info)
{
    struct Node *new = malloc(12);

    (*new).next = *lst;
    (*new).info = info;

    *lst = new;
}

int pop(struct Node **lst)
{
    int value = (**lst).info;

    struct Node *temp = *lst;

    *lst = (**lst).next;
    free(temp);

    return (value);
}

int main()
{
    int x = 3;
    struct MOSHE mosh;
    struct MOSHE mosh2;

    mosh.aa = 3;
    mosh.bb = &mosh.aa;
    mosh.bbb = mosh.bb;
    mosh.xx = 7;
    mosh.yy = 8;
    mosh.zz = &mosh.xx;
    mosh.mm = &mosh.zz;
    mosh.dd = &mosh.mm;
    mosh.q = mosh.aa;
    mosh.qq = &mosh.q;
    mosh.k = mosh.q;

    int _1 = 777;
    int *__1 = &_1;
    int **___1 = &__1;

    **___1 = 888;
    
    struct MOSHE2 moshe2;

    moshe2.x = _1;
    moshe2.y = **___1;

    mosh2.dd = &___1;

    mosh.zz = &mosh.yy;
    mosh.yy = mosh.yy + *&*&*&mosh.xx;

    printf("%d is moshe!\n", moshe2.x * moshe2.y);
    
    x = **&mosh.bb;

    printf("malloc'd value: %d\n", x);

    if (!(mosh.k + 1))
    {
        printf("%lu is max!\n", mosh.k);
    }
    else
    {
        printf("%lu is not max\n", mosh.k);
    }

    char *ptr = "Result:\t%d\t%d\t%d\t%d\t%d\n";

    char *string = strdup("hello, world!");
    puts(string);
    free(string);
    puts(string);

    printf("\n");
    printf(ptr, mosh.aa, *mosh.bb, *&mosh.aa, **&mosh.bb, *mosh.qq);
    printf("Char:\t%c\t%c\t%c\t%c\t%c\n", *ptr, *(ptr + (*mosh.zz - 2 * mosh.xx)), ptr[mosh.aa], ptr[***mosh.dd + *mosh.bb],
        (ptr + mosh.aa)[ptr[*mosh.zz - 2 * mosh.xx] - ptr[***mosh.dd + *mosh.bb] - (mosh.aa + 1)]);

    printf(ptr, *mosh.zz + mosh.yy, mosh.xx, mosh.aa, *mosh.bb/mosh.aa, ***mosh2.dd);
    printf(ptr, -(-***mosh.dd / -**mosh.mm), -*mosh.bb, *mosh.bb, *&mosh.aa****mosh.dd**mosh.bb, ***mosh.dd);
    printf("\n");

    moshe2.mozs = mosh;
    moshe2.pmozs = &mosh;

    struct MOSHE *temp = &moshe2.mozs;
    struct MOSHE *ptemp = moshe2.pmozs;

    x = ****&*&moshe2.mozs.dd;
    x = x + *(*ptemp).bb;

    struct MOSHE *tpm = malloc(80);

    (*tpm).aa = x;
    printf("AA:%d\n", (*tpm).aa);

    free(tpm);

    if ((*temp).aa == x)
    {
        printf("%d = %d\n", (*temp).aa, x);
    }
    else
    {
        printf("%d != %d\n", (*temp).aa, x);
    }

    struct Node *lst;

    init(&lst);

    push(&lst, 5);
    push(&lst, 7);
    push(&lst, 9);

    x = pop(&lst);
    printf("%d\n", x);
    x = pop(&lst);
    printf("%d\n", x);
    x = (*lst).info;
    printf("%d\n", x);

    return (x);
}
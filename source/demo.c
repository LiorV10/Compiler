int printf();
int puts();
long malloc();
void free();
long strdup();
long strlen();

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
    int k;
    int yy;
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
    *lst = 0;
}

void push(struct Node **lst, int info)
{
    struct Node *new = malloc(12);

    new->next = *lst;
    new->info = info;

    *lst = new;
}

int pop(struct Node **lst)
{
    struct Node *temp = *lst;
    int value = temp->info;

    *lst = (*lst)->next;
    free(temp);

    return (value);
}

int is_empty(struct Node *lst)
{
    return (!lst);
}

void print_list_iter(struct Node *lst, int *length)
{
    struct Node *ptr;

    *length = 0;

    for (ptr = lst; ptr; ptr = ptr->next)
    {
        printf("[%d]->", ptr->info);
        (*length) = *length + 1;
    }

    puts("||");
}

void print_list_rec();

void print_list_rec(struct Node *lst)
{
    if (is_empty(lst))
    {
        puts("||");
        return;
    }

    printf("[%d]->", lst->info);
    print_list_rec(lst->next);
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

    moshe2.k = _1;
    moshe2.yy = **___1;

    mosh2.dd = &___1;

    mosh.zz = &mosh.yy;
    mosh.yy = mosh.yy + mosh.xx;

    printf("%d is moshe!\n", moshe2.k * moshe2.yy);
    
    x = **&mosh.bb;

    printf("malloc'd value: %d\n", x);

    char *ptr = "Result:\t%d\t%d\t%d\t%d\t%d\n";

    char *string = strdup("hello, world!");
    puts(string);
    printf("%c:%c:%c\n", "hello, world"[2], ptr[0], ptr[ptr[1] - string[strlen(string) - 2]]);
    
    printf("\n");
    printf(ptr, mosh.aa, *mosh.bb, *&mosh.aa, **&mosh.bb, *mosh.qq);
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

    x = ***&**&*&moshe2.mozs.dd;
    x = x + *(*ptemp).bb;

    struct MOSHE *tpm = malloc(80);

    (*tpm).aa = x;
    printf("AA:%d\n", (*tpm).aa);
    
    free(tpm);

    if (*temp->bb == x)
    {
        printf("%d = %d\n", temp->aa, x);
    }
    else
    {
        printf("%d != %d\n", temp->aa, x);
    }

    struct Node *lst;
    int length;

    init(&lst);

    push(&lst, 3);
    push(&lst, -5);
    push(&lst, -(-7));
    push(&lst, 9);

    printf("[%d]->", lst->info);
    printf("[%d]->", lst->next->info);
    printf("[%d]->", lst->next->next->info);
    printf("[%d]->||\n", lst->next->next->next->info);

    print_list_iter(lst, &length);
    print_list_rec(lst);

    for (; !is_empty(lst); )
    {
        printf("[%d]->", pop(&lst));
    }
    
    puts("||");
    printf("length: %d\n", length);

    int arr[20];
    int mat[10][4];
    int y = x / 6;
    int return_value = x + y;

    mat[x/3][x/9] = return_value;

    arr[x ^ x] = x;
    arr[x] = arr[!x] - x;
    y = (x = arr[arr[x]] / 9);
    x = 3 * y;

    printf("%d\n", mat[x][y] == *(*(mat + x) + y));
    printf("Val:%d\n", mat[x][y]);

    return (mat[x][y]);
}
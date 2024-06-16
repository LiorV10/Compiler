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
    struct MOSHE *pmozs;
};

struct Node;

typedef struct Node
{
    int info;
    struct Node *next;
} Node;

void init(Node **lst)
{
    *lst = 0;
}

void push(Node **lst, int info)
{
    Node *new = malloc(12);
    new->next = *lst;
    new->info = info;

    *lst = new;
}

int pop(Node **lst)
{
    Node *temp = *lst;
    int value = temp->info;

    *lst = (*lst)->next;
    free(temp);

    return (value);
}

int is_empty(Node *lst)
{
    return (!lst);
}

void print_list_iter(Node *lst, int *length)
{
    Node *ptr;

    *length = 0;

    for (ptr = lst; ptr; ptr = ptr->next)
    {
        printf("[%d]->", ptr->info);
        *length = *length + 1;
    }

    puts("||");
}

void print_list_rec();

void print_list_rec(Node *lst)
{
    if (is_empty(lst))
    {
        puts("||");
        return;
    }

    printf("[%d]->", lst->info);
    print_list_rec(lst->next);

    return;
}

typedef char boolean;

int main()
{
    int aa = 3;
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

    int lll = 6;
    printf("lll: %d\n", lll);
    // hello, world!

    moshe2.k = _1;
    moshe2.yy = **___1;

    mosh2.dd = &___1;

    mosh.zz = &mosh.yy;
    mosh.yy = mosh.yy + mosh.xx;

    printf("%d is moshe!\n", moshe2.k * moshe2.yy);
    
    aa = **&mosh.bb;

    printf("malloc'd value: %d\n", aa);

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

    if ((&mosh2)->bb == mosh2.bb)
    {
        puts("ok!");
        aa = 18;
    }
    else
    {
        puts("not ok!");
        aa = 0;
    }

    Node *lst;
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

    // for (; !is_empty(lst); )
    //    printf("[%d]->", pop(&lst));

    Node *lstPtr;
    int i = 0;

    puts("\n");

    for (lstPtr = lst; lstPtr; lstPtr = lstPtr->next)
    {
        printf("[%d]:: ", i = i + 1);
        print_list_iter(lstPtr, &length);
    }
    
    puts("||");
    printf("length: %d\n", length);

    int arr[20];
    int mat[10][5];
    int y = aa / 6;
    int return_value = aa + y;

    mat[aa/3][aa/9] = return_value;

    arr[aa ^ aa] = aa;
    arr[aa] = arr[!aa] - aa;
    y = (aa = arr[arr[aa]] / 9);
    aa = 3 * y;

    printf("%d\n", mat[aa][y] == *(*(mat + aa) + y));
    printf("Val:%d\n", mat[aa][y]);

    printf("result:%d\n", (aa * y / y + aa + (4 + aa * (y + aa))) - y + (aa * 2 + y / 3) / y);

    struct teststruct
    {
        int x; int y;
    } test;

    typedef struct teststruct testtype;

    test.x = 4;
    test.y = 5;

    printf("%d\n", test.x);

    {
        test.y = 8;

        struct teststruct
        {
            int x;
        } test;

        testtype test2;

        test2.y = 0;
        test.x = 3;

        {
            printf("%d\n", test.x);
            
            struct teststruct
            {
                int x;
            } test;

            typedef struct teststruct testtype; 

            testtype test3;

            test.x = 2;

            printf("%d\n", test.x);
            // printf("%d\n", test.y); // illegal
            // printf("%d\n", test3.y); // illegal
            printf("%d\n", test2.y); // llegal

        }

        int *ptr = mat;

        printf("%d\n", test.x);
    }

    printf("%d\n", test.x);
    printf("%d\n", test.y);

    return (mat[aa][y]);
}
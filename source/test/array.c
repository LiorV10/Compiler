int printf();
int puts();

typedef short vector[11];

void print_vec(short vec[], int n)
{
    int i;

    for (i = 0; i < n; i = i + 1)
    {
        printf("%3hd", vec[i]);
    }

    puts("");
}

void print_mat(short mat[][11], int n, int m)
{
    int i;
    
    for (i = 0; i < n; i = i + 1)
    {
        print_vec(mat[i], m);
    }

    puts("");
}

int sum_mat(short (*mat)[11], int n, int m)
{
    int i;
    int size = n * m;
    int sum = 0;
    short *ptr = mat;

    printf("Same #1: %d\n", ptr == &mat[0][0]);
    printf("Same #2: %d\n", ptr[15] == mat[1][4] & ptr[15] == mat[0][15]);

    for (i = 0; i < size; i = i + 1)
    {
        sum = sum + ptr[i];
    }

    return sum;
}

int dummy()
{
    puts("hello, world!");
}

int main()
{
    short mat[11][11];

    mat[0][0] = 1;
    mat[0][1] = 2;
    mat[0][2] = 3;
    mat[1][0] = 4;
    mat[1][1] = 5;
    mat[1][2] = 6;
    mat[2][0] = 7;
    mat[2][1] = 8;
    mat[2][2] = 9;
    mat[3][0] = 10;
    mat[3][1] = 11;
    mat[3][2] = 12;

    print_mat(mat, 4, 3);
    printf("Sum #1: %d\n\n", sum_mat(mat, 4, 3));

    int i;
    int j;

    for (i = 0; i < 11; i = i + 1)
    {
        for (j = 0; j < 11; j = j + 1)
        {
            mat[i][j] = i * j;
        }
    }

    print_mat(mat, 11, 11);
    printf("Sum #2: %d\n\n", sum_mat(mat, 11, 11));

    short vec_2[5];

    vec_2[0] = 1;
    vec_2[1] = 2;
    vec_2[2] = 3;
    vec_2[3] = 4;
    vec_2[4] = 5;

    print_vec(vec_2, 5);

    vector vec;

    for (i = 0; i < 11; i = i + 1)
    {
        vec[i] = i + 1;
    }

    print_vec(vec, 11);

    return 1;
}
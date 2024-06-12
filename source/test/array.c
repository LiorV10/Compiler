int printf();
int puts();

void print_vec(int vec[], int n)
{
    int i;

    for (i = 0; i < n; i = i + 1)
    {
        printf("%d\t", vec[i]);
    }

    puts("");
}

void print_mat(int mat[][3], int n, int m)
{
    int i;
    
    for (i = 0; i < n; i = i + 1)
    {
        print_vec(mat[i], m);
    }

    puts("");
}

int sum_mat(int (*mat)[3], int n, int m)
{
    int i;
    int size = n * m;
    int sum = 0;
    int *ptr = mat;

    printf("Same #1: %d\n", ptr == &mat[0][0]);
    printf("Same #2: %d\n", ptr[4] == mat[1][1] & ptr[4] == mat[0][4]);

    for (i = 0; i < size; i = i + 1)
    {
        sum = sum + ptr[i];
    }

    return sum;
}

int main()
{
    int mat[4][3];

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
    printf("Sum: %d\n\n", sum_mat(mat, 4, 3));

    int i;
    int j;

    for (i = 0; i < 4; i = i + 1)
    {
        for (j = 0; j < 3; j = j + 1)
        {
            mat[i][j] = i + j;
        }
    }

    print_mat(mat, 4, 3);

    int vec[5];

    vec[0] = 1;
    vec[1] = 2;
    vec[2] = 3;
    vec[3] = 4;
    vec[4] = 5;

    print_vec(vec, 5);

    return 0;
}
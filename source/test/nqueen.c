int printf();

typedef char boolean;

void printSolution(int board[][8])
{
    int i;
    int j;

	for (i = 0; i < 8; i = i + 1) 
    {
		for (j = 0; j < 8; j = j + 1) 
        {
			if(board[i][j])
				printf("Q ");
			else
				printf(". ");
		}
		printf("\n");
	}
}

boolean isSafe(int board[][8], int row, int col)
{
	int i;
    int j;

	for (i = 0; i < col; i = i + 1)
		if (board[row][i])
			return 0;

    j = col;

	for (i = row; i >= 0 && j >= 0; i = i - 1)
    {
		if (board[i][j])
			return 0;

        j = j - 1;
    }

    j = col;

	for (i = row; j >= 0 && i < 8; i = i + 1)
    {
		if (board[i][j])
			return 0;

        j = j - 1;
    }

	return 1;
}

boolean solveNQUtil();

boolean solveNQUtil(int board[][8], int col)
{
    int i;

	if (col >= 8)
		return 1;

	for (i = 0; i < 8; i = i + 1) 
    {
		if (isSafe(board, i, col)) 
        {

			board[i][col] = 1;

			if (solveNQUtil(board, col + 1))
				return 1;

			board[i][col] = 0;
		}
	}
	return 0;
}

boolean solveNQ()
{
	int board[8][8];    
    int i;

    for (i = 0; i < 64; i = i + 1)
    {
        board[0][i] = 0;
    }

	if (solveNQUtil(board, 0) == 0) 
    {
		printf("Solution does not exist");
		return 0;
	}

	printSolution(board);
	return 1;
}

int main()
{
	solveNQ();
	return 0;
}
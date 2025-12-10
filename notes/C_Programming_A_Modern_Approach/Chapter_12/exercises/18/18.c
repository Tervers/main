/*

Write the evaluate_position function described in Exercise 13 of Chapter 9. Use
    pointer arithmetic - not array subscripting - to visit array elements. Use a
    single loop instead of nested loops.

int evaluate_position(char board[8][8])
{
    int white = 0, black = 0;

    for (int i = 1; i <= 8; i++)
        for (int j = 1; j <= 8; j++){
            if (board[i][j] == 'Q')
                white += 9;
            if (board[i][j] == 'q')
                black += 9;
            if (board[i][j] == 'R')
                white += 5;
            if (board[i][j] == 'r')
                black += 5;
            if (board[i][j] == 'B')
                white += 3;
            if (board[i][j] == 'b')
                black += 3;
            if (board[i][j] == 'N')
                white += 3;
            if (board[i][j] == 'n')
                black += 3;
            if (board[i][j] == 'P')
                white += 1;
            if (board[i][j] == 'p')
                black += 1;
        }

    return white - black;
}

*/

int evaluate_position(char *board[8][8], int *score)
{
    int white = 0, black = 0;
    char *positions = board;

    for (positions = board; positions < board + 63; positions++)
        

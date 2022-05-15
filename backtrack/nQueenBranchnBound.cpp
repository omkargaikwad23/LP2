#include <bits/stdc++.h>
using namespace std;
#define N 8

void printSolution(int board[N][N]){
    for (int i = 0; i < N; i++){
        for (int j = 0; j < N; j++)
            cout << " " << board[i][j];
        cout << "\n";
    }
}

bool isSafe(int row, int col, int slashCode[N][N],
            int backslashCode[N][N], bool rowLookup[],
            bool slashCodeLookup[], bool backslashCodeLookup[]){
    if (slashCodeLookup[slashCode[row][col]] ||
        backslashCodeLookup[backslashCode[row][col]] || rowLookup[row])
        return false;
    return true;
}

bool solveNQueensUtil(int board[N][N], int col,
                      int slashCode[N][N], int backslashCode[N][N],
                      bool rowLookup[N], bool slashCodeLookup[], bool backslashCodeLookup[]){
    if (col >= N)
        return true;
    /* Consider this column and try placing this queen in all rows one by one */
    for (int i = 0; i < N; i++)
    {
        if (isSafe(i, col, slashCode, backslashCode, rowLookup, slashCodeLookup, backslashCodeLookup)){
            board[i][col] = 1;
            rowLookup[i] = true;
            slashCodeLookup[slashCode[i][col]] = true;
            backslashCodeLookup[backslashCode[i][col]] = true;

            if (solveNQueensUtil(board, col + 1, slashCode, backslashCode,
                                 rowLookup, slashCodeLookup, backslashCodeLookup))
                return true;

            board[i][col] = 0;
            rowLookup[i] = false;
            slashCodeLookup[slashCode[i][col]] = false;
            backslashCodeLookup[backslashCode[i][col]] = false;
        }
    }

    /* If queen can not be place in any row in
        this column col then return false */
    return false;
}

bool solveNQueens()
{
    int board[N][N];
    memset(board, 0, sizeof board);

    int slashCode[N][N];
    int backslashCode[N][N];

    bool rowLookup[N] = {false};

    // keep two arrays to tell us which diagonals are occupied
    bool slashCodeLookup[2 * N - 1] = {false};
    bool backslashCodeLookup[2 * N - 1] = {false};

    for (int r = 0; r < N; r++)
        for (int c = 0; c < N; c++){
            slashCode[r][c] = r + c,
            backslashCode[r][c] = r - c + 7;
        }

    if (solveNQueensUtil(board, 0, slashCode, backslashCode,
                         rowLookup, slashCodeLookup, backslashCodeLookup) == false){
        cout << "Solution does not exist";
        return false;
    }
    printSolution(board);
    return true;
}

int main(){
    solveNQueens();
    return 0;
}

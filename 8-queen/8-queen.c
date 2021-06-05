#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

int check(int *board, int next_row, int next_col){
    for(int i = 0; i < next_row; i++)
        if(board[i] == next_col || next_row - i == abs(board[i] - next_col)) return 0;
    return 1;
}

int queen(int *board, int row, int n) {
    if(row == n){
        return 1;
    }
    int sum = 0;
    for(int i = 0; i < n; i++){
        if(check(board, row, i)){
            board[row] = i;
            sum += queen(board, row+1, n);
        } 
    }
    return sum;
}

int main(int argc, char *argv[]) {
    int n;
    assert(argc == 2);
    n = atoi(argv[1]);

    int *board = (int *)calloc(n, sizeof(int));
    printf("%d\n", queen(board, 0, n));

    return 0;
}

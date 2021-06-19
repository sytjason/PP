#include<stdio.h>
#include<stdlib.h>
#define MAXN 20

void printBoard(char board[MAXN][MAXN], int n){
	for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++)
			printf("%c", board[i][j]);
		printf("\n");
	}
}

int check(char board[MAXN][MAXN], int placement[MAXN], int row, int col){
	if(board[row][col] == '*')return -1;
	for(int i = 0; i < row; i++){
		if(placement[i] == col || row - i == abs(col - placement[i]))
			return -1;
	}
	return 1;
}

int do_queen(char board[MAXN][MAXN], int placement[MAXN], int row, int n){
	if(row == n)return 1;
	int sum = 0;
	#pragma omp parallel for firstprivate(placement) reduction(+ : sum)
	for(int i = 0; i < n; i++){
		if(check(board, placement, row, i) == 1){
			placement[row] = i;
			sum += do_queen(board, placement, row+1, n);
		}
	}
	return sum;
}

int main(){
	int n;
	int placement[MAXN];
	int c = 1;
	char board[MAXN][MAXN];

	while(scanf("%d ", &n) == 1){
		for(int i = 0; i < n; i++){
			for(int j = 0; j < n; j++){
				scanf("%c ", &board[i][j]);
			}
		}

		int sum = 0;
		#pragma omp parallel for private(placement) reduction(+ : sum)
		for(int i = 0; i < n; i++){
			if(board[0][i] == '*')continue;
			placement[0] = i;
			sum += do_queen(board, placement, 1, n);
		}

		printf("Case %d: %d\n",c++, sum);
	}
	return 0;
}
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#define MAXN 20

void *goQueen(void *);
int check(int *, int, int);
int queen(int *, int, int);
int numSol = 0;
int n;

int main(int argc, char *argv[]) {
    int *board;
    pthread_t thread_ids[MAXN];
    assert(argc == 2);
    n = atoi(argv[1]);
    assert(n <= MAXN);
    pthread_attr_t attr ;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    for (int i = 0; i < n; i++) {
        board = (int *)calloc(n, sizeof(int));
        board[0] = i;
        int err;
        err = pthread_create(&thread_ids[i], NULL, goQueen, (void *)board);
        if(err){
            printf("pthread create error!\n");
            exit(-1);
        }
    }

    for (int i = 0; i < n; i++) {
        int *num;
        pthread_join(thread_ids[i], (void **)&num);
        numSol += *num;
    }

    printf("%d\n", numSol);
    pthread_exit(NULL);

    return 0;
}

void *goQueen(void *board) {
    int *sum = (int *)malloc(sizeof(int));
    *sum = queen((int *)board, 1, n);
    pthread_exit((void *)sum);
}

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


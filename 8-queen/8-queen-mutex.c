#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<pthread.h>
#define MAXN 20

void *goQueen(void *);
int check(int *, int, int);
void queen(int *, int, int);
int numSol = 0;
int n;
pthread_mutex_t numSolLock;

int main(int argc, char *argv[]) {
    int *board;
    pthread_t thread_ids[MAXN];
    assert(argc == 2);
    n = atoi(argv[1]);
    assert(n <= MAXN);
    pthread_attr_t attr ;
    pthread_attr_init (&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_mutex_init(&numSolLock, NULL);

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
        pthread_join(thread_ids[i], NULL);
    }

    printf("%d\n", numSol);
    pthread_mutex_destroy(&numSolLock);
    pthread_exit(NULL);

    return 0;
}

void *goQueen(void *board) {
    queen((int *)board, 1, n);
    pthread_exit(NULL);
}

int check(int *board, int next_row, int next_col){
    for(int i = 0; i < next_row; i++)
        if(board[i] == next_col || next_row - i == abs(board[i] - next_col)) return 0;
    return 1;
}

void queen(int *board, int row, int n) {
    if(row == n){
        pthread_mutex_lock(&numSolLock);
        numSol++;
        pthread_mutex_unlock(&numSolLock);
    }
    for(int i = 0; i < n; i++){
        if(check(board, row, i)){
            board[row] = i;
            queen(board, row+1, n);
        } 
    }
}


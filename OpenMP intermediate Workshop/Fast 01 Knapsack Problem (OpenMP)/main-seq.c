#include<stdio.h>
#include<stdlib.h>
#include <string.h>
#define MAXN 10001
#define MAXM 1000001
#define max(a, b) (((a) > (b)) ? (a) : (b))

struct object{
	int weight;
	int value;
};

void print(struct object items[], int N){
	for(int i = 0; i < N; i++){
		printf("%d %d\n", items[i].weight, items[i].value);
	}
}

int main(){
	int N, M;
	struct object items[MAXN];
	int dp[2][MAXM];
	memset(dp, 0, sizeof(dp));

	scanf("%d %d", &N, &M);
	for(int i = 0; i < N; i++){
		int weight, value;
		scanf("%d %d", &weight, &value);
		items[i].weight = weight, items[i].value = value;
	}


	for(int i = 0; i < N; i++){
		int w = items[i].weight, v = items[i].value;
		if(i % 2){ // assign new dp from dp[1] to dp[0]
			for(int j = 0; j < w; j++) dp[0][j] = dp[1][j];
			for(int j = w; j <= M; j++) dp[0][j] = max(dp[1][j-w] + v, dp[1][j]);
		}else{ // assign new dp from dp[0] to dp[1]
			for(int j = 0; j < w; j++) dp[1][j] = dp[0][j];
			for(int j = w; j <= M; j++) dp[1][j] = max(dp[0][j-w] + v, dp[0][j]);
		}
	}

	printf("%d\n", (N-1) % 2 ? dp[0][M] : dp[1][M]);

	return 0;
}
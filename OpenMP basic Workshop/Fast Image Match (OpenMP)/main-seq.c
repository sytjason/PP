#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<limits.h>

// #define DEBUG
void print_image(int n, int m, int matrix[]) {
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", matrix[i*m+j]);
		}
		printf("\n");
	}
}


int main(int argc, char *argv[]) {
	int na, ma, nb, mb;
	while(scanf("%d %d %d %d", &na, &ma, &nb, &mb) == 4){
		assert(na >= nb && ma >= mb);
		int *A = (int*)calloc(na*ma, sizeof(int));
		int *B = (int*)calloc(nb*mb, sizeof(int));
		for(int i = 0; i < na*ma; i++){
			scanf("%d ", &A[i]);
		}
		for(int i = 0; i < nb*mb; i++){
			scanf("%d ", &B[i]);
		}

#ifdef DEBUG
		printf("A: na = %d, ma = %d\n", na, ma);
		print_image(na, ma, A);

		printf("B: nb = %d, mb = %d\n", nb, mb);
		print_image(nb, mb, B);
#endif

		int sumMin = INT_MAX;
		int idx[2];
		for(int iStart = 0; iStart <= na-nb; iStart++){
			for(int jStart = 0; jStart <= ma-mb; jStart++){
				int sum = 0;
				for(int i = 0; i < nb; i++){
					for(int j = 0; j < mb; j++){
						// d = A[iStart+i][jStart+j] - B[i][j]
						int d = A[(iStart+i)*ma+jStart+j]-B[i*mb+j];
						// printf("i = %d, j = %d, d = %d \n", i, j, d);
						sum += d*d;
					} 
				}

				#ifdef DEBUG
				printf("diff(%d,%d)=%d ", iStart+1, jStart+1, sum);
				#endif

				if(sum < sumMin){
					sumMin = sum;
					idx[0] = iStart;
					idx[1] = jStart;
				}
			}
			#ifdef DEBUG
			printf("\n");
			#endif
		}

		printf("%d %d\n", idx[0]+1, idx[1]+1);

		free(A);
		free(B);
	}


	return 0;
}
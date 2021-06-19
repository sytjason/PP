#include<stdio.h>
#include<stdlib.h>
#include<assert.h>
#include<limits.h>
#include<omp.h>

#define MAX 500
#define MAX_THREADS 12

// #define DEBUG
void print_image(int n, int m, int matrix[]) {
	for(int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			printf("%d ", matrix[i*m+j]);
		}
		printf("\n");
	}
}

struct ans{
	int sumMin;
	int i, j;
};

int main(int argc, char *argv[]) {
	int na, ma, nb, mb;
	int A[MAX*MAX], B[MAX*MAX], D[MAX*MAX];
	int num_threads = omp_get_num_procs();
	while(scanf("%d %d %d %d", &na, &ma, &nb, &mb) == 4){
		assert(na >= nb && ma >= mb);

		for(int i = 0; i < na; i++){
			for(int j = 0; j < ma; j++)
			scanf("%d ", &A[i*ma+j]);
		}
		for(int i = 0; i < nb; i++){
			for(int j = 0; j < mb; j++)
			scanf("%d ", &B[i*mb+j]);
		}

#ifdef DEBUG
		printf("A: na = %d, ma = %d\n", na, ma);
		print_image(na, ma, A);

		printf("B: nb = %d, mb = %d\n", nb, mb);
		print_image(nb, mb, B);
#endif

		struct ans ans_all[MAX_THREADS];
		for(int i = 0; i < num_threads; i++)
			ans_all[i].sumMin = INT_MAX;

		#pragma omp parallel for firstprivate(A, B)
		for(int iStart = 0; iStart <= na-nb; iStart++){
			for(int jStart = 0; jStart <= ma-mb; jStart++){
				int sum = 0;
				for(int i = 0; i < nb; i++){
					for(int j = 0; j < mb; j++){
						int d = A[(iStart+i)*ma+jStart+j] - B[i*mb+j];
						// printf("i = %d, j = %d, d = %d \n", i, j, d);
						sum += d * d;
					} 
				}

				#ifdef DEBUG
				printf("threadid=%d diff(%d,%d)=%d\n", omp_get_thread_num(), iStart+1, jStart+1, sum);
				#endif

				if(sum < ans_all[omp_get_thread_num()].sumMin){
					int tid = omp_get_thread_num();
					ans_all[tid].sumMin = sum;
					ans_all[tid].i = iStart;
					ans_all[tid].j = jStart;
				}
			}
			#ifdef DEBUG
			printf("\n");
			#endif
		}

		int sumMin = INT_MAX;
		int idx[2];
		for(int i = 0; i < num_threads; i++){
			if(ans_all[i].sumMin < sumMin){
				sumMin = ans_all[i].sumMin;
				idx[0] = ans_all[i].i;
				idx[1] = ans_all[i].j;
			}
		}
		printf("%d %d\n", idx[0]+1, idx[1]+1);
	}


	return 0;
}
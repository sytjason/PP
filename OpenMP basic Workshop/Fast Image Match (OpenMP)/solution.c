#include <stdio.h>
#include <limits.h>
#define MAXN 512
int A[MAXN][MAXN], B[MAXN][MAXN];
int C[MAXN][MAXN];
int main() {
    int Ah, Aw, Bh, Bw, x;
    int cases = 0;
    while(scanf("%d %d %d %d", &Ah, &Aw, &Bh, &Bw) == 4) {
        for (int i = 0; i < Ah; i++)
            for (int j = 0; j < Aw; j++)
                scanf("%d", &x), A[i][j] = x;
        for (int i = 0; i < Bh; i++)
            for (int j = 0; j < Bw; j++)
                scanf("%d", &x), B[i][j] = x;
        int Ch = Ah - Bh, Cw = Aw - Bw;
        int bx = -1, by = -1;
        int diff = INT_MAX;
        #pragma omp parallel for
        for (int i = 0; i <= Ch; i++) {
            for (int j = 0; j <= Cw; j++) {
                int d = 0;
                for (int p = 0; p < Bh; p++) {
                    for (int q = 0; q < Bw; q++) {
                        d += (B[p][q] - A[i+p][j+q])*(B[p][q] - A[i+p][j+q]);
                    }                    
                }
                C[i][j] = d;
            }
        }
        for (int i = 0; i <= Ch; i++) {
            for (int j = 0; j <= Cw; j++)
                if (C[i][j] < diff)
                    diff = C[i][j], bx = i, by = j;
        }
 
        printf("%d %d\n", bx + 1, by + 1);
    }
    return 0;
}
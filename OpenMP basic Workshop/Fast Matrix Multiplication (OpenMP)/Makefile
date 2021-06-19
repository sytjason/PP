all:
	gcc -std=c99 -Wall -Wextra ./main.c ./matrix.c -o main-seq
	gcc -std=c99 -Wall -Wextra ./main-omp.c ./matrix-omp.c -o main-transpose-seq
	gcc -std=c99 -Wall -Wextra -fopenmp ./main-omp.c ./matrix-omp.c -o main-transpose-omp  

run-seq:
	time ./main-seq <4.in
	
run-transpose-seq:
	time ./main-transpose-seq < 4.in

run-transpose-omp:
	time ./main-transpose-omp < 4.in



all:
	gcc -std=c99 -Wall -Wextra ./main-seq.c -o main-seq
	gcc -std=c99 -Wall -Wextra -fopenmp ./main-omp.c -o main-omp
	gcc -std=c99 -Wall -Wextra -fopenmp ./solution.c -o solution

run-seq-0:
	time ./main-seq < 0.in

run-omp-0:
	time ./main-omp < 0.in

run-seq-1:
	time ./main-seq < 1.in

run-omp-1:
	time ./main-omp < 1.in

run-seq-2:
	time ./main-seq < 2.in

run-omp-2:
	time ./main-omp < 2.in

run-seq-3:
	time ./main-seq < 3.in

run-omp-3:
	time ./main-omp < 3.in

run-seq-4:
	time ./main-seq < 4.in

run-omp-4:
	time ./main-omp < 4.in

run-seq-5:
	time ./main-seq < 5.in

run-omp-5:
	time ./main-omp < 5.in
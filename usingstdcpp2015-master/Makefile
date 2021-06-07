CC = g++
CFLAGS = -Wall -Wextra
LIBS = -lpthread

all: aos_vs_soa compact_aos_vs_soa filtered_sum linear_traversal matrix_sum parallel_count poly_containers random_access_aos_vs_soa

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

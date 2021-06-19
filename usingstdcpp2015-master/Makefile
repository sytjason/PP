CC = g++
CFLAGS = -Wall -Wextra
LIBS = -lpthread -g

all: aos_vs_soa compact_aos_vs_soa filtered_sum linear_traversal matrix_sum parallel_count poly_containers random_access_aos_vs_soa linear_traversal_vector linear_traversal_list linear_traversal_shuflist

%: %.cpp
	$(CC) $(CFLAGS) $< -o $@ $(LIBS)

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <pthread.h>
#include <inttypes.h>
#include "utils.h"
 
#define MAXN 10000005
#define MAX_THREADS 8

uint32_t prefix_sum[MAXN];
/*pthread_barrier_t barr;*/

struct parameter {
    uint32_t key;                    // key for the encrypt
    size_t pos;                      // starting position of each thread
    size_t size;                     // size of the prefix sum array
    size_t threads_num;              // total number of threads
    size_t threadId;                 // the number of thread
    uint32_t *lastElements;          // base pointer to lastElements array
    uint32_t *lastElements_next;     // base pointer to lastElements array
};

void *subPrefixSum(void *arg){
    struct parameter par = *((struct parameter *)arg);

    uint32_t sum = 0;
    for (uint32_t i = 0; i < par.size; i++) {
        sum += encrypt(par.pos + i, par.key);
        prefix_sum[par.pos+i] = sum;
    }

    pthread_exit((void *)(&prefix_sum[par.pos+par.size-1]));
}

void *updateRest(void *arg) {
    struct parameter par = *((struct parameter *)arg);
    for (int i = 0; i < par.size-1; i++) {
        prefix_sum[par.pos+i] += prefix_sum[par.pos-1];
    }
    pthread_exit(NULL);
}

/*void *lastElementPrefixSum(void *arg) {*/
    /*struct parameter par = *((struct parameter *)arg);*/
    
    /*for(int i = 1; i < par.threads_num; i *= 2){*/
        /*if(par.threadId - i > 0)*/
            /*par.lastElements_next[par.threadId] += par.lastElements[par.threadId-i];*/
        /*pthread_barrier_wait(&barr);*/
        /*par.lastElements = par.lastElements_next;*/
    /*}*/

    /*prefix_sum[par.pos+par.size-1] = par.lastElements[par.threadId];*/
    /*pthread_exit(NULL);*/
/*}*/

int main() {
    int n;
    uint32_t key;

    pthread_attr_t attr;
    pthread_t thread_ids[MAX_THREADS];
    struct parameter thread_pars[MAX_THREADS];

    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

    while (scanf("%d %" PRIu32, &n, &key) == 2) {
        // compute prefix sum of each thread
        // store last element of each prefix sum
        // into lastElements[]
        int threads_num = (MAX_THREADS >= n ? n : MAX_THREADS);
        int remain = n % threads_num;
        int quotient = n / threads_num;
        uint32_t *lastElements = (uint32_t *)calloc(threads_num, sizeof(uint32_t));
        uint32_t *lastElements_next = (uint32_t *)calloc(threads_num, sizeof(uint32_t));
        /*pthread_barrier_init(&barr, NULL, threads_num);*/

        /*printf("main: compute prefix sum of %d numbers with key = %d\n", n, key);*/

        size_t pos = 1;
        for (size_t t = 0; t < threads_num; t++) {
            struct parameter par = {.pos = pos, 
                             .size = t < n%threads_num ? (quotient + 1) : (quotient), 
                              .key = key,
                      .threads_num = threads_num,
                     .lastElements = lastElements,
                .lastElements_next = lastElements_next,
                         .threadId = t};
            thread_pars[t] = par;
            pos += par.size;
            /*printf("thread %d: compute preSum pos = %d, size = %d\n", t, thread_pars[t].pos, thread_pars[t].size);*/
            pthread_create(&thread_ids[t], &attr, subPrefixSum, (void *)(&thread_pars[t]));
        }

        for (size_t t = 0; t < threads_num; t++) {
            uint32_t *last_pre_sum;
            pthread_join(thread_ids[t], (void **)&last_pre_sum);
            lastElements[t] = *last_pre_sum;
            /*printf("thread %d: join lastPreSum = %d\n", t, lastElements[t]);*/
        }
        /*printf("prefix_sum[]: ");*/
        /*for (size_t i = 1; i <= n; i++) printf(" %d", prefix_sum[i]);*/
        /*printf("\n");*/

        // calculate prefix sum of last elements
        /*printf("computing last elements pre sum\n");*/

        // using O(log(p)) algo
        /*for (size_t t = 0; t < threads_num; t++) {*/
            /*pthread_create(&thread_ids[t], &attr, lastElementPrefixSum, (void *)(&thread_pars[t]));*/
        /*}*/
        /*for (size_t t = 0; t < threads_num; t++) {*/
            /*pthread_join(thread_ids[t], NULL);*/
        /*}*/
        
        // using O(p) method
        uint32_t sum = 0;
        for(size_t t = 0; t < threads_num; t++) {
            sum += lastElements[t];
            lastElements[t] = sum;
        }
        for(size_t t = 0; t < threads_num; t++) {
            prefix_sum[thread_pars[t].pos+thread_pars[t].size-1] = lastElements[t];
        }
        /*printf("last elements pre sum finished\n");*/
        /*printf("prefix_sum[]: ");*/
        /*for (size_t i = 1; i <= n; i++) printf(" %d", prefix_sum[i]);*/
        /*printf("\n");*/

        // add the rest prefix sum with the ones that are summed
        for (size_t t = 1; t < threads_num; t++) {
            pthread_create(&thread_ids[t], &attr, updateRest, (void *)(&thread_pars[t]));
        }
        for (size_t t = 1; t < threads_num; t++) {
            pthread_join(thread_ids[t], NULL);
        }
        /*printf("rest elements update finished\n");*/
        /*printf("prefix_sum[]: ");*/
        /*for (size_t i = 1; i <= n; i++) printf(" %d", prefix_sum[i]);*/
        /*printf("\n");*/

        output(prefix_sum, n);
        /*pthread_barrier_destroy(&barr);*/
    }
    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

    return 0;
}

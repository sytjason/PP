#include<pthread.h>
#include<stdio.h>
#include<stdlib.h>
#include<assert.h>

#define MAX_N 20

void *hello(void *arg) {
    int id = *((int *)arg);
    printf("hello thread id: %d\n", id);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    assert(argc == 2);
    pthread_t thread_ids[MAX_N];
    pthread_attr_t attr;
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);
    pthread_attr_init(&attr);

    int n = atoi(argv[1]);
    assert(n < MAX_N);

    int *ids = (int *)calloc(n, sizeof(int));

    for(int i = 0; i < n; i++) {
        ids[i] = i;
        int err = pthread_create(&thread_ids[i], NULL, hello, (void *)(&ids[i]));
        if (err) {
            printf("pthread creation error!\n");
            exit(-1);
        }
    }

    for (int i = 0; i < n; i++) {
        pthread_join(thread_ids[i], NULL);
    }

    pthread_attr_destroy(&attr);
    pthread_exit(NULL);

    return 0;
}

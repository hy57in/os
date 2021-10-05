#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#define NUMBER_OF_THREADS 10

void *print_hello_world(void *tid) {
    printf("Hello World. Greetings from thread %d\n", *(int *)tid);
    free(tid);
    pthread_exit(NULL);
}

int main(int argc, char *argv[]) {
    pthread_t threads[NUMBER_OF_THREADS];
    int status, i;

    for(i = 0; i < NUMBER_OF_THREADS; i++) {
        int *arg = malloc(sizeof(*arg));
        if(arg == NULL) {
            fprintf(stderr, "memory error\n");
            exit(EXIT_FAILURE);       
        }

        *arg = i;
        printf("Main here. Creating thread %d\n", *arg);
        status = pthread_create(&threads[i], NULL, print_hello_world, arg);

        if(status != 0) {
            printf("error code %d\n", status);
            exit(-1);
        }
    }
    sleep(1);
    exit(0);
}

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *thread_function(void *arg);

int run_now = 1;

int main() {
    int res;
    pthread_t a_thread;
    void *thread_result;
    int print_count1 = 0;

    res = pthread_create(&a_thread, NULL, thread_function, NULL);

    while(print_count1++ < 20) {
        if(run_now == 1) {
            printf("1");
            run_now = 2;
        } else {
            sleep(1);
        }
    }

    printf("\nWaiting for thread to finish...\n");
    res = pthread_join(a_thread, &thread_result);
    printf("Thread joined\n");
    exit(EXIT_FAILURE);
}

void *thread_function(void *arg) {
    int print_count2 = 0;

    while(print_count2++ < 20) {
        if(run_now == 2) {
            printf("2");
            run_now = 1;
        } else {
            sleep(1);
        }
    }
}
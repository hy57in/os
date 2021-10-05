#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>

void *producer(void *arg);
void *consumer(void *arg);

int gNumber = 0;
int run_now = 1;

int main() {
    int producer_result, consumer_result;
    pthread_t producer_thread, consumer_thread;
    void *producer_thread_result, *consumer_thread_result;

    producer_result = pthread_create(&producer_thread, NULL, producer, NULL);
    printf("\nWaiting for producer thread to finish...\n");
    consumer_result = pthread_create(&consumer_thread, NULL, consumer, NULL);
    printf("\nWaiting for consumer thread to finish...\n");

    producer_result = pthread_join(producer_thread, &producer_thread_result);
    printf("producer thread join\n");
    consumer_result = pthread_join(consumer_thread, &consumer_thread_result);
    printf("consumer thread join\n");

    if(producer_thread_result == consumer_thread_result) {
        printf("SUCCESS");
    } else {
        printf("FAIL");
    }
    exit(EXIT_SUCCESS);

}

void *producer(void *arg) {
    int print_count_p = 0;
    int sum_p = 0;

    while(print_count_p++ < 100) {
        if(run_now == 1) {
            int randomNumber = rand() % 100; // generate 0~99 number
            gNumber = randomNumber;
            printf("randomNumber : %d\n", randomNumber);
            sum_p += randomNumber;
            run_now = 2;
        } else {
            sleep(1);
        }
    }
    
}

void *consumer(void *arg) {
    int print_count_c = 0;
    int sum_c = 0;

    while(print_count_c++ < 100) {
        if(run_now == 2) {
            printf("sgNumber : %d\n", gNumber);
            run_now = 1;
            sum_c += gNumber;
        } else {
            sleep(1);
        }
    }
}
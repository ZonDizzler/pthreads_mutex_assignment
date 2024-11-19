#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

int var = 0;

pthread_mutex_t lock;


void* write_data(void* arg) {
    pthread_mutex_lock(&lock);
    
    int i;
    //add one to var 10 times, over 10 seconds
    for (int i = 0; i < 10; i++){
        var = var + 1;
        printf("thread_1: Wrote data %d\n", var);
        sleep(1); //pause for one second
    }
    pthread_mutex_unlock(&lock);
    return NULL;
}

void* read_data(void *arg) {
    pthread_mutex_lock(&lock);  // Lock mutex
    printf("thread_2: Read data %d\n", var);
    pthread_mutex_unlock(&lock);  // Unlock mutex
    return NULL;
}


int main() {
    //declare the two threads
    pthread_t thread_1, thread_2;
    
    // Initialize the mutex
    pthread_mutex_init(&lock, NULL);
    
    printf("main: Initial value of var: %d\n", var);
    
    // Create threads
    pthread_create(&thread_1, NULL, write_data, NULL);
    pthread_create(&thread_2, NULL, read_data, NULL);
    
    // Wait for threads to finish
    pthread_join(thread_1, NULL);
    pthread_join(thread_2, NULL);
    
    // Destroy the mutex
    pthread_mutex_destroy(&lock);
    
    printf("main: Final value of var: %d\n", var);

    return 0;
}

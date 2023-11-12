#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <math.h>
#include <time.h>
#include <stdint.h>
//:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
#define SIZE 1024
#define NUM_THREADS 10
//============================================================================
int a[SIZE][SIZE];
int b[SIZE][SIZE];
long int c[SIZE][SIZE];
//:::::::::::::::::::::::::::::::::::::::::::::: Data structure to pass to each thread
typedef struct {
    int start_row;
    int end_row;
} threadData;

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; // Mutex for synchronization

//-------------------------------------------------------------------- Initialize matrices a, b, and c
void init_matrices() {
      for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
        }
    }

}
//--------------------------------------------------------------------------------------- Function to perform matrix multiplication for a specific range of rows
void* multiply_matrices_range(void* thread_data_void) {
   threadData* thread_data = (threadData*)thread_data_void;
    int start = thread_data->start_row;
    int end = thread_data->end_row;

    for (int i = start; i < end; i++) {
        for (int j = 0; j < SIZE; j++) {
            pthread_mutex_lock(&mutex); // Lock before updating the result matrix
            long int sum = 0; // Use a temporary variable to accumulate the result
            for (int k = 0; k < SIZE; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum; // Update the result matrix after all calculations
            pthread_mutex_unlock(&mutex); // Unlock after updating the result matrix
        }
    }
    return NULL;
}
//--------------------------------------------------------------------------------------------------Main
int main() {
    // Check if matrix multiplication is possible
    if (SIZE <= 0 || SIZE % 2 != 0) {
        printf("Matrix multiplication is not possible with the current SIZE value.\n");
        return 1; // Matrix multiplication is not possible
    }
//:::::::::::::::::::::::::::::::::::::::::::
    clock_t start = clock();	// Record start time
    init_matrices();    // Initialize matrices
//:::::::::::::::::::::::::::::::::::::::::::
    pthread_t threads[NUM_THREADS];
    threadData thread_data[NUM_THREADS]; // Define thread_data array
    int rows_per_thread = SIZE / NUM_THREADS; // Calculate the number of rows each thread will handle
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::


    // Create and run threads
    for (int i = 0; i < NUM_THREADS; i++) {
        thread_data[i].start_row = i * rows_per_thread;
        thread_data[i].end_row = (i + 1) * rows_per_thread;

        pthread_create(&threads[i], NULL, multiply_matrices_range, (void*)&thread_data[i]);
    }

    // Wait for all threads to finish
    for (int i = 0; i < NUM_THREADS; i++) {
        pthread_join(threads[i], NULL);
    }

    clock_t end = clock();  // Record end time
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::: Calculate and print the time taken for matrix multiplication
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Elapsed time using %d Pthreads: %f seconds\n", NUM_THREADS, cpu_time_used);
    pthread_mutex_destroy(&mutex); // Destroy the mutex

    return 0;
}


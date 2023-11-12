#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>
//:::::::::::::::::::::::::::::::::::::::::::::
#define SIZE 1024
#define NUM_THREADS 10
//==================================================================================
int a[SIZE][SIZE];
int b[SIZE][SIZE];
long int c[SIZE][SIZE];

void init_matrices() {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
        }
    }
}
//---------------------------------------------------------------------------------
void multiply_matrices() {
#pragma omp parallel for collapse(2) num_threads(NUM_THREADS)
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            long int sum = 0;
            for (int k = 0; k < SIZE; k++) {
                sum += a[i][k] * b[k][j];
            }
            c[i][j] = sum;
        }
    }
}
//----------------------------------------------------------------------------------------
int main() {
    if (SIZE <= 0 || SIZE % 2 != 0) {
    	  printf("Matrix multiplication is not possible with the current SIZE value.\n");
        return 1;
    }
    init_matrices();
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
   double start = omp_get_wtime();;
   
    	multiply_matrices();
    	
    double end = omp_get_wtime();;
//::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::
    printf("Elapsed time using %d OpenMP threads: %f seconds\n", NUM_THREADS, (double)(end - start));
    return 0;
}


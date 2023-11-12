#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//:::::::::::::::::::::::::::::::::::::::::::::::::
#define SIZE 1024
//===================================================================================================
int a[SIZE][SIZE];
int b[SIZE][SIZE];
long int c[SIZE][SIZE];
//-------------------------------------------------------------------------------------------------------- Initialize matrices a, b, and c
void init_matrices() {
  for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            a[i][j] = rand() % 10;
            b[i][j] = rand() % 10;
        }
    }

}
// -------------------------------------------------------------------------------------------------Perform matrix multiplication
void multiply_matrices() {

    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            for (int k = 0; k < SIZE; k++) {
                c[i][j] += a[i][k] * b[k][j];
            }
        }
    }
}
//----------------------------------------------------------------------------------------------Main
int main() {
    // Check if matrix multiplication is possible
     if (SIZE <= 0 || SIZE % 2 != 0) {
        printf("Matrix multiplication is not possible with the current SIZE value.\n");
        return 1; // Matrix multiplication is not possible
    }
//::::::::::::::::::::::::::::::::::::::::::: Initialize matrices
    init_matrices();   
//::::::::::::::::::::::::::::::::::::::::::::::
    clock_t start = clock();	// Record start time

   	 multiply_matrices(); // Perform matrix multiplication

    clock_t end = clock();  // Record end time
//:::::::::::::::::::::::::::::::::::::::::::::::::::: Calculate and print the time taken for matrix multiplication
    double cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;
    printf("Multiplication SEQUENTIAL TIME took %lf seconds\n", cpu_time_used);

    return 0;
}


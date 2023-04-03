// Eray Genç 19050111005

#include "hellomake.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>



int main(int argc, char *argv[]) {

    // mpirun -n 3 ./your_id 1003 1003 output.txt
    // 1,2-> 1003, 3-> output.txt

    int rank, size;
    //size = atoi(argv[2]);

    MPI_Init(NULL, NULL);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);


    int MATRIX_SIZE = atoi(argv[2]);
    long int seed = 19050111005;  // seed value as my number
    double **matrix;
    double *vector;
    char *filename = argv[3];
    FILE *output_file;
    int i, j;  // for iterations
    double start_time, end_time;
    double result[MATRIX_SIZE];


    // seed value to my number
    srand(seed);

    // creating and allocating memory for matrix	
    matrix = (double **)malloc(MATRIX_SIZE * sizeof(double *));
    for(i = 0; i < MATRIX_SIZE; i++) {
	matrix[i] = (double *)malloc(MATRIX_SIZE * sizeof(double));
    }

	// filling matrix with random double values between [1.0 - 100.0]
    for(i = 0; i < MATRIX_SIZE; i++) {
	for(j = 0; j < MATRIX_SIZE; j++) {
		matrix[i][j] = (rand()) % 100 + 1.0; // taking random values between 1.0 and 100.0
	}
    }

    // creating a vector for multiplication
    vector = (double *)malloc(MATRIX_SIZE * sizeof(double *));
    for (i = 0; i < MATRIX_SIZE; i++) {
	vector[i] = (rand()) % 100 + 1.0;
    }
    

    // calculating number of rows each process will take
    int chunk_size = MATRIX_SIZE / size;
    int start_row = rank * chunk_size;
    int end_row = (rank + 1) * chunk_size;

    // allocating memory for result vector
    double local_result[MATRIX_SIZE];

    // performing matrix-vector multiplication
    for (int i = start_row; i < end_row; i++) {
        local_result[i] = 0;
        for (int j = 0; j < MATRIX_SIZE; j++) {
            local_result[i] += matrix[i][j] * vector[j];
        }
    }

    start_time = MPI_Wtime();

    MPI_Reduce(local_result, result, MATRIX_SIZE, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);


    output_file = fopen(filename, "w"); 
    
    for (int i = 0; i < MATRIX_SIZE; i++) {
        fprintf(output_file, "%.2f\n", result[i]);
    }

    end_time = MPI_Wtime();
    double elapsed_time = end_time - start_time;

    printf("\nElapsed time is %lf seconds for parallel mxv with %d processes\n", elapsed_time, size);

    
    MPI_Finalize();
    free(vector);
    free(matrix);
    fclose(output_file);

    return 0;
}

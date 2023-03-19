#include "hellomake.h"
#include <time.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {

 	//myFunc();

	if (argc != 4) {
		printf("You typed wrongly. Please give four arguments. Example form:\n");
         printf("%s row_number(int) col_number(int) output_filename(string)\n", argv[0]);
         return 1;
     }

	//printf("String: %s\n", argv[0]);
	//printf("String: %s\n", argv[1]);
	//printf("String: %s\n", argv[2]);
	//printf("String: %s\n", argv[3]);


	// taking given inputs and initializing them to variables
	int num1 = atoi(argv[1]); // I used atoi to convert string to integer
	int num2 = atoi(argv[2]);
	char *filename = argv[3];

	long int seed = 19050111005; // my number as seed value
	int i,j; // for iterations
	double **matrix;
	double *vector;


	// creating and allocating memory for matrix	
	matrix = (double **)malloc(num1 * sizeof(double *));

	for(i = 0; i < num1; i++) {
		matrix[i] = (double *)malloc(num2 * sizeof(double));
	}

	// seed value to my number
	srand(seed);

	// filling matrix with random double values between [1.0 - 100.0]
//	printf("\n*****Matrix*****\n");
	for(i = 0; i < num1; i++) {
		for(j = 0; j < num2; j++) {
			matrix[i][j] = (rand()) % 100 + 1.0; // taking random values between 1.0 and 100.0
//			printf("%.1f ", matrix[i][j]); 
		}
//		printf("\n");
	}

	printf("%dx%d matrix created and filled with random double numbers.\n", num1, num2);


	// creating a vector for multiplication
//	printf("\n*****Vector*****\n");
	vector = (double *)malloc(num2 * sizeof(double *));
	for (i = 0; i < num2; i++) {
		vector[i] = (rand()) % 100 + 1.0;
//		printf("%.1f ", vector[i]);
	}

	printf("Random vector is created for matrix X vector multiplication.\n");


	// creating an output file to write result
	FILE *out_file = fopen(filename, "w");

	if(out_file == NULL) {
		printf("%s cannot open!", filename);
	}

	// multiplication of matrix and vector and writing to output file
	double mult = 0;
	for(i = 0; i < num1; i++) {
                for(j = 0; j < num2; j++) {
                       mult += matrix[i][j] * vector[j];
                }
		fprintf(out_file, "%.1f\n", mult);
		mult = 0;
    }

	printf("\nSuccessfully multiplied and written to %s file.\n\n", filename);

	fclose(out_file);

	// freeing memory
	for (i = 0; i < num1; i++) {
         free(matrix[i]);
     }
	free(matrix);
	free(vector);

	

	return 0;
}

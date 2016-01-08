#include <stdio.h>
#include <stdlib.h>
#include "sys/alt_timestamp.h"

#define matrixSize 100

void exercise_two();
int** createSquareMatrix(int size);

void exercise_two() {
	printf("Running exercise two\n");

	int** a = createSquareMatrix(matrixSize);
	int** b = createSquareMatrix(matrixSize);
	int** c = createSquareMatrix(matrixSize);

	int sum;

	alt_timestamp_start();

	for (int i = 0; i < matrixSize; i++) {
		for (int j = 0; j < matrixSize; j++) {
			sum = 0;
			for (int k = 0; k < matrixSize; k++) {
				sum += a[i][k]*b[k][j];
			}
			c[i][j] = sum;
		}
	}

	int end = alt_timestamp();
	printf("time taken : %f seconds\n", (float)end / (float)alt_timestamp_freq());
	printf("clock ticks: %d seconds\n", end);
}

int** createSquareMatrix(int size){
	int a[size][size];
	for (int col = 0; col < size; col++){
		for (int row = 0; row < size; row++) {
			a[col][row] = rand() % 10; //arbitrary upper bound
		}
	}
	return a;
}

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>
#include <time.h>
#define bool int

// Function returns floor of square root of x
int floorSqrt(int x)
{
	// Base cases
	if (x == 0 || x == 1)
		return x;

	// Staring from 1, try all numbers until
	// i*i is greater than or equal to x.
	int i = 1, result = 1;
	while (result < x)
	{
		if (result == x)
			return result;
		i++;
		result = i * i;
	}
	return i - 1;
}

// checks if a number is power of two or not
bool isPowerOfTwo(int n)
{
	return (n && (!(n&(n - 1))));
}

// Function to verify matrix are same or not 
int compareMatrix(int **C, int **CS, int size) 
{
	int status = 0;
	for (int i = 0; i<size; i++) {
		for (int j = 0; j<size; j++) {
			if (C[i][j] == CS[i][j]) {
				status = 1;
			}
			else {
				status = 0;
			}
		}
	}

	// matrix same
	if (status == 1) {
		return 1;
	}
	// matrix not same
	else {
		return 0;
	}
}

// function to print matrix
void printMatrix(int **m, int size)
{
	for (int i = 0; i<size; i++) 
	{
		for (int j = 0; j<size; j++) 
		{
			printf("%d\t", m[i][j]);
		}
		printf("\n");
	}
}

void addMatrices(int **A, int **B, int **C, int size)
{
	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++) 
		{
			C[i][j] = A[i][j] + B[i][j];
		}
	}
}

void subtractMatrices(int **A, int **B, int **C, int size) 
{
	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++) 
		{
			C[i][j] = A[i][j] - B[i][j];
		}
	}
}

void standardMatrixMultiplication(int **A, int **B, int **C, int size)
{
	for (int i = 0; i<size; i++)
	{
		for (int j = 0; j<size; j++) 
		{
			C[i][j] = 0;
			for (int k = 0; k<size; k++) 
			{
				C[i][j] += (A[i][k] * B[k][j]);
			}
		}
	}
}

void strassenMatrixMultiplication(int **A, int **B, int **C, int size)
{

	if (size <= 2) {
		standardMatrixMultiplication(A, B, C, size);
	}
	else {

		int newSize = (size / 2);

		//Creating and then Initialization of sub-matrices of new size

		int **A11 = (int **)malloc(sizeof(int *)*newSize);
		int **A12 = (int **)malloc(sizeof(int *)*newSize);
		int **A21 = (int **)malloc(sizeof(int *)*newSize);
		int **A22 = (int **)malloc(sizeof(int *)*newSize);

		int **B11 = (int **)malloc(sizeof(int *)*newSize);
		int **B12 = (int **)malloc(sizeof(int *)*newSize);
		int **B21 = (int **)malloc(sizeof(int *)*newSize);
		int **B22 = (int **)malloc(sizeof(int *)*newSize);

		int **A_result = (int **)malloc(sizeof(int *)*newSize);
		int **B_result = (int **)malloc(sizeof(int *)*newSize);

		int **M1 = (int **)malloc(sizeof(int *)*newSize);
		int **M2 = (int **)malloc(sizeof(int *)*newSize);
		int **M3 = (int **)malloc(sizeof(int *)*newSize);
		int **M4 = (int **)malloc(sizeof(int *)*newSize);
		int **M5 = (int **)malloc(sizeof(int *)*newSize);
		int **M6 = (int **)malloc(sizeof(int *)*newSize);
		int **M7 = (int **)malloc(sizeof(int *)*newSize);

		int **C11 = (int **)malloc(sizeof(int *)*newSize);
		int **C12 = (int **)malloc(sizeof(int *)*newSize);
		int **C21 = (int **)malloc(sizeof(int *)*newSize);
		int **C22 = (int **)malloc(sizeof(int *)*newSize);



		for (int i = 0; i<newSize; i++)
		{
			A11[i] = (int *)malloc(sizeof(int)*newSize);
			A12[i] = (int *)malloc(sizeof(int)*newSize);
			A21[i] = (int *)malloc(sizeof(int)*newSize);
			A22[i] = (int *)malloc(sizeof(int)*newSize);

			B11[i] = (int *)malloc(sizeof(int)*newSize);
			B12[i] = (int *)malloc(sizeof(int)*newSize);
			B21[i] = (int *)malloc(sizeof(int)*newSize);
			B22[i] = (int *)malloc(sizeof(int)*newSize);

			A_result[i] = (int *)malloc(sizeof(int)*newSize);
			B_result[i] = (int *)malloc(sizeof(int)*newSize);

			M1[i] = (int *)malloc(sizeof(int)*newSize);
			M2[i] = (int *)malloc(sizeof(int)*newSize);
			M3[i] = (int *)malloc(sizeof(int)*newSize);
			M4[i] = (int *)malloc(sizeof(int)*newSize);
			M5[i] = (int *)malloc(sizeof(int)*newSize);
			M6[i] = (int *)malloc(sizeof(int)*newSize);
			M7[i] = (int *)malloc(sizeof(int)*newSize);

			C11[i] = (int *)malloc(sizeof(int)*newSize);
			C12[i] = (int *)malloc(sizeof(int)*newSize);
			C21[i] = (int *)malloc(sizeof(int)*newSize);
			C22[i] = (int *)malloc(sizeof(int)*newSize);

		}

		//Divide each matrix in 4 sub-matrices
		for (int i = 0; i < newSize; i++) {
			for (int j = 0; j < newSize; j++) {
				A11[i][j] = A[i][j]; // top left
				A12[i][j] = A[i][j + newSize]; // top right
				A21[i][j] = A[i + newSize][j]; // bottom left
				A22[i][j] = A[i + newSize][j + newSize]; // bottom right

				B11[i][j] = B[i][j]; // top left
				B12[i][j] = B[i][j + newSize]; // top right
				B21[i][j] = B[i + newSize][j]; // bottom left
				B22[i][j] = B[i + newSize][j + newSize]; // bottom right
			}
		}

		// inner multiplications:

		// calculating M1
		addMatrices(A11, A22, A_result, newSize);
		addMatrices(B11, B22, B_result, newSize);
		strassenMatrixMultiplication(A_result, B_result, M1, newSize);

		// calculating M2
		addMatrices(A21, A22, A_result, newSize);
		strassenMatrixMultiplication(A_result, B11, M2, newSize);

		// calculating M3
		subtractMatrices(B12, B22, B_result, newSize);
		strassenMatrixMultiplication(A11, B_result, M3, newSize);

		// calculating M4
		subtractMatrices(B21, B11, B_result, newSize);
		strassenMatrixMultiplication(A22, B_result, M4, newSize);

		// calculating M5
		addMatrices(A11, A12, A_result, newSize);
		strassenMatrixMultiplication(A_result, B22, M5, newSize);

		// calculating M6
		subtractMatrices(A21, A11, A_result, newSize);
		addMatrices(B11, B12, B_result, newSize);
		strassenMatrixMultiplication(A_result, B_result, M6, newSize);

		// calculating M7
		subtractMatrices(A12, A22, A_result, newSize);
		addMatrices(B21, B22, B_result, newSize);
		strassenMatrixMultiplication(A_result, B_result, M7, newSize);

		// calculating C12
		addMatrices(M3, M5, C12, newSize);

		// calculating C21
		addMatrices(M2, M4, C21, newSize);

		// calculating C11
		addMatrices(M1, M4, A_result, newSize);
		addMatrices(A_result, M7, B_result, newSize);
		subtractMatrices(B_result, M5, C11, newSize);

		// calculating C22
		addMatrices(M1, M3, A_result, newSize);
		addMatrices(A_result, M6, B_result, newSize);
		subtractMatrices(B_result, M2, C22, newSize);

		for (int i = 0; i<newSize; i++)
		{
			for (int j = 0; j<newSize; j++)
			{
				C[i][j] = C11[i][j];
				C[i][j + newSize] = C12[i][j];
				C[i + newSize][j] = C21[i][j];
				C[i + newSize][j + newSize] = C22[i][j];
			}
		}
	}
}

// main function
int main()
{
	int n = 0;
	printf("Enter Matrix size n (n must be power of 2):\n");
	scanf("%d", &n);

	int max_limit = floorSqrt(INT_MAX / n);
	int min_limit = 0;
	
	// validating n is power of two
	if (!isPowerOfTwo(n))
	{
		printf("Improper Input!\n");
		printf("n should be power of 2.\n");	
		return 0;
	}
	
	/*  matrix A and matrix B are input matrix, matrix C to store standard matrix multiplication result and
	matrix CS to store Strassen's matrix multiplication result
	*/

	// Allocate array of pointer of dimension n by n
	int **A = (int **)malloc(sizeof(int *)*n);
	int **B = (int **)malloc(sizeof(int *)*n);
	int **C = (int **)malloc(sizeof(int *)*n);
	int **CS = (int **)malloc(sizeof(int *)*n);

	for (int i = 0; i<n; i++) 
	{
		A[i] = (int *)malloc(sizeof(int)*n);
		B[i] = (int *)malloc(sizeof(int)*n);
		C[i] = (int *)malloc(sizeof(int)*n);
		CS[i] = (int *)malloc(sizeof(int)*n);
	}

	// intializing the matrices
	srand(time(0));
	for (int i = 0; i<n; i++) 
	{
		for (int j = 0; j<n; j++) 
		{
			A[i][j] = ((rand() + min_limit) % (max_limit + 1));
			B[i][j] = ((rand() + min_limit) % (max_limit + 1));
			C[i][j] = 0;
			CS[i][j] = 0;
		}
	}

	printf("\nMatrix A:\n");
	printMatrix(A, n);

	printf("\nMatrix B:\n");
	printMatrix(B, n);

	// Standard Matrix Multiplication with Time complexity:O(n^3)
	standardMatrixMultiplication(A, B, C, n);

	printf("\nResult Matrix using Standard Matrix Multiplication:\n");
	printMatrix(C, n);

	printf("\nResult Matrix using Strassen's Matrix Multiplication:\n");
	strassenMatrixMultiplication(A, B, CS, n);
	printMatrix(CS, n);

	// Code to check if matrices same or not
	if (compareMatrix(C, CS, n) == 1) 
	{
		printf("\nMatrix multiplication results by two methods are SAME!\n\n");
	}
	else 
	{
		printf("\nMatrix multiplication results by two methods are NOT SAME!\n\n");
	}
	return 0;
}

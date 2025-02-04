// Avinash Chouhan
// CISC 372 HW-1

#include <stdio.h>
#include <stdlib.h>

void matrixArrayOfArrays(int m, int n) {
    // set up row pointers
    float** matrix = (float**)malloc(m * sizeof(float*));
    // set up pointer arrays
    for (int x=0; x<m; x++) {
        matrix[x] = (float*)malloc(n * sizeof(float));  
    }
    // populate with incrementing numbers
    int x = 1;
    for (int row=0; row<m; row++) {
        for (int col=0; col<n; col++) {
            matrix[row][col] = x;
            x++;
        }
    }
    //print it out
    //printf("Matrix array of arrays (%dx%d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f\t", matrix[i][j]);
        }
        printf("\n");
    }

    //print it out transposed
    //printf("Matrix Transposed (%dx%d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%f\t", matrix[j][i]);
        }
        printf("\n");
    }
    for (int x=0; x<m; x++) {
        free(matrix[x]);
    }
    free(matrix);
}

void matrixOneBigArray(int m, int n) {
    // array of pointers
    float** matrix = (float**)malloc(m * sizeof(float*));
    // allocated large block
    float* block = (float*)malloc(m * n * sizeof(float));
    // point row to large block
    for (int i = 0; i < m; i++) {
        matrix[i] = block + (i * n);
    }
    // populate with nums
    for (int i = 0; i < m * n; i++) {
        block[i] = i + 1;
    }
    //print it out
    //printf("Matrix big array (%dx%d):\n", m, n);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            printf("%f\t", *(matrix[i] + j));
        }
        printf("\n");
    }
    //print it out transposed
    //printf("Matrix Transposed (%dx%d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%f\t", *(matrix[j] + i));
        }
        printf("\n");
    }
    free(block);
    free(matrix);
}

#define M 5
#define N 6

int main(int argc,char** argv){
    matrixArrayOfArrays(M,N);
    matrixOneBigArray(M,N);
    return 0;
}
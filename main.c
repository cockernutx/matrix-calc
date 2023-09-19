#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int** allocateMatrix(int rows, int cols) {
    int** matrix = (int**)malloc(rows * sizeof(int*));
    for (int i = 0; i < rows; i++) {
        matrix[i] = (int*)malloc(cols * sizeof(int));
    }
    return matrix;
}


void deallocateMatrix(int** matrix, int rows) {
    for (int i = 0; i < rows; i++) {
        free(matrix[i]);
    }
    free(matrix);
}


void fillMatrix(int** matrix, int rows, int cols) {
    srand(time(NULL));
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("Row %d, Col %d\t: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }
}


void printMatrix(int** matrix, int rows, int cols) {
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}


int** addMatrices(int** matrixA, int** matrixB, int rows, int cols) {
    int** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] + matrixB[i][j];
        }
    }
    return result;
}


int** subtractMatrices(int** matrixA, int** matrixB, int rows, int cols) {
    int** result = allocateMatrix(rows, cols);
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < cols; j++) {
            result[i][j] = matrixA[i][j] - matrixB[i][j];
        }
    }
    return result;
}


int** multiplyMatrices(int** matrixA, int** matrixB, int rowsA, int colsA, int colsB) {
    int** result = allocateMatrix(rowsA, colsB);
    for (int i = 0; i < rowsA; i++) {
        for (int j = 0; j < colsB; j++) {
            result[i][j] = 0;
            for (int k = 0; k < colsA; k++) {
                result[i][j] += matrixA[i][k] * matrixB[k][j];
            }
        }
    }
    return result;
}

int main() {
    int rowsA, colsA, rowsB, colsB;

    printf("Type the number of lines and columns of the 'A' matrix: ");
    scanf("%d %d", &rowsA, &colsA);

    printf("Type the number of lines and columns of the 'B' matrix: ");
    scanf("%d %d", &rowsB, &colsB);

    if (colsA != rowsB) {
        printf("Error: The number of columns of the 'A' matrix must be equal to the number of lines of the 'B' matrix\n");
        return 1;
    }

    int** matrixA = allocateMatrix(rowsA, colsA);
    int** matrixB = allocateMatrix(rowsB, colsB);

    printf("Fill the matrix A:\n");
    fillMatrix(matrixA, rowsA, colsA);
    printMatrix(matrixA, rowsA, colsA);

    printf("Fill the matrix B:\n");
    fillMatrix(matrixB, rowsB, colsB);
    printMatrix(matrixB, rowsB, colsB);

    int choice;
    printf("Select the operation:\n");
    printf("1. Sum\n");
    printf("2. Subtraction\n");
    printf("3. Multiplication\n");
    scanf("%d", &choice);

    int** resultMatrix = NULL;
    switch (choice) {
        case 1:
            resultMatrix = addMatrices(matrixA, matrixB, rowsA, colsA);
            break;
        case 2:
            resultMatrix = subtractMatrices(matrixA, matrixB, rowsA, colsA);
            break;
        case 3:
            resultMatrix = multiplyMatrices(matrixA, matrixB, rowsA, colsA, colsB);
            break;
        default:
            printf("Invalid choice.\n");
            break;
    }

    if (resultMatrix) {
        printf("Result:\n");
        printMatrix(resultMatrix, rowsA, colsB);
        deallocateMatrix(resultMatrix, rowsA);
    }

    deallocateMatrix(matrixA, rowsA);
    deallocateMatrix(matrixB, rowsB);

    return 0;
}

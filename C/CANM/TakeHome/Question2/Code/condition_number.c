#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void read_matrix(const char *filename, double **matrix, int n) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            fscanf(file, "%lf", &matrix[i][j]);
        }
    }

    fclose(file);
}

double calculate_norm(double **matrix, int n) {
    double norm = 0.0;
    for (int i = 0; i < n; i++) {
        double row_sum = 0.0;
        for (int j = 0; j < n; j++) {
            row_sum += fabs(matrix[i][j]);
        }
        if (row_sum > norm) {
            norm = row_sum;
        }
    }
    return norm;
}

void invert_matrix(double **matrix, double **inverse, int n) {
    // Initialize the inverse matrix as an identity matrix
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            inverse[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Perform Gaussian elimination
    for (int i = 0; i < n; i++) {
        double pivot = matrix[i][i];
        if (fabs(pivot) < 1e-9) {
            fprintf(stderr, "Matrix is singular or nearly singular.\n");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < n; j++) {
            matrix[i][j] /= pivot;
            inverse[i][j] /= pivot;
        }

        for (int k = 0; k < n; k++) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < n; j++) {
                    matrix[k][j] -= factor * matrix[i][j];
                    inverse[k][j] -= factor * inverse[i][j];
                }
            }
        }
    }
}

int main() {
    int n;
    printf("Enter the size of the matrix (n): ");
    scanf("%d", &n);

    // Dynamically allocate memory for the matrices
    double **matrix = (double **)malloc(n * sizeof(double *));
    double **inverse = (double **)malloc(n * sizeof(double *));

    for (size_t i = 0; i < n; i++)
    {
        matrix[i] = (double *)malloc(n * sizeof(double));
        inverse[i] = (double *)malloc(n * sizeof(double));
    }
    

    // Read the matrix from the file
    read_matrix("inputs.txt", matrix, n);

    // Calculate the norm of the matrix
    double norm = calculate_norm(matrix, n);

    // Calculate the inverse of the matrix
    invert_matrix(matrix, inverse, n);

    // Calculate the norm of the inverse matrix
    double inverse_norm = calculate_norm(inverse, n);

    // Calculate the condition number
    double condition_number = norm * inverse_norm;
    printf("Condition number of the matrix: %lf\n", condition_number);

    // Free allocated memory 
    for (int i = 0; i < n; i++) {
        free(matrix[i]);
        free(inverse[i]);
    }
    free(matrix);
    free(inverse);

    return 0;
}

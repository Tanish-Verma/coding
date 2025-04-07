#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

void readInputsFromFile(const char *filename, double **A, double *b, int n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(1);
    }

    // Read matrix A
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                fprintf(stderr, "Error: Invalid input format in file\n");
                fclose(file);
                exit(1);
            }
        }
    }

    // Read vector b
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf", &b[i]) != 1) {
            fprintf(stderr, "Error: Invalid input format in file\n");
            fclose(file);
            exit(1);
        }
    }

    fclose(file);
}

double* multiplyMatrixVector(double **A, double *b, int n) {
    double *result = (double *)malloc(n * sizeof(double));
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        result[i] = 0;
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * b[j];
        }
    }

    return result;
}

double* subtractVectors(double *vector1, double *vector2, int n) {
    double *result = (double *)malloc(n * sizeof(double));
    if (result == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        result[i] = vector1[i] - vector2[i];
    }

    return result;
}

double calculateNorm(double *vector, int n) {
    double norm = 0.0;
    for (int i = 0; i < n; i++) {
        norm += vector[i] * vector[i];
    }
    return norm;
}
double* Gauss_seidel(double ** A,double * b,int n,double weight,double epsilon){
    double * x= (double* )malloc(n*sizeof(double));
    if (x == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    double * xg= (double* )malloc(n*sizeof(double));
    if (xg == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        xg[i] = 1.0;  
    }
    
    for (int i = 0; i < n; i++) {
        x[i] = xg[i]; // Initialize x with xg values
    }

    double *residual = subtractVectors(b, multiplyMatrixVector(A, xg, n), n);
    if (residual == NULL) {
        fprintf(stderr, "Error: Memory allocation failed for residual\n");
        exit(1);
    }
    double tolerance = calculateNorm(residual, n);
    int iteration = 0;
    while (tolerance > epsilon) {
        for (int i = 0; i < n; i++) {
            double sigma = 0.0;
            for (int j = 0; j < n; j++) {
                if (j != i) {
                    sigma += A[i][j] * x[j];
                }
            }
            x[i] = (1 - weight) * xg[i] + weight * (b[i] - sigma) / A[i][i];
        }

        // Update xg with the new values of x
        for (int i = 0; i < n; i++) {
            xg[i] = x[i];
        }

        // Recalculate residual and tolerance
        free(residual);
        residual = subtractVectors(b, multiplyMatrixVector(A, xg, n), n);
        tolerance = calculateNorm(residual, n);

        iteration++;
    }

    printf("\n==============================\n");
    printf("Converged in %d iterations.\n", iteration);
    printf("==============================\n");

    free(residual);
    return x;
}

int main() {
    int n;
    printf("Enter the number of variables: ");
    scanf("%d", &n);

    double epsilon;
    printf("Enter the value of epsilon: ");
    scanf("%lf", &epsilon);

    double w;
    printf("Enter the value of weight w: ");
    scanf("%lf", &w);

    if (w <= 0 || w > 1) {
        fprintf(stderr, "Error: Weight w must be greater than 0 and less than or equal to 1.\n");
        return 1;
    }

    double **A = (double **)malloc(n * sizeof(double *));
    if (A == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }
    for (size_t i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        if (A[i] == NULL) {
            fprintf(stderr, "Error: Memory allocation failed\n");
            return 1;
        }
    }

    double *b = (double *)malloc(n * sizeof(double));
    if (b == NULL) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        return 1;
    }
    
    readInputsFromFile("inputs.txt", A, b, n);

    clock_t start, end;
    double cpu_time_used;

    start = clock();
    double *solution = Gauss_seidel(A, b, n, w, epsilon);
    end = clock();

    cpu_time_used = ((double)(end - start)) / CLOCKS_PER_SEC;

    printf("\n==============================\n");
    printf("Solution Vector:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.6lf\n", i, solution[i]);
    }
    printf("==============================\n");

    printf("\n==============================\n");
    printf("Time taken to solve: %.9f seconds\n", cpu_time_used);
    printf("==============================\n");

    // Free allocated memory
    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(solution);

    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void readInputsFromFile(const char *filename, double **A, double *b, int n) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        fprintf(stderr, "Error: Could not open file %s\n", filename);
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                fprintf(stderr, "Error: Invalid input format in file\n");
                fclose(file);
                exit(1);
            }
        }
    }

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

double* subtractVectors(double *v1, double *v2, int n) {
    double *result = (double *)malloc(n * sizeof(double));
    if (!result) {
        fprintf(stderr, "Error: Memory allocation failed\n");
        exit(1);
    }
    for (int i = 0; i < n; i++) {
        result[i] = v1[i] - v2[i];
    }
    return result;
}

double multiplyVectors(int n, double *v1, double *v2) {
    double result = 0.0;
    for (int i = 0; i < n; i++) {
        result += v1[i] * v2[i];
    }
    return result;
}

double* Conjugate_Gradient(double **A, double *b, int n, double epsilon, int *iterations) {
    *iterations = 0;

    double *x = (double *)malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) x[i] = 1.0;

    double *Ax = multiplyMatrixVector(A, x, n);
    double *r = subtractVectors(b, Ax, n);
    free(Ax);

    double *d = (double *)malloc(n * sizeof(double));
    double *r_new = (double *)malloc(n * sizeof(double));

    for (int i = 0; i < n; i++) d[i] = r[i];

    double tol = sqrt(multiplyVectors(n, r, r));

    while (tol > epsilon) {
        double *Ad = multiplyMatrixVector(A, d, n);
        double alpha = multiplyVectors(n, r, r) / multiplyVectors(n, d, Ad);

        for (int i = 0; i < n; i++) x[i] += alpha * d[i];
        for (int i = 0; i < n; i++) r_new[i] = r[i] - alpha * Ad[i];

        double beta = multiplyVectors(n, r_new, r_new) / multiplyVectors(n, r, r);

        for (int i = 0; i < n; i++) d[i] = r_new[i] + beta * d[i];

        for (int i = 0; i < n; i++) r[i] = r_new[i];
        tol = sqrt(multiplyVectors(n, r, r));

        free(Ad);
        (*iterations)++;
    }

    free(r);
    free(r_new);
    free(d);
    return x;
}

int main() {
    int n;
    printf("Enter the number of variables: ");
    scanf("%d", &n);

    double epsilon;
    printf("Enter the value of epsilon: ");
    scanf("%lf", &epsilon);

    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    double *b = (double *)malloc(n * sizeof(double));

    readInputsFromFile("inputs.txt", A, b, n);

    clock_t start = clock();
    int iterations;
    double *x = Conjugate_Gradient(A, b, n, epsilon, &iterations);
    clock_t end = clock();

    double time_ns = ((double)(end - start)) * 1e9 / CLOCKS_PER_SEC;

    printf("\n==============================\n");
    printf("Converged in %d iterations.\n", iterations);
    printf("Time taken to solve: %.0f ns\n", time_ns);
    printf("==============================\n");

    printf("\nSolution Vector:\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %.6lf\n", i+1, x[i]);
    }
    printf("==============================\n");

    for (int i = 0; i < n; i++) free(A[i]);
    free(A);
    free(b);
    free(x);

    return 0;
}
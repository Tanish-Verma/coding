#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void matrix_multiply_n1(int n, double **A, double *B, double *C) {
    for (int i = 0; i < n; i++) {
        C[i] = 0;
        for (int j = 0; j < n; j++) {
            C[i] += A[i][j] * B[j];
        }
    }
}

long double tolerance_calculator(int n, double **A, double *b, double *x) {
    double *residual = (double *)malloc(n * sizeof(double));
    matrix_multiply_n1(n, A, x, residual);
    for (size_t i = 0; i < n; i++) {
        residual[i] = b[i] - residual[i];
    }
    long double tolerance = 0;
    for (size_t i = 0; i < n; i++) {
        tolerance += residual[i] * residual[i];
    }
    free(residual);
    return sqrt(tolerance);
}

double *gauss_jacobi_seidel(int n, double **A, double *b, long double epsilon, int method, float weight) {
    double *xg = (double *)calloc(n, sizeof(double));
    double *x = (double *)calloc(n, sizeof(double));
    long count = 0;

    long double S = tolerance_calculator(n, A, b, xg);
    while (S > epsilon) {
        for (size_t i = 0; i < n; i++) {
            double sum = b[i];
            for (size_t j = 0; j < n; j++) {
                if (i != j) {
                    if (method == 0) {
                        // Seidel
                        sum -= A[i][j] * x[j];
                    } else {
                        // Jacobi
                        sum -= A[i][j] * xg[j];
                    }
                }
            }
            x[i] = (1 - weight) * xg[i] + weight * (sum / A[i][i]);
        }
        S = tolerance_calculator(n, A, b, x);
        for (size_t i = 0; i < n; i++) {
            xg[i] = x[i];
        }
        count++;
    }
    printf("Total number of iterations is %ld\n", count);
    free(xg);
    return x;
}

void read_file_input(int n, double **A, double *b) {
    FILE *file = fopen("input.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "File not found\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                fprintf(stderr, "Invalid input\n");
                exit(EXIT_FAILURE);
            }
        }
    }
    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf", &b[i]) != 1) {
            fprintf(stderr, "Invalid input\n");
            exit(EXIT_FAILURE);
        }
    }
    fclose(file);
}

void write_computed_values(int n, double *x_computed) {
    FILE *file = fopen("computed_values.txt", "w");
    if (file == NULL) {
        fprintf(stderr, "Could not open computed_values.txt for writing\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        fprintf(file, "%f\n", x_computed[i]);
    }
    fclose(file);
}

void run_python_script(int n) {
    char command[1024];
    snprintf(command, sizeof(command), "python3 compare_solutions.py %d", n);
    system(command);
}

int main() {
    int n, method;
    float weight;
    long double epsilon;
    char command[100];
    printf("Enter the number of variables: ");
    scanf("%d", &n);
    sprintf(command, "python3 Equations.py %d", n);
    system(command);
    printf("Enter the method for solving 0 for seidel and 1 for jacobi: ");
    scanf("%d", &method);
    printf("Enter the value of epsilon: ");
    scanf("%Lf", &epsilon);
    printf("Enter the weight for calculation. it should be less than 1: ");
    scanf("%f", &weight);

    double **A = (double **)malloc(n * sizeof(double *));
    if (A == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
        if (A[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    double *b = (double *)malloc(n * sizeof(double));
    if (b == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    read_file_input(n, A, b);
    double *x = gauss_jacobi_seidel(n, A, b, epsilon, method, weight);
    for (int i = 0; i < n; i++) {
        printf("The value of x[%d] is: %lf\n", i + 1, x[i]);
    }
    write_computed_values(n, x);

    run_python_script(n);

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(b);
    free(x);
    remove("solutions.txt");
    return 0;
}
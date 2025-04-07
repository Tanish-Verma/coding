#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

double norm(double* v, int len) {
    double sum = 0.0;
    for (int i = 0; i < len; ++i)
        sum += v[i] * v[i];
    return sqrt(sum);
}

void matmul(double** A, double** B, double** C, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j) {
            C[i][j] = 0.0;
            for (int k = 0; k < n; ++k)
                C[i][j] += A[i][k] * B[k][j];
        }
}

void transpose(double** src, double** dst, int n) {
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            dst[j][i] = src[i][j];
}

void qr_householder(double** A, double** Q, double** R, int n) {
    double** Qn = malloc(n * sizeof(double*));
    double** QnT = malloc(n * sizeof(double*));
    double** temp = malloc(n * sizeof(double*));
    for (int i = 0; i < n; ++i) {
        Qn[i] = calloc(n, sizeof(double));
        QnT[i] = calloc(n, sizeof(double));
        temp[i] = calloc(n, sizeof(double));
    }

    double* u = calloc(n, sizeof(double));
    double* v = calloc(n, sizeof(double));

    // Initialize Q as an identity matrix
    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            Q[i][j] = (i == j) ? 1.0 : 0.0;

    for (int i = 0; i < n; ++i)
        for (int j = 0; j < n; ++j)
            R[i][j] = A[i][j];

    for (int i = 0; i < n - 1; ++i) {
        double alpha = 0.0;
        for (int j = i; j < n; ++j)
            alpha += R[j][i] * R[j][i];
        alpha = sqrt(alpha);

        for (int j = 0; j < n; ++j)
            u[j] = (j < i) ? 0.0 : (j == i) ? R[j][i] - alpha : R[j][i];

        double u_norm = norm(u + i, n - i);
        for (int j = 0; j < n; ++j)
            v[j] = (j < i) ? 0.0 : u[j] / u_norm;

        // Initialize Qn as an identity matrix
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++)
                Qn[r][c] = (r == c) ? 1.0 : 0.0;

        for (int r = i; r < n; r++)
            for (int c = i; c < n; c++)
                Qn[r][c] -= 2 * v[r] * v[c];

        matmul(Qn, R, temp, n);
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++)
                R[r][c] = temp[r][c];

        transpose(Qn, QnT, n);
        matmul(Q, QnT, temp, n);
        for (int r = 0; r < n; r++)
            for (int c = 0; c < n; c++)
                Q[r][c] = temp[r][c];
    }

    for (int r = 0; r < n; ++r) {
        free(Qn[r]);
        free(QnT[r]);
        free(temp[r]);
    }
    free(Qn);
    free(QnT);
    free(temp);
    free(u);
    free(v);
}

void solve_using_qr(double** Q, double** R, double* b, double* x, int n) {
    double* Qtb = calloc(n, sizeof(double));

    // Compute Qt * b
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            Qtb[i] += Q[j][i] * b[j];
        }
    }

    // Back substitution to solve R * x = Qtb
    for (int i = n - 1; i >= 0; --i) {
        x[i] = Qtb[i];
        for (int j = i + 1; j < n; ++j) {
            x[i] -= R[i][j] * x[j];
        }
        x[i] /= R[i][i];
    }

    free(Qtb);
}

void read_file_input(int n, double **A, double *b) {
    FILE *file = fopen("inputs.txt", "r");
    if (file == NULL) {
        fprintf(stderr, "Failed to open input file\n");
        exit(1);
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (fscanf(file, "%lf", &A[i][j]) != 1) {
                fprintf(stderr, "Failed to read matrix A from file\n");
                exit(1);
            }
        }
    }

    for (int i = 0; i < n; i++) {
        if (fscanf(file, "%lf", &b[i]) != 1) {
            fprintf(stderr, "Failed to read vector b from file\n");
            exit(1);
        }
    }

    fclose(file);
}

int main() {
    int n;
    printf("Enter the number of variables: ");
    scanf("%d", &n);

    double **A = (double **)malloc(n * sizeof(double *));
    for (int i = 0; i < n; i++) {
        A[i] = (double *)malloc(n * sizeof(double));
    }

    double *b = (double *)malloc(n * sizeof(double));

    read_file_input(n, A, b);

    double** Q = malloc(n * sizeof(double*));
    double** R = malloc(n * sizeof(double*));
    for (int i = 0; i < n; ++i) {
        Q[i] = calloc(n, sizeof(double));
        R[i] = calloc(n, sizeof(double));
    }

    double* x = calloc(n, sizeof(double));

    clock_t start = clock();
    qr_householder(A, Q, R, n);
    clock_t end = clock();

    solve_using_qr(Q, R, b, x, n);

    printf("\n==============================\n");
    printf("Solution Vector (x):\n");
    for (int i = 0; i < n; i++) {
        printf("x[%d] = %10.6f\n", i + 1, x[i]);
    }
    printf("==============================\n");

    printf("\n==============================\n");
    printf("Runtime: %ld ns\n", (end - start) * 1000000000L / CLOCKS_PER_SEC);
    printf("==============================\n");

    printf("\n==============================\n");
    printf("Matrix Q (Orthogonal):\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%10.6f ", Q[i][j]);
        }
        printf("\n");
    }
    printf("==============================\n");

    printf("\n==============================\n");
    printf("Matrix R (Upper Triangular):\n");
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            printf("%10.6f ", R[i][j]);
        }
        printf("\n");
    }
    printf("==============================\n");

    free(x);
    for (int i = 0; i < n; ++i) {
        free(A[i]);
        free(Q[i]);
        free(R[i]);
    }
    free(A);
    free(Q);
    free(R);
    free(b);
    return 0;
}

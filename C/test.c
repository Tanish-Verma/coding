#include <stdio.h>
#include <stdlib.h>

void input_Aand_B(double **A, double *B, int n, double hot, double cold) {
    B[0] = hot;
    B[n - 1] = cold;
    for (int i = 0; i < n; i++) {
        A[i][i] = 2;
        if (i > 0) {
            A[i][i - 1] = -1;
        }
        if (i < n - 1) {
            A[i][i + 1] = -1;
        }
    }

    for (int i = 1; i < n - 1; i++) {
        B[i] = 0;
    }
}

void tri_diagonal(double **A, double *B, int n, double *x) {
    double *P = malloc((n - 1) * sizeof(double));
    double *Q = malloc(n * sizeof(double));

    if (P == NULL || Q == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    P[0] = A[0][1] / A[0][0];
    Q[0] = B[0] / A[0][0];

    for (int i = 1; i < n - 1; i++) {
        double d = A[i][i] - A[i][i - 1] * P[i - 1];
        P[i] = A[i][i + 1] / d;
        Q[i] = (B[i] - A[i][i - 1] * Q[i - 1]) / d;
    }

    Q[n - 1] = (B[n - 1] - A[n - 1][n - 2] * Q[n - 2]) / (A[n - 1][n - 1] - A[n - 1][n - 2] * P[n - 2]);
    x[n - 1] = Q[n - 1];

    for (int i = n - 2; i >= 0; i--) {
        x[i] = Q[i] - P[i] * x[i + 1];
    }

    free(P);
    free(Q);
}

int main() {
    int l;
    double dx, hot, cold;
    printf("Length of the rod:\n");
    scanf("%d", &l);
    printf("Length of one section:\n");
    scanf("%lf", &dx);
    printf("Hot end temperature:\n");
    scanf("%lf", &hot);
    printf("Cold end temperature:\n");
    scanf("%lf", &cold);

    int n = (l / dx) - 1;
    double **A = malloc(n * sizeof(double *));
    double *B = malloc(n * sizeof(double));
    double *x = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++) {
        A[i] = malloc(n * sizeof(double));
    }

    input_Aand_B(A, B, n, hot, cold);

    tri_diagonal(A, B, n, x);

    for (int i = 0; i < n; i++) {
        printf("Temperature[%d]=%lf\n", i, x[i]);
    }

    for (int i = 0; i < n; i++) {
        free(A[i]);
    }
    free(A);
    free(B);
    free(x);

    return 0;
}
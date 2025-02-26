#include <stdio.h>
#include <stdlib.h>

void LU_Decomposition(int n, double **A, double **L, double **U){
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            if(i<=j){
                U[i][j] = A[i][j];
                for(int k=0; k<i; k++){
                    U[i][j] -= L[i][k] * U[k][j];
                }
                if(i==j){
                    L[i][j] = 1;
                } else {
                    L[i][j] = 0;
                }
            } else {
                L[i][j] = A[i][j];
                for(int k=0; k<j; k++){
                    L[i][j] -= L[i][k] * U[k][j];
                }
                L[i][j] /= U[j][j];
                U[i][j] = 0;
            }
        }
    }
}

double* Forward_Substitution(int n, double **L, double *b){
    double *x = (double*)malloc(n * sizeof(double));
    for(int i=0; i<n; i++){
        x[i] = b[i];
        for(int j=0; j<i; j++){
            x[i] -= L[i][j] * x[j];
        }
    }
    return x;   
}

double* Backward_Substitution(int n, double **U, double *b){
    double *x = (double *)malloc(n * sizeof(double));
    for(int i=n-1; i>=0; i--){
        x[i] = b[i];
        for(int j=i+1; j<n; j++){
            x[i] -= U[i][j] * x[j];
        }
        x[i] /= U[i][i];
    }
    return x;
}

int main(){
    int n;

    printf("Enter the number of equations: ");
    scanf("%d", &n);

    double **A = (double **)malloc(n * sizeof(double *));
    double **L = (double **)malloc(n * sizeof(double *));
    double **U = (double **)malloc(n * sizeof(double *));
    for(int i=0; i<n; i++){
        A[i] = (double *)malloc(n * sizeof(double));
        L[i] = (double *)calloc(n, sizeof(double)); 
        U[i] = (double *)calloc(n, sizeof(double));
    }

    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("Enter the value of A[%d][%d]: ", i+1, j+1);
            scanf("%lf", &A[i][j]);
        }
    }

    double *b = (double *)malloc(n * sizeof(double));
    for(int i=0; i<n; i++){
        printf("Enter the value of b[%d]: ", i+1);
        scanf("%lf", &b[i]);
    }

    LU_Decomposition(n, A, L, U);

    printf("The Lower Triangular Matrix is: \n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%lf ", L[i][j]);
        }
        printf("\n");
    }

    printf("The Upper Triangular Matrix is: \n");
    for(int i=0; i<n; i++){
        for(int j=0; j<n; j++){
            printf("%lf ", U[i][j]);
        }
        printf("\n");
    }

    double *y = Forward_Substitution(n, L, b);
    double *x = Backward_Substitution(n, U, y);

    for(int i=0; i<n; i++){
        printf("The value of x[%d] is: %lf\n", i+1, x[i]);
    }

    // Free allocated memory
    for(int i=0; i<n; i++){
        free(A[i]);
        free(L[i]);
        free(U[i]);
    }
    free(A);
    free(L);
    free(U);
    free(b);
    free(y);
    free(x);

    return 0;
}
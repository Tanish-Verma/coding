// #include <iostream>
// #include <chrono>
// using namespace std;
// void LU_Decomposition(int n, double **A, double **L, double **U){
//     for(int j=0;j<n;j++){
//         for(int i=0;i<=j;i++){
//             L[i][j]=(double)(i==j)?1:0;
//             double sum = 0;
//             for(int k=0;k<i;k++)sum+=L[i][k]*U[k][j];
//             U[i][j] = A[i][j]-sum;
//         }
//         for(int i=j+1;i<n;i++){
//             U[i][j]=0;
//             double sum = 0;
//             for(int k=0;k<j;k++)sum+=L[i][k]*U[k][j];
//             L[i][j] = (A[i][j]-sum)/U[j][j];
//         }
//     }
// }
// double *Forward_Substitution(int n, double** L, double* b){
//     double* y = new double[n];
//     for(int i=0;i<n;i++){
//         double sum = 0;
//         for(int j=0;j<i;j++)sum+=L[i][j]*y[j];
//         y[i]=(b[i]-sum)/L[i][i];
//     }
//     return y;
// }
// double *Backward_Substitution(int n, double** U, double* y){
//     double* x = new double[n];
//     for(int i=n-1;i>=0;i--){
//         double sum = 0;
//         for(int j=i+1;j<n;j++)sum+=U[i][j]*x[j];
//         x[i]=(y[i]-sum)/U[i][i];
//     }
//     return x;
// }
// int main(){
//     int n;
//     cout << "Give value for size of matrix A and vector b: ";
//     cin >> n;
//     double **A = new double*[n];
//     for(int i=0;i<n;i++){
//         A[i] = new double[n];
//         for(int j=0;j<n;j++){
//             cout << "Input the value in row " << i+1 << " and column " << j+1 << " of matrix A: ";
//             cin >> A[i][j];
//         }
//     }
//     cout << "Matrix A is:" << endl;
//     for(int i=0;i<n;i++){
//         cout << "[ ";
//         for(int j=0;j<n;j++)cout << A[i][j] << " ";
//         cout << "]" << endl;
//     }
//     double *b = new double[n];
//     for(int i=0;i<n;i++){
//         cout << "Input the value of element " << i+1 << " of vector b: ";
//         cin >> b[i];
//     }
//     cout << "Vector b is:" << endl;
//     cout << "[ ";
//     for(int i=0;i<n;i++){
//         cout << b[i] << " ";
//     }
//     cout << "]" << endl;
//     double ** L = new double*[n];
//     double ** U = new double*[n];
//     for(int i=0;i<n;i++){
//         L[i] = new double[n];
//         U[i] = new double[n];
//     }
//     auto start = chrono::high_resolution_clock::now();
//     LU_Decomposition(n, A, L, U);
//     double* y = Forward_Substitution(n, L, b);
//     double* v = Backward_Substitution(n, U, y);
//     auto end = chrono::high_resolution_clock::now();
//     auto timeTaken = chrono::duration_cast<chrono::microseconds>(end - start).count();
//     cout << "Lower Triangular Matrix L:" << endl;
//     for(int i=0;i<n;i++){
//         cout << "[ ";
//         for(int j=0;j<n;j++)cout << L[i][j] << " ";
//         cout << "]" << endl;
//     }
//     cout << "Upper Triangular Matrix U:" << endl;
//     for(int i=0;i<n;i++){
//         cout << "[ ";
//         for(int j=0;j<n;j++)cout << U[i][j] << " ";
//         cout << "]" << endl;
//     }
//     cout << "Voltages at each of the junctions are:" << endl;
//     for(int i=0;i<n;i++)cout << "V" << i+1 << " = " << v[i] << endl;
    
//     cout << "Time taken to find voltages using LU Decomposition: " << timeTaken << " microseconds" << endl;
// }







#include <iostream>
#include <chrono>
using namespace std;
double mod2(int n, double* x){
    double modu = 0;
    for(int i=0;i<n;i++){
        modu += x[i]*x[i];
    }
    return modu;
}
double* Residual(int n, double* b, double** A, double* x){
    double* Ax = new double[n]();
    for(int i=0; i<n;i++){
        for(int j=0;j<n;j++) Ax[i] += A[i][j]*x[j];
    }
    double *r = new double[n];
    for(int i=0; i<n;i++) r[i] = b[i]-Ax[i];
    delete[] Ax;
    return r;
}
int iterationCount =0;
double *Gauss_Siedel(int n, double w, double* b, double** A, double* xg, double z){
    double* x = new double[n];
    for(int i=0;i<n;i++) x[i] = xg[i];
    double *r = Residual(n, b, A, x);
    double s = mod2(n, r);
    while(s>z){
        for(int i=0;i<n;i++){
            double sum = b[i];
            for(int j=0;j<i;j++) sum -= A[i][j]*x[j];
            for(int j=i+1;j<n;j++) sum -= A[i][j]*xg[j];
            x[i] = (1-w)*xg[i] + (w/A[i][i])*sum;
        }
        r = Residual(n, b, A, x);
        s = mod2(n, r);
        for(int i=0;i<n;i++) xg[i] = x[i];
        iterationCount++;
    }
    delete[] r;
    return x;
}
int main(){
    double w, z;
    cout << "Enter the value of weight, w used for SOR method (Set w=1 for Gauss-Siedel): ";
    cin >> w;
    cout << "Enter the value of tolerance, z: ";
    cin >> z;
    int n;
    cout << "Give value for size of matrix A and vector b: ";
    cin >> n;
    double **A = new double*[n];
    double *b = new double[n];
    double *vg = new double[n];
    for(int i=0;i<n;i++){
        A[i] = new double[n];
        for(int j=0;j<n;j++){
            cout << "Input the value in row " << i+1 << " and column " << j+1 << " of matrix A: ";
            cin >> A[i][j];
        }
    }
    cout << "Matrix A is:" << endl;
    for(int i=0;i<n;i++){
        cout << "[ ";
        for(int j=0;j<n;j++) cout << A[i][j] << " ";
        cout << "]" << endl;
    }
    for(int i=0;i<n;i++){
        cout << "Input the value of element " << i+1 << " of vector b: ";
        cin >> b[i];
    }
    cout << "Vector b is:" << endl << "[ ";
    for(int i=0;i<n;i++) cout << b[i] << " ";
    cout << "]" << endl;
    for(int i=0;i<n;i++){
        cout << "Input the initial guess for voltage value at node " << i+1 << ": ";
        cin >> vg[i];
    }
    cout << "The vector consisting of initial guess voltages, vg is:" << endl << "[ ";
    for(int i=0;i<n;i++) cout << vg[i] << " ";
    cout << "]" << endl;
    auto start = chrono::high_resolution_clock::now();
    double *v = Gauss_Siedel(n,w,b,A,vg,z);
    auto end = chrono::high_resolution_clock::now();
    auto timeTaken = chrono::duration_cast<chrono::microseconds>(end - start).count();
    cout << "Voltages at each of the junctions are:" << endl;
    for(int i=0;i<n;i++)cout << "V" << i+1 << " = " << v[i] << endl;
    cout << "Number of iterations required to find voltages: "<< iterationCount << endl;
    cout << "Time taken to find voltages using Gauss-Siedel/SOR: " << timeTaken << " microseconds" << endl;
    delete[] b;
    delete[] vg;
    delete[] v;
    for(int i=0;i<n;i++){
        delete[] A[i];
    }
    delete[] A;
}



// #include <iostream>
// #include <chrono>
// using namespace std;
// double* axpy(int n, double a, double* x, double* y){
//     double* axy = new double[n];
//     for(int i=0;i<n;i++) axy[i] = a*x[i]+y[i];
//     return axy;
// }
// double* matvec(int n, double** A, double* y){
//     double* Ay = new double[n]();
//     for(int i=0;i<n;i++){
//         for(int j=0;j<n;j++) Ay[i] += A[i][j]*y[j];
//     }
//     return Ay;
// }
// double dot(int n, double* x, double* y){
//     double result = 0;
//     for(int i=0;i<n;i++) result += x[i]*y[i];
//     return result;
// }
// double* Residual(int n, double* b, double** A, double* x){
//     double* Ax = matvec(n, A, x);
//     double* r = axpy(n, -1, Ax, b);
//     delete[] Ax;
//     return r;
// }
// int iterationCount = 0;
// double* Conjugate_Gradient(int n, double z, double** A, double* b, double* xg){
//     double* x = new double[n];
//     for(int i=0;i<n;i++) x[i] = xg[i];
//     double* r = Residual(n, b, A, x);
//     double* d = new double[n];
//     for(int i=0;i<n;i++) d[i] = r[i];
//     double s = dot(n, r, r);
//     while(s>z){
//         double* Ad = matvec(n, A, d);
//         double alpha = dot(n, r, d)/dot(n, d, Ad);
//         double* new_x = axpy(n, alpha, d, x);
//         delete[] x;
//         x = new_x;
//         double* new_r = axpy(n, -alpha, Ad, r);
//         delete[] r;
//         r = new_r;
//         double beta = -dot(n, new_r, Ad)/dot(n, d, Ad);
//         delete[] Ad;
//         double* new_d = axpy(n, beta, d, r);
//         delete[] d;
//         d = new_d;
//         s = dot(n, r, r);
//         iterationCount++;
//     }
//     delete[] r;
//     delete[] d;
//     return x;
// }
// int main(){
//     double z;
//     cout << "Enter the value of tolerance, z: ";
//     cin >> z;
//     int n;
//     cout << "Enter the size of matrix A and vector b: ";
//     cin >> n;
//     double** A = new double*[n];
//     for(int i=0;i<n;i++){
//         A[i] = new double[n];
//         for(int j=0;j<n;j++){
//             cout << "Input the value in row " << i+1 << " and column " << j+1 << " of matrix A: ";
//             cin >> A[i][j];
//         }
//     }
//     cout << "Matrix A is:" << endl;
//     for(int i=0;i<n;i++){
//         cout << "[ ";
//         for(int j=0;j<n;j++)cout << A[i][j] << " ";
//         cout << "]" << endl;
//     }
//     double* b = new double[n];
//     for(int i=0;i<n;i++) {
//         cout << "Input the value of element " << i+1 << " of vector b: ";
//         cin >> b[i];
//     }
//     cout << "Vector b is:" << endl;
//     cout << "[ ";
//     for(int i=0;i<n;i++){
//         cout << b[i] << " ";
//     }
//     cout << "]" << endl;
//     double* vg = new double[n];
//     for(int i=0;i<n;i++){
//         cout << "Input the value of element " << i+1 << " of vector xg: ";
//         cin >> vg[i];
//     }
//     auto start = chrono::high_resolution_clock::now();
//     double* v = Conjugate_Gradient(n,z,A,b,vg);
//     auto end = chrono::high_resolution_clock::now();
//     auto timeTaken = chrono::duration_cast<chrono::microseconds>(end - start).count();
//     cout << "Voltages at each of the junctions are:" << endl << "[ ";
//     for(int i=0;i<n;i++) cout << "V" << i+1 << " = " << v[i] << endl;
//     cout << "Number of iterations: " << iterationCount << endl;
//     cout << "Time taken to find voltages using Conjugate Gradient: " << timeTaken << " ms" << endl;
//     delete[] b;
//     delete[] vg;
//     delete[] v;
//     for(int i=0;i<n;i++) delete[] A[i];
//     delete[] A;
// }
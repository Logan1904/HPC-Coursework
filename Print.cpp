#include <iostream>
using namespace std;

// Function to print a vector 'a' of size 'N'
void PrintVector(double* a, int N) {
    for (int i = 0; i < N; ++i) {
        cout << a[i] << " ";
    }
    cout << endl;
}

// Function to print matrix 'a' of size 'Nx' x 'Ny'
void PrintMatrix(double* a, int Nx, int Ny) {
    for (int i = Ny-1; i > -1; --i) {
        for (int j = 0; j < Nx; ++j) {
            cout << a[Nx*i + j] << " ";
        }
        cout << endl;
    }
}
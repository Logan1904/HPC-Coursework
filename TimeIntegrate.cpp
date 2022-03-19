#include "ReactionDiffusion.h"

#include <iostream>
#include <cblas.h>

// Method to initialise A and B matrix
void ReactionDiffusion::TimeIntegrate(int np) {

    int length = Nx*Ny;
    int t = 0;
    while (t<Nt) {
        double* utmp = new double[Nx*Ny]();
        double* vtmp = new double[Nx*Ny]();

        #pragma omp parallel for num_threads(np)
        
            for (int row = 0; row < length; ++row) {
                utmp[row] += dt*(eps*u[row]*(1.0-u[row])*(u[row] - (1/a)*(v[row]+b)));
                vtmp[row] += dt*(u[row]*u[row]*u[row] - v[row]);
            }
        
        
        #pragma omp parallel for num_threads(np) collapse(2) 
        
            for (int row = 0; row < length; ++row) {
                for (int col = 0; col < length; ++col) {
                    utmp[row] += A[row*length + col] * u[col];
                    vtmp[row] += B[row*length + col] * v[col];
                }
            }
        

        cblas_dcopy(length, utmp, 1, u, 1);
        cblas_dcopy(length, vtmp, 1, v, 1);

        ++t;

        std::cout << t << std::endl;

        delete[] utmp;
        delete[] vtmp;
    }

}

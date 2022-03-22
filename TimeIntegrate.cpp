#include "ReactionDiffusion.h"

#include <cblas.h>

/**
 * @brief Method to integrate our Reaction-Diffusion PDE
 */

// Method to initialise A and B matrix
void ReactionDiffusion::TimeIntegrate() {
    for (int t = 0; t < Nt; ++t) {
        double* utmp = new double[Nx*Ny];
        double* vtmp = new double[Nx*Ny];
        double* utmp2 = new double[Nx*Ny];
        double* vtmp2 = new double[Nx*Ny];
        
        #pragma omp parallel
        {
            #pragma omp sections nowait
            {   
                #pragma omp section
                cblas_dsbmv(CblasColMajor, CblasUpper, Nx*Ny, Nx, 1.0, A, Nx+1, u, 1, 0.0, utmp, 1); // Compute A*u[n]

                #pragma omp section
                cblas_dsbmv(CblasColMajor, CblasUpper, Nx*Ny, Nx, 1.0, B, Nx+1, v, 1, 0.0, vtmp, 1); // Compute B*v[n]
            }

            // Compute f1(u[n],v[n]) and f2(u[n],v[n])
            #pragma omp for schedule(static)
                for (int i = 0; i < Nx*Ny; ++i) {
                    utmp2[i] = dt*(eps*u[i]*(1-u[i])*(u[i] - (1/a)*(v[i]+b)));
                    vtmp2[i] = dt*(u[i]*u[i]*u[i] - v[i]);
                }

            #pragma omp for nowait schedule(static)
                for (int i = 0; i < Nx*Ny; ++i) {
                    u[i] = utmp[i] + utmp2[i];
                    v[i] = vtmp[i] + vtmp2[i];
                }
        }

        delete[] utmp;
        delete[] vtmp;
        delete[] utmp2;
        delete[] vtmp2;
    }
}

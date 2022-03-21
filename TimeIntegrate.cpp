#include "ReactionDiffusion.h"

#include <cblas.h>

/**
 * @brief Method to integrate our Reaction-Diffusion PDE
 */

// Method to initialise A and B matrix
void ReactionDiffusion::TimeIntegrate() {
    int t = 0;
    while (t < Nt) {
        double* utmp = new double[Nx*Ny];
        double* vtmp = new double[Nx*Ny];
        
        #pragma omp parallel
        {
            #pragma omp single
            {   
                #pragma omp task
                cblas_dsbmv(CblasColMajor, CblasUpper, Nx*Ny, Nx, 1.0, A, Nx+1, u, 1, 0.0, utmp, 1); // Compute A*u{n}

                #pragma omp task
                cblas_dsbmv(CblasColMajor, CblasUpper, Nx*Ny, Nx, 1.0, B, Nx+1, v, 1, 0.0, vtmp, 1); // Compute B*v{n}
            }

            // Compute f1(u{n},v{n}) and f2(u{n},v{n})
            #pragma omp for
                for (int i = 0; i < Nx*Ny; ++i) {
                    utmp[i] += dt*(eps*u[i]*(1-u[i])*(u[i] - (1/a)*(v[i]+b)));
                    vtmp[i] += dt*(u[i]*u[i]*u[i] - v[i]);
                }
        
            // Update u and v
            #pragma omp single
            {   
                #pragma omp task
                cblas_dcopy(Nx*Ny, utmp, 1, u, 1);

                #pragma omp task
                cblas_dcopy(Nx*Ny, vtmp, 1, v, 1);

                #pragma omp task
                ++t;
            }
        }

        delete[] utmp;
        delete[] vtmp;
    }
}

#include "ReactionDiffusion.h"

#include <cblas.h>

/**
 * @brief Method to integrate our Reaction-Diffusion PDE
 */

// Method to initialise A and B matrix
void ReactionDiffusion::TimeIntegrate() {
    for (int t = 0; t < Nt; ++t) {
        double* utmp = new double[Nx*Ny]();
        double* vtmp = new double[Nx*Ny]();
        double* utmp2 = new double[Nx*Ny]();
        double* vtmp2 = new double[Nx*Ny]();
        
        #pragma omp parallel
        {
            #pragma omp for schedule(static)
                for (int i = 0; i < Nx*Ny; ++i) {
                    utmp[i] += u[i]*A[(Nx*Ny)*0 + i];
                    vtmp[i] += v[i]*B[(Nx*Ny)*0 + i];
                }
            
            #pragma omp for schedule(static)
                for (int i = 0; i < Nx*Ny-1; ++i) {
                    utmp[i] += u[i+1]*A[(Nx*Ny)*1 + i];
                    vtmp[i] += v[i+1]*B[(Nx*Ny)*1 + i];
                }

            #pragma omp for schedule(static)
                for (int i = 0; i < Nx*Ny-Nx; ++i) {
                    utmp[i] += u[i+Nx]*A[(Nx*Ny)*2 + i];
                    vtmp[i] += v[i+Nx]*B[(Nx*Ny)*2 + i];
                }
            
            #pragma omp for schedule(static)
                for (int i = Nx*Ny-1; i>=1; --i) {
                    utmp[i] += u[i-1]*A[(Nx*Ny)*1 + i-1];
                    vtmp[i] += v[i-1]*B[(Nx*Ny)*1 + i-1];
                }

            #pragma omp for schedule(static)
                for (int i = Nx*Ny-Nx; i>=Nx; --i) {
                    utmp[i] += u[i-Nx]*A[(Nx*Ny)*2 + i-Nx];
                    vtmp[i] += v[i-Nx]*B[(Nx*Ny)*2 + i-Nx];
                }

            // Compute f1(u[n],v[n]) and f2(u[n],v[n])
            #pragma omp for schedule(static)
                for (int i = 0; i < Nx*Ny; ++i) {
                    utmp2[i] = dt*(eps*u[i]*(1-u[i])*(u[i] - (1/a)*(v[i]+b)));
                    vtmp2[i] = dt*(u[i]*u[i]*u[i] - v[i]);
                }

            #pragma omp for schedule(static)
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

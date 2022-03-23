#include "ReactionDiffusion.h"

#include <cblas.h>

/**
 * @brief Method to integrate our Reaction-Diffusion PDE
 */

// Method to initialise A and B matrix
void ReactionDiffusion::TimeIntegrate() {
    int length = Nx*Ny;
    for (int t = 0; t < Nt; ++t) {
        double* utmp = new double[length]();
        double* vtmp = new double[length]();
        double* utmp2 = new double[length]();
        double* vtmp2 = new double[length]();
        
        #pragma omp parallel
        {
            #pragma omp for
                for (int i = 0; i < length; ++i) {
                    utmp[i] += u[i]*A[(length)*0 + i];
                    vtmp[i] += v[i]*B[(length)*0 + i];

                    if (i < length-1) {
                        utmp[i] += u[i+1]*A[(length)*1 + i];
                        vtmp[i] += v[i+1]*B[(length)*1 + i];
                    }

                    if (i < length-Nx) {
                        utmp[i] += u[i+Nx]*A[(length)*2 + i];
                        vtmp[i] += v[i+Nx]*B[(length)*2 + i];
                    }
                }
            
            #pragma omp for
                for (int j = length-1; j>=1; --j) {
                    utmp[j] += u[j-1]*A[(length)*1 + j-1];
                    vtmp[j] += v[j-1]*B[(length)*1 + j-1];

                    if (j >= Nx) {
                        utmp[j] += u[j-Nx]*A[(length)*2 + j-Nx];
                        vtmp[j] += v[j-Nx]*B[(length)*2 + j-Nx];
                    }
                }

            // Compute f1(u[n],v[n]) and f2(u[n],v[n])
            #pragma omp for
                for (int k = 0; k < length; ++k) {
                    double uval = u[k];
                    double vval = v[k];

                    utmp2[k] = dt*(eps*uval*(1-uval)*(uval - (1/a)*(vval+b)));
                    vtmp2[k] = dt*(uval*uval*uval - vval);
                }

            #pragma omp for
                for (int i = 0; i < length; ++i) {
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

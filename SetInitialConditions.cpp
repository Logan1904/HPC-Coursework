#include "ReactionDiffusion.h"

/**
 * @brief Method to set the initial conditions for our 'u' and 'v' vectors
 *        Initial conditions defined as: u(x,y) = {1.0, if y>Ly/2}, {0.0, otherwise}
 *                                       v(x,y) = {a/2, if x<Lx/2}, {0.0, otherwise}
 */

void ReactionDiffusion::SetInitialConditions() {
    #pragma omp parallel
    {
        #pragma omp for collapse(2)

            for (int j = 0; j < Ny; ++j) {
                for (int i = 0; i < Nx; ++i) {

                    if (j > double(Ny-1)/2) {
                        if (i < double(Nx-1)/2) {
                            u[Nx*j + i] = 1.0;
                            v[Nx*j + i] = a/2;
                        } else {
                            u[Nx*j + i] = 1.0;
                            v[Nx*j + i] = 0.0;
                        }
                    } else if (i < double(Nx-1)/2){
                        u[Nx*j + i] = 0.0;
                        v[Nx*j + i] = a/2;
                    } else {
                        u[Nx*j + i] = 0.0;
                        v[Nx*j + i] = 0.0;
                    }
                }
            }
    }

    Initialise();
}
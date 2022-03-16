#include "ReactionDiffusion.h";

// Method to set initial conditions
void ReactionDiffusion::SetInitialConditions() {
    u = new double[Nx*Ny];
    v = new double[Nx*Ny];

    // Initial conditions for u
    for (int j = 0; j < Ny; ++j) {
        for (int i = 0; i < Nx; ++i) {
            if (j > double(Ny-1)/2) {
                u[Nx*j + i] = 1.0;
            } else {
                u[Nx*j + i] = 0.0;
            }
        }
    }

    // Initial conditions for v
    for (int j = 0; j < Ny; ++j) {
        for (int i = 0; i < Nx; ++i) {
            if (i < double(Nx-1)/2) {
                u[Nx*j + i] = a/2;
            } else {
                u[Nx*j + i] = 0.0;
            }
        }
    }
}
#include "ReactionDiffusion.h"

// Method to initialise A and B matrix
void ReactionDiffusion::TimeIntegrate() {
    double* utmp = new double[Nx*Ny]();
    int length = Nx*Ny;
    for (int row = 0; row < length; ++row) {
        utmp[row] += dt*()
        for (int col = 0; col < length; ++col) {
            utmp[row] += A[row*length + col] * u[row];
        }
    }

}
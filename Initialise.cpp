#include "ReactionDiffusion.h"

#include <iostream>
#include <iomanip>

// Method to initialise A and B matrix
void ReactionDiffusion::Initialise() {
    A = new double[Nx*Ny*Nx*Ny]();
    B = new double[Nx*Ny*Nx*Ny]();

    int length = Nx*Ny;

    for (int block = 0; block < Ny; ++block) {
        for (int row = 0; row < Nx; ++row) {

            int global_row = block*Nx + row;

            if (block == 0) {
                if (row == 0) {
                    A[global_row*length + global_row] = 1-2*lambda1;
                    A[global_row*length + global_row + 1] = lambda1;
                    A[global_row*length + global_row + Nx] = lambda1;

                    B[global_row*length + global_row] = 1-2*lambda2;
                    B[global_row*length + global_row + 1] = lambda2;
                    B[global_row*length + global_row + Nx] = lambda2;
                } else if (row == Nx-1) {
                    A[global_row*length + global_row] = 1-2*lambda1;
                    A[global_row*length + global_row - 1] = lambda1;
                    A[global_row*length + global_row + Nx] = lambda1;

                    B[global_row*length + global_row] = 1-2*lambda2;
                    B[global_row*length + global_row - 1] = lambda2;
                    B[global_row*length + global_row + Nx] = lambda2;
                } else {
                    A[global_row*length + global_row] = 1-3*lambda1;
                    A[global_row*length + global_row + 1] = lambda1;
                    A[global_row*length + global_row - 1] = lambda1;
                    A[global_row*length + global_row + Nx] = lambda1;

                    B[global_row*length + global_row] = 1-3*lambda2;
                    B[global_row*length + global_row + 1] = lambda2;
                    B[global_row*length + global_row - 1] = lambda2;
                    B[global_row*length + global_row + Nx] = lambda2;
                }
            } else if (block == Ny-1) {
                if (row == 0) {
                    A[global_row*length + global_row] = 1-2*lambda1;
                    A[global_row*length + global_row + 1] = lambda1;
                    A[global_row*length + global_row - Nx] = lambda1;
                    
                    B[global_row*length + global_row] = 1-2*lambda2;
                    B[global_row*length + global_row + 1] = lambda2;
                    B[global_row*length + global_row - Nx] = lambda2;
                } else if (row == Nx-1) {
                    A[global_row*length + global_row] = 1-2*lambda1;
                    A[global_row*length + global_row - 1] = lambda1;
                    A[global_row*length + global_row - Nx] = lambda1;

                    B[global_row*length + global_row] = 1-2*lambda2;
                    B[global_row*length + global_row - 1] = lambda2;
                    B[global_row*length + global_row - Nx] = lambda2;
                } else {
                    A[global_row*length + global_row] = 1-3*lambda1;
                    A[global_row*length + global_row + 1] = lambda1;
                    A[global_row*length + global_row - 1] = lambda1;
                    A[global_row*length + global_row - Nx] = lambda1;

                    B[global_row*length + global_row] = 1-3*lambda2;
                    B[global_row*length + global_row + 1] = lambda2;
                    B[global_row*length + global_row - 1] = lambda2;
                    B[global_row*length + global_row - Nx] = lambda2;
                }
            } else {
                if (row == 0) {
                    A[global_row*length + global_row] = 1-3*lambda1;
                    A[global_row*length + global_row + 1] = lambda1;
                    A[global_row*length + global_row + Nx] = lambda1;
                    A[global_row*length + global_row - Nx] = lambda1;

                    B[global_row*length + global_row] = 1-3*lambda2;
                    B[global_row*length + global_row + 1] = lambda2;
                    B[global_row*length + global_row + Nx] = lambda2;
                    B[global_row*length + global_row - Nx] = lambda2;
                } else if (row == Nx-1) {
                    A[global_row*length + global_row] = 1-3*lambda1;
                    A[global_row*length + global_row - 1] = lambda1;
                    A[global_row*length + global_row + Nx] = lambda1;
                    A[global_row*length + global_row - Nx] = lambda1;

                    B[global_row*length + global_row] = 1-3*lambda2;
                    B[global_row*length + global_row - 1] = lambda2;
                    B[global_row*length + global_row + Nx] = lambda2;
                    B[global_row*length + global_row - Nx] = lambda2;
                } else {
                    A[global_row*length + global_row] = 1-4*lambda1;
                    A[global_row*length + global_row + 1] = lambda1;
                    A[global_row*length + global_row - 1] = lambda1;
                    A[global_row*length + global_row + Nx] = lambda1;
                    A[global_row*length + global_row - Nx] = lambda1;

                    B[global_row*length + global_row] = 1-4*lambda2;
                    B[global_row*length + global_row + 1] = lambda2;
                    B[global_row*length + global_row - 1] = lambda2;
                    B[global_row*length + global_row + Nx] = lambda2;
                    B[global_row*length + global_row - Nx] = lambda2;
                }
            }
        }
    }
}
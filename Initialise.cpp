#include "ReactionDiffusion.h"
#include <iostream>

/**
 * @brief Method to initialise our A and B matrices
 *        A matrix defined as: u[n+1] = A*u[n] + f1(u[n],v[n])
 *        B matrix defined as: v[n+1] = B*v[n] + f2(u[n],v[n])
 *        A and B matrices are symmetric, and hence created in the Column-Major, Upper Band, Packed storage form
 */

void ReactionDiffusion::Initialise() {

    for (int block = 0; block < Ny; ++block) {
        for (int i = 0; i < Nx; ++i) {
            
            if (i == Nx-1) {
                A[(Nx*Ny)*1 + block*Nx + i] = 0.0;
                B[(Nx*Ny)*1 + block*Nx + i] = 0.0;
            } else {
                A[(Nx*Ny)*1 + block*Nx + i] = lambda1;
                B[(Nx*Ny)*1 + block*Nx + i] = lambda2;
            }

            if (block == 0 || block == Ny-1) {

                if (block == Ny-1) {
                    A[(Nx*Ny)*2 + block*Nx + i] = 0.0;
                    B[(Nx*Ny)*2 + block*Nx + i] = 0.0;
                } else {
                    A[(Nx*Ny)*2 + block*Nx + i] = lambda1;
                    B[(Nx*Ny)*2 + block*Nx + i] = lambda2;
                }
            
                if (i == 0 || i == Nx-1) {
                    A[(Nx*Ny)*0 + block*Nx + i] = 1-2*lambda1;
                    B[(Nx*Ny)*0 + block*Nx + i] = 1-2*lambda2;
                    
                } else {
                    A[(Nx*Ny)*0 + block*Nx + i] = 1-3*lambda1;
                    B[(Nx*Ny)*0 + block*Nx + i] = 1-3*lambda2;
                }

            } else {

                A[(Nx*Ny)*2 + block*Nx + i] = lambda1;
                B[(Nx*Ny)*2 + block*Nx + i] = lambda2;
                
                if (i == 0 || i == Nx-1) {
                    A[(Nx*Ny)*0 + block*Nx + i] = 1-3*lambda1;
                    B[(Nx*Ny)*0 + block*Nx + i] = 1-3*lambda2;
                } else {
                    A[(Nx*Ny)*0 + block*Nx + i] = 1-4*lambda1;
                    B[(Nx*Ny)*0 + block*Nx + i] = 1-4*lambda2;
                }

            }
        }
    }
}
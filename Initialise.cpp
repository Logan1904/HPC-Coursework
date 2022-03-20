#include "ReactionDiffusion.h"

/**
 * @brief Method to initialise our A and B matrices
 *        A matrix defined as: u[n+1] = A*u[n] + f1(u[n],v[n])
 *        B matrix defined as: v[n+1] = B*v[n] + f2(u[n],v[n])
 *        A and B matrices are symmetric, and hence created in the Column-Major, Upper Band, Packed storage form
 */

void ReactionDiffusion::Initialise() {
    int length_col = Nx+1;
    int length_block = Nx*length_col;

    #pragma omp parallel 
    {
        #pragma omp for collapse(2)

            for (int block = 0; block < Ny; ++block) {
                for (int i = 0; i < Nx; ++i) {
                    A[length_col*i + length_block*block + 0] = lambda1;
                    B[length_col*i + length_block*block + 0] = lambda2;
                    for (int j = 1; j < length_col-2; ++j) {
                        A[length_col*i + length_block*block + j] = 0.0;
                        B[length_col*i + length_block*block + j] = 0.0;
                    }

                    if (i == 0) {
                        A[length_col*i + length_block*block + length_col-2] = 0.0;
                        B[length_col*i + length_block*block + length_col-2] = 0.0;
                    } else {
                        A[length_col*i + length_block*block + length_col-2] = lambda1;
                        B[length_col*i + length_block*block + length_col-2] = lambda2;
                    }

                    if (block == 0 || block == Ny-1) {
                        if (i == 0 || i == Nx-1) {
                            A[length_col*i + length_block*block + length_col-1] = 1-2*lambda1;
                            B[length_col*i + length_block*block + length_col-1] = 1-2*lambda2;
                        } else {
                            A[length_col*i + length_block*block + length_col-1] = 1-3*lambda1;
                            B[length_col*i + length_block*block + length_col-1] = 1-3*lambda2;
                        }
                    } else {
                        if (i == 0 || i == Nx-1) {
                            A[length_col*i + length_block*block + length_col-1] = 1-3*lambda1;
                            B[length_col*i + length_block*block + length_col-1] = 1-3*lambda2;
                        } else {
                            A[length_col*i + length_block*block + length_col-1] = 1-4*lambda1;
                            B[length_col*i + length_block*block + length_col-1] = 1-4*lambda2;
                        }
                    }

                }
            }
    }
}
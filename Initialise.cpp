#include "ReactionDiffusion.h"

// Method to initialise A and B matrix
void ReactionDiffusion::Initialise(int rank, int size) {
    // First (size-X) processes compute Y rows
    // Remaining X processes compute Y+1 rows
    int X = (Nx*Ny) % size;
    int Y = (Nx*Ny - X)/ size;

    int length = Nx*Ny;

    int n_rows;

    if (rank < size-X) {
        n_rows = Y;
    } else {
        n_rows = Y+1;
    }

    A = new double[n_rows*length]();
    B = new double[n_rows*length]();
    
    for (int loc_row = 0; loc_row < n_rows; ++loc_row) {

        int glob_row;
        if (rank < size-X) {
            glob_row = rank*Y + loc_row;
        } else {
            glob_row = (size-X)*Y + (rank-(size-X))*(Y+1) + loc_row;
        }

        int block = (int) glob_row / Nx;
        
        
        if (block == 0) {                                       // First block
            if (glob_row == 0) {                                    // First row
                A[loc_row*length + glob_row] = 1-2*lambda1;
                B[loc_row*length + glob_row] = 1-2*lambda2;

                A[loc_row*length + glob_row + 1] = lambda1;
                B[loc_row*length + glob_row + 1] = lambda2;

                A[loc_row*length + glob_row + Nx] = lambda1;
                B[loc_row*length + glob_row + Nx] = lambda2;
            } else if (glob_row == Nx-1) {                          // Last row
                A[loc_row*length + glob_row] = 1-2*lambda1;
                B[loc_row*length + glob_row] = 1-2*lambda2;
                
                A[loc_row*length + glob_row - 1] = lambda1;
                B[loc_row*length + glob_row - 1] = lambda2;

                A[loc_row*length + glob_row + Nx] = lambda1;
                B[loc_row*length + glob_row + Nx] = lambda2;
            } else {                                                // Middle rows
                A[loc_row*length + glob_row] = 1-3*lambda1;
                B[loc_row*length + glob_row] = 1-3*lambda2;

                A[loc_row*length + glob_row - 1] = lambda1;
                B[loc_row*length + glob_row - 1] = lambda2;
                
                A[loc_row*length + glob_row + 1] = lambda1;
                B[loc_row*length + glob_row + 1] = lambda2;
                
                A[loc_row*length + glob_row + Nx] = lambda1;
                B[loc_row*length + glob_row + Nx] = lambda2;
            }
        } else if (block == Ny-1) {                             // Last block
            if (glob_row == Nx*Ny-Nx) {                              // First row
                A[loc_row*length + glob_row] = 1-2*lambda1;
                B[loc_row*length + glob_row] = 1-2*lambda2;
                
                A[loc_row*length + glob_row + 1] = lambda1;
                B[loc_row*length + glob_row + 1] = lambda2;
                
                A[loc_row*length + glob_row - Nx] = lambda1;
                B[loc_row*length + glob_row - Nx] = lambda2;
            } else if (glob_row == Nx*Ny-1) {                       // Last row
                A[loc_row*length + glob_row] = 1-2*lambda1;
                B[loc_row*length + glob_row] = 1-2*lambda2;
                
                A[loc_row*length + glob_row - 1] = lambda1;
                B[loc_row*length + glob_row - 1] = lambda2;
                
                A[loc_row*length + glob_row - Nx] = lambda1;
                B[loc_row*length + glob_row - Nx] = lambda2;
            } else {                                                // Middle rows
                A[loc_row*length + glob_row] = 1-3*lambda1;
                B[loc_row*length + glob_row] = 1-3*lambda2;
                
                A[loc_row*length + glob_row - 1] = lambda1;
                B[loc_row*length + glob_row - 1] = lambda2;
                
                A[loc_row*length + glob_row + 1] = lambda1;
                B[loc_row*length + glob_row + 1] = lambda2;
                
                A[loc_row*length + glob_row - Nx] = lambda1;
                B[loc_row*length + glob_row - Nx] = lambda2;
            }
        } else {                                                // Middle blocks
            if (glob_row % Nx == 0) {                               // First row
                A[loc_row*length + glob_row] = 1-3*lambda1;
                B[loc_row*length + glob_row] = 1-3*lambda2;
                
                A[loc_row*length + glob_row + 1] = lambda1;
                B[loc_row*length + glob_row + 1] = lambda2;
                
                A[loc_row*length + glob_row + Nx] = lambda1;
                B[loc_row*length + glob_row + Nx] = lambda2;
                
                A[loc_row*length + glob_row - Nx] = lambda1;
                B[loc_row*length + glob_row - Nx] = lambda2;
            } else if ((glob_row+1) % Nx == 0) {                    // Last row
                A[loc_row*length + glob_row] = 1-3*lambda1;
                B[loc_row*length + glob_row] = 1-3*lambda2;
                
                A[loc_row*length + glob_row - 1] = lambda1;
                B[loc_row*length + glob_row - 1] = lambda2;
                
                A[loc_row*length + glob_row + Nx] = lambda1;
                B[loc_row*length + glob_row + Nx] = lambda2;
                
                A[loc_row*length + glob_row - Nx] = lambda1;
                B[loc_row*length + glob_row - Nx] = lambda2;
            } else {                                                // Middle rows
                A[loc_row*length + glob_row] = 1-4*lambda1;
                B[loc_row*length + glob_row] = 1-4*lambda2;
                
                A[loc_row*length + glob_row + 1] = lambda1;
                B[loc_row*length + glob_row + 1] = lambda2;
                
                A[loc_row*length + glob_row - 1] = lambda1;
                B[loc_row*length + glob_row - 1] = lambda2;
                
                A[loc_row*length + glob_row + Nx] = lambda1;
                B[loc_row*length + glob_row + Nx] = lambda2;
                
                A[loc_row*length + glob_row - Nx] = lambda1;
                B[loc_row*length + glob_row - Nx] = lambda2;
            }
        }
    }
}
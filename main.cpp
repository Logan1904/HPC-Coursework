#include "ReactionDiffusion.h"
#include "ProcessArgs.h"

int main(int argc, char* argv[]) {
    // Initialise MPI
    MPI_Init(&argc, &argv);

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    // Declare parameter variables
    double dt, T, a, b, mu1, mu2, eps;
    int Nx, Ny;

    // Parse command line
    int error = ProcessArgs(rank, argc, argv, dt, T, Nx, Ny, a, b, mu1, mu2, eps);

    if (error = 1) {
        MPI_Finalize();
        return 0;
    }
    
    ReactionDiffusion my_prob;

    my_prob.SetParameters(0.001,100.0,101,101,0.75,0.06,5.0,0.0,50.0);

    my_prob.SetInitialConditions();

    my_prob.Write();

    MPI_Finalize();
}
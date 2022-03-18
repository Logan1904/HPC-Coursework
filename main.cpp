#include "ReactionDiffusion.h"
#include "ProcessArgs.h"

int main(int argc, char* argv[]) {

    // Declare parameter variables
    double dt, T, a, b, mu1, mu2, eps;
    int Nx, Ny;

    // Parse command line
    int error = ProcessArgs(argc, argv, dt, T, Nx, Ny, a, b, mu1, mu2, eps);

    if (error == 1) {
        return 0;
    }

    ReactionDiffusion my_prob;

    my_prob.SetParameters(dt,T,Nx,Ny,a,b,mu1,mu2,eps);

    my_prob.SetInitialConditions();

    my_prob.Initialise();

    //my_prob.TimeIntegrate(rank, size);

    //my_prob.Write();
}
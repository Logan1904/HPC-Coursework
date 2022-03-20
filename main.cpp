#include "ReactionDiffusion.h"
#include "ProcessArgs.h"

#include <omp.h>

int main(int argc, char* argv[]) {

    // Declare parameter variables
    double dt, T, a, b, mu1, mu2, eps;
    int Nx, Ny, np;

    // Parse command line
    try {
        ProcessArgs(argc, argv, dt, T, Nx, Ny, a, b, mu1, mu2, eps, np);
    } catch (const std::invalid_argument& e) {
        std::cout << "Program terminated: " << e.what() << std::endl;
        return 0;
    }

    omp_set_num_threads(np);

    ReactionDiffusion my_prob;

    my_prob.SetParameters(dt,T,Nx,Ny,a,b,mu1,mu2,eps);

    my_prob.SetInitialConditions();
    
    my_prob.TimeIntegrate();
    
    my_prob.Write();
}
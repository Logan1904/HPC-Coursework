#include "ReactionDiffusion.h"

/**
 * @brief Method to set class object parameters from user inputs
 * 
 * @param dt Time-step
 * @param T Total integration time
 * @param Nx Number of grid points in x
 * @param Ny Number of grid points in y
 * @param a Value of parameter a
 * @param b Value of parameter b
 * @param mu1 Value of parameter mu1
 * @param mu2 Value of parameter mu2
 * @param eps Value of parameter epsilon
 */

// Method to set parameters
void ReactionDiffusion::SetParameters(double dt, double T, int Nx, int Ny, double a, double b, double mu1, double mu2, double eps) {
    this->dt = dt;
    this->T = T;

    Nt = int(T/dt);
    
    this->Nx = Nx;
    this->Ny = Ny;
    this->a = a;
    this->b = b;
    this->mu1 = mu1;
    this->mu2 = mu2;
    this->eps = eps;

    lambda1 = mu1*dt/(h*h);
    lambda2 = mu2*dt/(h*h);

    A = new double[(3)*(Nx*Ny)]();
    B = new double[(3)*(Nx*Ny)]();

    u = new double[Nx*Ny];
    v = new double[Nx*Ny];
}
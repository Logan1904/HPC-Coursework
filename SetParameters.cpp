#include "ReactionDiffusion.h"

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

    A = new double[(Nx+1)*(Nx*Ny)]();
    B = new double[(Nx+1)*(Nx*Ny)]();

    u = new double[Nx*Ny];
    v = new double[Nx*Ny];
}
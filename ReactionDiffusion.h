// Class for computing Reaction Diffusion PDE (variant of Barkley model)
class ReactionDiffusion {
    private:
        // Attributes
        double dt, T;
        int Nt;

        double h = 1.0;
        int Nx, Ny;

        double a, b, mu1, mu2, eps;
        double lambda1, lambda2;

        double* u, *v;
        double* A, *B;

    public:
        // Methods
        void SetParameters(double, double, int, int, double, double, double, double, double);
        void SetInitialConditions();
        void Initialise();
        void TimeIntegrate(int);
        void Write();
};
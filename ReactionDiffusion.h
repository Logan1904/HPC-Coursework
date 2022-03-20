/**
 * @class ReactionDiffusion
 * @brief Describes the Reaction-Diffusion PDE (variant of Barkley model)
 */
class ReactionDiffusion {
    private:
        // Time attributes
        double dt, T;
        int Nt;

        // Space attributes
        double h = 1.0;
        int Nx, Ny;

        // Parameter attributes
        double a, b, mu1, mu2, eps;
        double lambda1, lambda2;

        // Pointers to u and v vectors
        double* u, *v;

        // Pointers to A and B matrices
        double* A, *B;

    public:
        // Method to set parameter values
        void SetParameters(double, double, int, int, double, double, double, double, double);

        // Method to set initial conditions
        void SetInitialConditions();

        // Method to initialise A and B matrices
        void Initialise();

        // Method to time integrate the PDE
        void TimeIntegrate();
        
        // Method to write solution to a txt file
        void Write();
};
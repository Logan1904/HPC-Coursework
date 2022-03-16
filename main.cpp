#include "ReactionDiffusion.h"
#include "Print.h"

int main() {

    ReactionDiffusion my_prob;

    my_prob.SetParameters(0.001,100.0,101,101,0.75,0.06,5.0,0.0,50.0);

    my_prob.SetInitialConditions();

    my_prob.Write();
}
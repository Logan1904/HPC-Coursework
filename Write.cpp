#include "ReactionDiffusion.h"

#include <fstream>
#include <iomanip>

/**
 * @brief Method to write our solution vectors 'u' and 'v' to the file 'output.txt'
 * 
 */

void ReactionDiffusion::Write() {
    
    std::ofstream vOut("output.txt", std::ios::out | std::ios::trunc);
    vOut.precision(5);

    for (int j = 0; j < Ny; ++j) {
        for (int i = 0; i < Nx; ++i) {
            vOut << i * 1.0 / double(Nx - 1) << " " << j * 1.0 / double(Ny - 1) << " " << u[Nx*j + i] << " " << v[Nx*j + i] << std::endl;
        }
        vOut << std::endl;
    }

    vOut.close();
}
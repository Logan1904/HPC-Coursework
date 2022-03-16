#include "ProcessArgs.h"

namespace po = boost::program_options;

int ProcessArgs(int &rank, int &argc, char* argv[], double &dt, double &T, int &Nx, int &Ny, double &a, double &b, double &mu1, double &mu2, double &eps) {
    // Parse command line
    po::options_description description("Parameters");
    
    description.add_options()
        ("help", "produce help message")
        ("dt", po::value<double>(&dt)->required(), "Time-step to use")
        ("T", po::value<double>(&T)->required(), "Total integration time")
        ("Nx", po::value<int>(&Nx)->required(), "Number of grid points in x")
        ("Ny", po::value<int>(&Ny)->required(), "Number of grid points in y")
        ("a", po::value<double>(&a)->required(), "Value of parameter a")
        ("b", po::value<double>(&b)->required(), "Value of parameter b")
        ("mu1", po::value<double>(&mu1)->required(), "Value of parameter mu1")
        ("mu2", po::value<double>(&mu2)->required(), "Value of parameter mu2")
        ("eps", po::value<double>(&eps)->required(), "Value of parameter eps");

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, description), vm);

    if (vm.count("help")) {
        if (rank == 0) {
            std::cout << description;
        }
        return 1;
    }

    // Check if all arguments provided
    try {
        po::notify(vm);
    } catch (std::exception& e) {
        if (rank == 0) {
            std::cout << "Error: " << e.what() << std::endl;
            std::cout << description << std::endl;
            return 1;
        }
    }

    return 0;
}
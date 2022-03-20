#include "ProcessArgs.h"

namespace po = boost::program_options;

/**
 * @brief Function to parse command-line inputs to our parameter variables
 * 
 * @param argc Integer value of the number of command line arguments
 * @param argv Pointer array of the command line arguments
 * @param dt Time-step
 * @param T Total integration time
 * @param Nx Number of grid points in x
 * @param Ny Number of grid points in y
 * @param a Value of parameter a
 * @param b Value of parameter b
 * @param mu1 Value of parameter mu1
 * @param mu2 Value of parameter mu2
 * @param eps Value of parameter epsilon
 * @param np Number of threads to use with OpenMP
 * 
 * @return int If 'help' argument specified, or missing an argument, function returns 1. Otherwise, returns 1
 */
void ProcessArgs(int &argc, char* argv[], double &dt, double &T, int &Nx, int &Ny, double &a, double &b, double &mu1, double &mu2, double &eps, int &np) {
    // Parse command line
    po::options_description description("Parameters");
    
    description.add_options()
        ("help", "Produce this help message")
        ("np", po::value<int>(&np)->required(), "Number of threads")
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
        std::cout << description << std::endl;
        throw std::invalid_argument ("Help option specified");
    }

    // Check if all arguments provided
    try {
        po::notify(vm);
    } catch (std::exception& e) {
        std::cout << "Error: " << e.what() << std::endl << std::endl;
        std::cout << "Use argument --help to produce help message" << std::endl << std::endl;
        throw std::invalid_argument ("Certain argument(s) not specified");
    }

}
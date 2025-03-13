#include <iostream>
#include <string>
#include <cstring>
#include <stdexcept>
#include "src/simulation.hpp"


/*
Example CLI Usage:
    Using custom values for m and n:
        make
        ./main --numTrucks 4 --numStations 3

    Using default values for m and n:
        make
        ./main
*/

int main(int argc, char* argv[]) {
    // Set by default can be set by flags
    int numTrucks = 5;
    int numStations = 2;

    for (int flag = 0; flag < argc; flag++) {
        if (std::strcmp(argv[flag], "--numTrucks") == 0) {
            if (flag + 1 < argc) { // Bounds check
                std::string num = argv[flag + 1];
                try {
                    numTrucks = std::stoi(num);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error: Invalid argument for stoi: " << e.what() << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error: Out of range argument for stoi: " << e.what() << std::endl;
                }
            } else {
                std::cerr << "Error: Missing value after --numTrucks" << std::endl;
            }
        }

        if (std::strcmp(argv[flag], "--numStations") == 0) {
            if (flag + 1 < argc) {
                std::string num = argv[flag + 1];
                try {
                    numStations = std::stoi(num);
                } catch (const std::invalid_argument& e) {
                    std::cerr << "Error, invalid argument for stoi: " << e.what() << std::endl;
                } catch (const std::out_of_range& e) {
                    std::cerr << "Error, out of range argument for stoi: " << e.what() << std::endl;
                }
            } else {
                std::cerr << "Error: Missing value after --numStations" << std::endl;
            }
        }
    }
    
    Simulation simulation(numTrucks, numStations);
    simulation.start();
    return 0;
}
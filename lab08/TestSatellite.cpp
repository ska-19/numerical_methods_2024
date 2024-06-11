#include <iostream>
#include "Everhart.h"
#include "SatelliteEq.h"

using namespace ADAI;

template<typename T>
void runTest() {
    T dt = static_cast<T>(10.0);
    T t_end = static_cast<T>(86400.0);
    std::vector<T> initial_conditions = {static_cast<T>(7000e3), static_cast<T>(0.0), static_cast<T>(0.0),
                                         static_cast<T>(0.0), static_cast<T>(7.12e3), static_cast<T>(1.0e3)};

    Everhart<T> solver(dt, initial_conditions, satelliteEquations<T>);
    std::vector<std::vector<T>> trajectory = solver.integrate(t_end);

    for (const auto &state: trajectory) {
        std::cout << "x: " << state[0] << ", y: " << state[1] << ", z: " << state[2]
                  << ", vx: " << state[3] << ", vy: " << state[4] << ", vz: " << state[5] << std::endl;
    }
}

int main() {
    std::cout << "Testing with double:\n";
    runTest<double>();

    std::cout << "Testing with float:\n";
    runTest<float>();

    std::cout << "Testing with long double:\n";
    runTest<long double>();

    return 0;
}
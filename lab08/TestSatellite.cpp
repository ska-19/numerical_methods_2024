#include <iostream>
#include "Everhart.h"
#include "SatelliteEq.h"

template<typename T>
void runTest() {
    T dt = static_cast<T>(10.0);
    T t_end = static_cast<T>(86400.0);
    std::vector<T> initial_conditions = {static_cast<T>(7000e3), static_cast<T>(0.0), static_cast<T>(0.0), static_cast<T>(7.12e3)}; // Начальные условия: {x, y, vx, vy}

    ADAI::Everhart<T> solver(dt, initial_conditions, ADAI::satelliteEquations<T>);
    std::vector<std::vector<T>> trajectory = solver.integrate(t_end);

    for (const auto& state : trajectory) {
        std::cout << "x: " << state[0] << ", y: " << state[1] << ", vx: " << state[2] << ", vy: " << state[3] << std::endl;
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
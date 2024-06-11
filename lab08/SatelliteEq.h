#ifndef SATELLITEEQ_H
#define SATELLITEEQ_H

#include <vector>
#include <cmath>
#include "Consts.h"

namespace ADAI {

    template<typename T>
    std::vector<T> satelliteEquations(const std::vector<T> &state) {
        T x = state[0];
        T y = state[1];
        T z = state[2];
        T vx = state[3];
        T vy = state[4];
        T vz = state[5];

        // Calculate the distance from the center of the Earth
        T r = std::sqrt(x * x + y * y + z * z);

        // Calculate the acceleration components due to gravity
        T ax = -G<T> * M<T> * x / (r * r * r);
        T ay = -G<T> * M<T> * y / (r * r * r);
        T az = -G<T> * M<T> * z / (r * r * r);

        return {vx, vy, vz, ax, ay, az};
    } // Template function to define the differential equations for satellite motion

}

#endif // SATELLITEEQ_H
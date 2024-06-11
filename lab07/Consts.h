#ifndef CONSTS_H
#define CONSTS_H

#include <cmath>
#include <climits>

namespace ADAI {
    constexpr double R_air = 287.0528;

    constexpr double p0 = 101325.0; // давление в 0 слое
    constexpr double p1 = 22632.38; // давление в 1 слое
    constexpr double p2 = 5367.01; // давление во 2 слое
    constexpr double p3 = 868.02; // давление в 3 слое

    constexpr double h0 = 0.0;
    constexpr double h1 = 11000.0;
    constexpr double h2 = 20000.0;
    constexpr double h3 = 32000.0;

    constexpr double r0 = 0.0065;
    constexpr double r1 = 0.0;
    constexpr double r2 = -0.001;
    constexpr double r3 = -0.0028;

    constexpr double T0 = 288.15; // 0 слой
    constexpr double T1 = 213.65; // 1 слой
    constexpr double T2 = 213.65; // 2 слой
    constexpr double T3 = 225.65; // 3 слой

    constexpr double g = 9.80655;
    constexpr double pi = M_PI;
    constexpr double diameter = 0.216;
    double S = pi * diameter * diameter / 4.0;

    static constexpr double mass = 106.0;
    // Consts for RKF45
    static constexpr double alpha_table[6] = {0, 1.0 / 2, 1.0 / 2, 1.0, 2.0 / 3, 1.0 / 5};
    static constexpr double beta_table[6][6] = {
            {0,          0,         0,           0,          0,            0},
            {1.0 / 2,    0,         0,           0,          0,            0},
            {1.0 / 4,    1.0 / 4,   0,           0,          0,            0},
            {0,          -1.0,      2.0,         0,          0,            0},
            {7.0 / 27,   10.0 / 27, 0,           1.0 / 27,   0,            0},
            {28.0 / 625, -1.0 / 5,  546.0 / 625, 54.0 / 625, -378.0 / 625, 0}
    };
    static constexpr double gamma_table[6] = {1.0 / 24, 0, 0, 5.0 / 48, 27.0 / 56, 125.0 / 336};
    static constexpr double delta_table[6] = {1.0 / 8, 0, 2.0 / 3, 1.0 / 16, -27.0 / 56, -125.0 / 336};
    // u_0 vector
    static constexpr double x0 = 0.0;
    static constexpr double y0 = 0.0;
    static constexpr double v0 = 1640.0;
    //step
    static constexpr double h = 1e-2;
}

#endif //CONSTS_H

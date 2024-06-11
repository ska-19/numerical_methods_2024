#ifndef CONSTS_H
#define CONSTS_H

#include <cmath>
#include <climits>

namespace ADAI {
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
    static constexpr double h = 1e-6;
}

#endif //CONSTS_H

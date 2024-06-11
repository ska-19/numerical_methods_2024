#pragma once

#include <iostream>
#include <valarray>
#include <gsl/gsl_odeiv2.h>
#include <gsl/gsl_errno.h>

#include "SAM.h"

namespace ADAI {
    class ParisGun { // история кайф кстати
    public:
        static const int n = 13;
        static constexpr inline double M_i[n] = { // M_i in machs
                0.4, 0.6, 0.8, 0.86, 0.91, 0.95, 1.0, 1.2, 1.4, 1.61, 1.8, 2.1, 2.2
        };
        static constexpr inline double c_d[n] = { //precalced
                0.086, 0.097, 0.1, 0.11, 0.125, 0.215, 0.37, 0.32, 0.305, 0.285, 0.27, 0.235, 0.22
        };

        static double interpolate(double v_M) {
            int ind = -1;
            if (v_M < M_i[0]) {
                return c_d[0];
            } else if (v_M > M_i[n - 1]) {
                return c_d[n - 1];
            } else {
                for (int i = 0; i < n - 1; ++i) {
                    if (v_M >= M_i[i] && v_M <= M_i[i + 1]) {
                        ind = i;
                        break;
                    }
                }
            }

            if (ind != -1) {
                double c_d_interp = c_d[ind] + (c_d[ind + 1] - c_d[ind]) * (v_M - M_i[ind]) / (M_i[ind + 1] - M_i[ind]);
                return c_d_interp;
            } else {
                std::cerr << "Cлишком большая скорость" << std::endl;
                return -1;
            }
        }
    };
}
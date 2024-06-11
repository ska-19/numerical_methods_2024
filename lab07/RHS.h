#ifndef RHS_H
#define RHS_H

#include "Consts.h"
#include "SAM.h"
#include "PG.h"

namespace ADAI {
    class RHS {
    private:
    public:
        constexpr static int N = 4;
        void operator()(const double a_t, const double a_y[N], double a_rhs[N]) const {
            double Q;
            double x = a_y[0];
            double v_x = a_y[1];
            double y = a_y[2];
            double v_y = a_y[3];
            double v = std::sqrt(v_x * v_x + v_y * v_y);
            double altitude = y;

            double ro = ADAI::SAM::get_ro(altitude);
            double A = ADAI::SAM::get_A(altitude);
            double M = v / A;
            double c_d_M = ParisGun::interpolate(M);
            Q = ro * v * v * S * c_d_M / 2;

            a_rhs[0] = a_y[1]; // dx/dt = v_x
            a_rhs[1] = -Q * a_y[1] / v / mass; // dv_x/dt
            a_rhs[2] = a_y[3]; // dy/dt = v_y
            a_rhs[3] = -Q * a_y[3] / v / mass - g; // dv_y/dt
        };
    };
}

#endif //RHS_H

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

        static int projectile_equations(double t, const double u[], double *u_point[], void *params) {
            double Q;
            double x = u[0];
            double v_x = u[1];
            double y = u[2];
            double v_y = u[3];
            double v = std::sqrt(v_x * v_x + v_y * v_y);
            double altitude = y;

            double ro = SAM::get_ro(altitude);
            double A = SAM::get_A(altitude);
            double M = v / A;
            double c_d_M = interpolate(M);
            Q = ro * v * v * S * c_d_M / 2;

            *u_point[0] = u[1]; // dx/dt = v_x
            *u_point[1] = -Q * u[1] / v / mass; // dv_x/dt
            *u_point[2] = u[3]; // dy/dt = v_y
            *u_point[3] = -Q * u[3] / v / mass - g; // dv_y/dt
            return 0;
        }

        static void simulate_projectile_motion() {
            const gsl_odeiv2_step_type *T = ::gsl_odeiv2_step_rkf45;
            gsl_odeiv2_system sys = {
                    reinterpret_cast<int (*)(double, const double *, double *, void *)>(projectile_equations), nullptr,
                    4, nullptr};
            gsl_odeiv2_driver *d = gsl_odeiv2_driver_alloc_y_new(&sys, T, 1e-6, 1e-6, 0.0);

            double t = 0.0;
            double dt = 5.0;

            double u[4];
            u[0] = 0.0;
            u[1] = v_0 * std::cos(alpha_rad); // v_x
            u[2] = 0.0;
            u[3] = v_0 * std::sin(alpha_rad); // v_y


            while (u[2] >= 0) {
                std::cout << "t: " << t << " x: " << u[0] << " y: " << u[2] << " v_x: "
                                                                               ""
                                                                               "" << u[1] << " v_y: " << u[3] << std::endl;
                int status = gsl_odeiv2_driver_apply(d, &t, t + dt, u);
                if(status != GSL_SUCCESS){
                    std::cerr << "error" << std::endl;
                }
            }
            gsl_odeiv2_driver_free(d);
        }
    };
}

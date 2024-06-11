#ifndef TIMESTEPPERRKF45_H
#define TIMESTEPPERRKF45_H

#include <vector>
#include "RHS.h"
#include "Consts.h"

namespace ADAI {
    template<typename RHS>
    class TimeStepperRKF45 {
    private:
        RHS const *const m_rhs;
        double K1[RHS::N], K2[RHS::N], K3[RHS::N], K4[RHS::N], K5[RHS::N], K6[RHS::N];
    public:
        constexpr static int N = RHS::N;

        TimeStepperRKF45(RHS const *a_rhs) : m_rhs(a_rhs) {}

        //Making a step:
        //return <next_t, next_h>
        std::pair<double, double> operator()(double a_t, double a_y[N], double h, double a_y_next[N]) {

            double curr_y[N];
            for (int i = 0; i < N; ++i) curr_y[i] = a_y[i];

            //Calc K1
            m_rhs->operator()(a_t + alpha_table[0] * h, curr_y, K1);

            //Calc K2
            for (int i = 0; i < N; ++i) curr_y[i] = a_y[i] + h * beta_table[1][0] * K1[i];
            m_rhs->operator()(a_t + alpha_table[1] * h, curr_y, K2);

            //Calc K3
            for (int i = 0; i < N; ++i) curr_y[i] = a_y[i] + h * (beta_table[2][0] * K1[i] + beta_table[2][1] * K2[i]);
            m_rhs->operator()(a_t + alpha_table[2] * h, curr_y, K3);

            //Calc K4
            for (int i = 0; i < N; ++i)
                curr_y[i] = a_y[i] + h * (beta_table[3][0] * K1[i] + beta_table[3][1] * K2[i] +
                                          beta_table[3][2] * K3[i]);
            m_rhs->operator()(a_t + alpha_table[3] * h, curr_y, K4);

            //Calc K5
            for (int i = 0; i < N; ++i)
                curr_y[i] = a_y[i] + h * (beta_table[4][0] * K1[i] + beta_table[4][1] * K2[i] +
                                          beta_table[4][2] * K3[i] + beta_table[4][3] * K4[i]);
            m_rhs->operator()(a_t + alpha_table[4] * h, curr_y, K5);

            //Calc K6
            for (int i = 0; i < N; ++i)
                curr_y[i] = a_y[i] + h * (beta_table[5][0] * K1[i] + beta_table[5][1] * K2[i] +
                                          beta_table[5][2] * K3[i] + beta_table[5][3] * K4[i] +
                                          beta_table[5][4] * K5[i]);
            m_rhs->operator()(a_t + alpha_table[5] * h, curr_y, K6);

            //Calc a_y_next
            for (int i = 0; i < N; ++i) {
                a_y_next[i] = a_y[i] + h * (gamma_table[0] * K1[i] + gamma_table[1] * K2[i] + gamma_table[2] * K3[i] +
                                            gamma_table[3] * K4[i] + gamma_table[4] * K5[i] + gamma_table[5] * K6[i]);
                curr_y[i] = a_y[i] + h * (delta_table[0] * K1[i] + delta_table[1] * K2[i] + delta_table[2] * K3[i] +
                                          delta_table[3] * K4[i] + delta_table[4] * K5[i] + delta_table[5] * K6[i]);
            }

            return {a_t + h, h};
        }
    };
}

#endif //TIMESTEPPERRKF45_H

#pragma once

#include <gsl/gsl_fft_halfcomplex.h>

#include "Consts.h"

namespace ADAI {

    const int N = 31;
    double points[N + 2]; // точки для подсчета чебышева
    double g_x[N + 2]; // когда дебагал запихал все значения в массив, пусть останется
    double nodes[N + 2];  // точки для рсавнения насколько все хорошо
    double chebyshev[N + 1][N + 1] = {{0.0}}; // массив для хранения коэффициентов чебышева, для каждого полинома
    double result[N + 2] = {0};   // коэффициенты для фурье



    inline void initialize_points() {
        for (int i = 1; i <= N + 1; ++i) {
            points[i] = std::cos(ADAI::PI<double> * (2.0 * i - 1) / (2.0 * (N + 1)));
        }
    }

    inline void initialize_g_x() {
        for (int i = 1; i <= N + 1; ++i) {
            g_x[i] = std::exp(std::acos(points[i]));
        }
    }

    void initialize_nodes() {
        for (int i = 0; i <= N; ++i) {
            nodes[i] = ADAI::PI<double> * i / (N + 1);
        }
    }

    inline void initialize_chebyshev_polynomials() {
        chebyshev[0][0] = chebyshev[1][1] = 1;

        for (int order = 2; order <= N; ++order) {
            for (int i = order; i > 0; i--) {
                chebyshev[order][i] = 2 * chebyshev[order - 1][i - 1] - chebyshev[order - 2][i];
            }
            chebyshev[order][0] = -chebyshev[order - 2][0];
        }
    }

    double computeChebyshev(int k, double x) { //считаем k-тый полином чебышева
        double x_pow = 1;
        double res = 0;
        for (int i = 0; i <= k; i++) {
            res += chebyshev[k][i] * x_pow;
            x_pow *= x;
        }
        return res;
    }

    void initialize_a() { // считаем коэффициенты для фурье с помощью квадратуры Гаусса
        for (int k = 0; k <= N; ++k) {
            for (int i = 1; i <= N + 1; ++i) {
                result[k] += computeChebyshev(k, points[i]) * g_x[i];
            }
            result[k] *= 2.0 / (N + 1);
        }
        result[0] /= 2.0;
    }


    void FFT() {
        initialize_points();
        initialize_nodes();
        initialize_g_x();
        initialize_chebyshev_polynomials();
        initialize_a();

        size_t cnt = 2 * (N + 1);
        gsl_fft_real_radix2_transform(result, 1, cnt);
    }

    static bool is_initialized = false;

    template<typename T>
    constexpr T
    Exp_Fourier(T x) {
        if (!is_initialized) {
            FFT();
            is_initialized = true;
        }

        size_t i = 0;
        double prev_delta = std::abs(x - nodes[i]);
        for (; i <= N; ++i) {
            double delta = std::abs(x - nodes[i]);

            if (delta > prev_delta) {
                break;
            }

            prev_delta = delta;
        }

        return result[i];
    }

}
#pragma once

#include <cmath>
#include "Consts.h"
#include <gsl/gsl_chebyshev.h>
#include <gsl/gsl_linalg.h>

namespace ADAI {
    const int N = 32 - 1;
    double points[N + 2];
    double scale[N + 2];
    double chebyshev[N + 1][N + 1] = { 0.0 };
    double coefficients[N + 1] = { 0 };

    void initialize_points() {
        for (int i = 1; i <= N + 1; ++i) {
            points[i] = std::cos(ADAI::PI<double> * (2.0 * i - 1) / (2.0 * (N + 1)));
        }
    } // Compute points for evaluating Chebyshev polynomials

    void initialize_scale() {
        for (int i = 1; i <= N + 1; ++i) {
            scale[i] = std::exp(std::acos(points[i]));
        }
    } // Compute exp(arccos(point)) for each point

    void initialize_chebyshev_polynomials() {
        chebyshev[0][0] = chebyshev[1][1] = 1;

        for (int order = 2; order <= N; ++order) {
            for (int i = order; i > 0; i--) {
                chebyshev[order][i] = 2 * chebyshev[order - 1][i - 1] - chebyshev[order - 2][i];
            }
            chebyshev[order][0] = -chebyshev[order - 2][0];
        }
    } // Initialize Chebyshev polynomials coefficients up to order N

    double computeChebyshev(int k, double x) {
        double x_pow = 1;
        double res = 0;
        for (int i = 0; i <= k; i++) {
            res += chebyshev[k][i] * x_pow;
            x_pow *= x;
        }
        return res;
    } // Compute the k-th Chebyshev polynomial at point x

    void solve_coefficients_gsl() {
        gsl_matrix *A = gsl_matrix_alloc(N + 1, N + 1);
        gsl_vector *b = gsl_vector_alloc(N + 1);
        gsl_vector *c = gsl_vector_alloc(N + 1);
        gsl_permutation *p = gsl_permutation_alloc(N + 1);
        int signum;

        for (int i = 0; i <= N; ++i) {
            for (int j = 0; j <= N; ++j) {
                gsl_matrix_set(A, i, j, computeChebyshev(j, points[i + 1]));
            }
            gsl_vector_set(b, i, scale[i + 1]);
        }

        gsl_linalg_LU_decomp(A, p, &signum);
        gsl_linalg_LU_solve(A, p, b, c);

        for (int i = 0; i <= N; ++i) {
            coefficients[i] = gsl_vector_get(c, i);
        }

        gsl_permutation_free(p);
        gsl_vector_free(c);
        gsl_vector_free(b);
        gsl_matrix_free(A);
    } // Solve the system of linear equations to find the coefficients for Chebyshev approximation using GSL

    void initialize() {
        initialize_points();
        initialize_scale();
        initialize_chebyshev_polynomials();
        solve_coefficients_gsl();
    } // Initialize all necessary data for computations

    static bool is_initialized = false;

    template<typename T>
    T Exp_Chebyshev(T x) {
        if (!is_initialized) {
            initialize();
            is_initialized = true;
        }

        T result = 0;
        for (int k = 0; k <= N; ++k) {
            result += coefficients[k] * computeChebyshev(k, x);
        }

        return result;
    }  // Compute exp(x) using the Chebyshev polynomial series approximation

    // Explicit template instantiation
    template float Exp_Chebyshev<float>(float x);
    template double Exp_Chebyshev<double>(double x);
} // namespace ADAI
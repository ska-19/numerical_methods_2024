#ifndef NUMERICAL_METHODS_2024_EXP_C_H
#define NUMERICAL_METHODS_2024_EXP_C_H
#pragma once

#include "Consts.h"
#include <gsl/gsl_chebyshev.h>
#include <gsl/gsl_linalg.h>

namespace ADAI {
    template<typename T>
    constexpr T ex(T x, void *p) {
        return std::exp(x);
    }

    template<typename T>
    constexpr std::enable_if_t<std::is_floating_point_v<T>, T> Exp_Chebyshev(T x) {
        gsl_cheb_series *cs = gsl_cheb_alloc(N < T > +1);
        gsl_function F = {.function = &ex};

        gsl_cheb_init(cs, &F, -1, 1);
        T ans = gsl_cheb_eval(cs, x);
        gsl_cheb_free(cs);

        return ans;
    }
}
#endif //NUMERICAL_METHODS_2024_EXP_C_H

#ifndef NUMERICAL_METHODS_2024_EXP_H
#define NUMERICAL_METHODS_2024_EXP_H

#include "Consts.h"
#include "assert.h"

namespace ADAI {

    template<typename T>
    constexpr inline int MkExpTaylorOrder(bool positive = false) {
        T d = 10 * Eps<T>;
        T Ln2d2 = Ln2<T> / 2;
        T LHS_i = positive ? SqRt2<T> : 1.0;

        for (int i = 0; i < 1000;) {
            LHS_i *= Ln2d2 / static_cast<T>(++i);
            if (LHS_i < d) {
                return i - 1;
            }
        }
        assert (false);
    }

    enum class MethodE : int {
        Taylor,
        Pade
    };

    template<MethodE M = MethodE::Pade, typename T>
    constexpr T EXP(const T &x) {
        static_assert(std::is_floating_point<T>::value, "T must be a floating-point type.");


        // exp(x) = 2^(x/ln(2)) = 2^n * exp(y_1 * ln(2)) = 2^n * exp(x_1) = f_1 * 2^n
        // y = x/ln(2) y = n + y_1
        T y = x / Ln2<T>;

        // split y into integer and fractional parts
        T y_0;
        T y_1 = std::modf(y, &y_0);

        // check that y_0 is in the range of int
        if (y_0 < std::numeric_limits<int>::min())
            return 0;
        if (y_0 > std::numeric_limits<int>::max())
            return std::numeric_limits<T>::infinity();
        int n = static_cast<int>(y_0);

        // make mod(y_1) < 0.5
        if (y_1 < -0.5) {
            y_1 += 1;
            n -= 1;
        } else if (y_1 > 0.5) {
            y_1 -= 1;
            n += 1;
        }

        T x_1 = y_1 * Ln2<T>;

        // epsilon precision d = 10.0 * Eps<T>
        // calc f_1 = exp(x_1)
        // res: exp(t) * x_1^(n+1) / (n+1)!

        T f_1 = 1.0;
        T d = 10 * Eps<T>;
        T term = 1.0;
        if constexpr (M == MethodE::Taylor) {
            for (int i = 0; i < MkExpTaylorOrder<T>(x_1 >= 0);) {
                term *= x_1 / static_cast<T>(++i);
                f_1 += term;
            }
        }
        if constexpr (M == MethodE::Pade) {
            T p = 1;
            T q = 1;
            int sign = 1;
            const int coef[] = {2, 44, 66, 792, 15'840, 665'280};
            for (const int &i: coef) {
                term *= x_1;
                sign *= -1;
                p += term / i;
                q += sign * term / i;
            }
            f_1 = p / q;
        }
        return std::ldexp(f_1, n);
    }

}
#endif //NUMERICAL_METHODS_2024_EXP_H

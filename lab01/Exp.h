#ifndef NUMERICAL_METHODS_2024_EXP_H
#define NUMERICAL_METHODS_2024_EXP_H

#include "Consts.h"

namespace ADAI {
    template<typename T>
    constexpr T EXP(const T &x) {
        static_assert(std::is_floating_point<T>::value, "T must be a floating-point type.");

        // exp(x) = 2^(x/ln(2)) = 2^n * exp(y_1 * ln(2)) = 2^n * exp(x_1)
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

        int k = 0;
        T f_1 = 1.0;
        T d = 10 * Eps<T>;
        T term = 1.0;

        if (x_1 >= 0) {
            while (SqRt2<T> * term >= d) {
                term *= x_1 / static_cast<T>(++k);
                f_1 += term;
            }
        } else {
            while (term >= d) {
                term *= x_1 / static_cast<T>(++k);
                f_1 += term;
            }
        }

        return std::ldexp(f_1, n);
    }

}
#endif //NUMERICAL_METHODS_2024_EXP_H

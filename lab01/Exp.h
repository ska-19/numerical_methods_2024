
#ifndef NUMERICAL_METHODS_2024_EXP_H
#define NUMERICAL_METHODS_2024_EXP_H

#include <iostream>
#include <cmath>
#include <limits>
#include <type_traits>
#include <cfloat>

template<typename T>
constexpr inline T Ln2;
template<>
constexpr inline float Ln2<float> = 1 /  1.4426950408889634074f;
template<>
constexpr inline double Ln2<double> = 1 / M_LOG2E;
template<>
constexpr inline long double Ln2<long double> = 1 / 1.442695040888963407359924681001892137L;


template<typename T>
constexpr inline T Eps;
template<>
constexpr inline float Eps<float> = FLT_EPSILON;
template<>
constexpr inline double Eps<double> = DBL_EPSILON;
template<>
constexpr inline long double Eps<long double> = LDBL_EPSILON;

template<typename T>
constexpr inline T SqRt2;
template<>
constexpr inline float SqRt2<float> = 1.41421356237309504880f;
template<>
constexpr inline double SqRt2<double> = M_SQRT2;
template<>
constexpr inline long double SqRt2<long double> = 1.414213562373095048801688724209698079L;


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

    if (x_1 >= 0){
        while(SqRt2<T> * term >= d){
            term *= x_1 / static_cast<T>(++k);
            f_1 += term;
        }
    }
    else{
        while( term >= d){
            term *= x_1 / static_cast<T>(++k);
            f_1 += term;
        }
    }

    return std::ldexp(f_1, n);
}



#endif //NUMERICAL_METHODS_2024_EXP_H

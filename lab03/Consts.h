#ifndef NUMERICAL_METHODS_2024_CONSTS_H
#define NUMERICAL_METHODS_2024_CONSTS_H

#include <type_traits>
#include <iostream>
#include <cfloat>

namespace ADAI {
    template<typename T>
    constexpr inline T Ln2;
    template<>
    constexpr inline float Ln2<float> = 1 / 1.4426950408889634074f;
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
    constexpr inline T N;
    template<>
    constexpr inline float N<float> = 6;
    template<>
    constexpr inline double N<double> = 12;
    template<>
    constexpr inline long double N<long double> = 14;

}

#endif //NUMERICAL_METHODS_2024_CONSTS_H

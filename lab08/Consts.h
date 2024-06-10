#ifndef CONSTS_H
#define CONSTS_H

#include <cmath>

namespace ADAI {

    template<typename T>
    constexpr inline T G;
    template<>
    constexpr inline float G<float> = 6.67430e-11f;
    template<>
    constexpr inline double G<double> = 6.67430e-11;
    template<>
    constexpr inline long double G<long double> = 6.67430e-11L;

    template<typename T>
    constexpr inline T M;
    template<>
    constexpr inline float M<float> = 5.972e24f;
    template<>
    constexpr inline double M<double> = 5.972e24;
    template<>
    constexpr inline long double M<long double> = 5.972e24L;

}

#endif //CONSTS_H
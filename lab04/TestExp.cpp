#include <iostream>
#include <cmath>
#include <limits>

#include "Exp.h"

template<typename T>
void test_EXP(const T &x) {
    T exp_result_FTT = ADAI::Exp_Fourier(x);


    T std_exp_result = std::exp(x);

    std::cout << "std::exp(" << x << ") = " << std_exp_result << '\n';
    std::cout << "Exp_Fourier(" << x << ") =" << exp_result_FTT << "  diff = " << std::abs(exp_result_FTT - std_exp_result) << "\n";
}

int main() {
    test_EXP(0.0f);
    test_EXP(0.0);
    test_EXP(0.0l);
    std::cout << '\n';

    test_EXP(1.0f);
    test_EXP(1.0);
    test_EXP(1.0l);
    std::cout << '\n';

    test_EXP(-1.0f);
    test_EXP(-1.0);
    test_EXP(-1.0l);
    std::cout << '\n';

    test_EXP(10.0f);
    test_EXP(10.0);
    test_EXP(10.0l);
    std::cout << '\n';

    test_EXP(std::numeric_limits<float>::min());
    test_EXP(std::numeric_limits<double>::min());
    test_EXP(std::numeric_limits<long double>::min());
    std::cout << '\n';

    test_EXP(std::numeric_limits<float>::max());
    test_EXP(std::numeric_limits<double>::max());
    test_EXP(std::numeric_limits<long double>::max());
    std::cout << '\n';

    test_EXP(1e-30f);
    test_EXP(1e-30);
    test_EXP(1e-30l);
    std::cout << '\n';

    test_EXP(1.4426950408889634073e-5f);
    test_EXP(1.4426950408889634073e-5);
    test_EXP(1.4426950408889634073e-5l);
    std::cout << '\n';

    return 0;
}
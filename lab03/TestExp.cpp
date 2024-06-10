#include <iostream>
#include <cmath>
#include <limits>

#include "Exp.h"
#include "Exp_Chebyshev.h"

template<typename T>
void test_EXP(const T &x) {
    T exp_result_pade = ADAI::EXP<ADAI::MethodE::Pade>(x);
    T exp_result_taylor = ADAI::EXP<ADAI::MethodE::Taylor>(x);
    T exp_result_chebyshev = ADAI::Exp_Chebyshev(x);


    T std_exp_result = std::exp(x);

    std::cout << "std::exp(" << x << ") = " << std_exp_result << '\n';
    std::cout << "EXP<Pade>(" << x << ") = " << exp_result_pade << "  diff = "
              << std::abs(exp_result_pade - std_exp_result) << '\n';
    std::cout << "EXP<Taylor>(" << x << ") = " << exp_result_taylor << "  diff = "
              << std::abs(exp_result_taylor - std_exp_result) << '\n';
    std::cout << "EXP<Chebyshev>(" << x << ") = " << exp_result_chebyshev << "  diff = "
              << std::abs(exp_result_chebyshev - std_exp_result) << '\n';
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

    test_EXP(-10.0f);
    test_EXP(-10.0);
    test_EXP(-10.0l);
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

    test_EXP(20.0f);
    test_EXP(20.0);
    test_EXP(20.0l);
    std::cout << '\n';

    test_EXP(700.0f);
    test_EXP(700.0);
    test_EXP(700.0l);
    std::cout << '\n';

    test_EXP(1.4426950408889634073e-5f);
    test_EXP(1.4426950408889634073e-5);
    test_EXP(1.4426950408889634073e-5l);
    std::cout << '\n';

    return 0;
}
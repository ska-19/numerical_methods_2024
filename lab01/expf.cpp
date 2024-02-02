#include <iostream>
#include <cmath>
#include <limits>
#include <type_traits>

template<typename T>
T EXP(const T& x, const int n = 1000)
{
    static_assert(std::is_floating_point<T>::value, "T must be a floating-point type.");

    if (x < 0)
        return 1.0 / EXP(-x, n);

    T sum = 1.0;
    T term = 1.0;
    for (int i = 1; i <= n; i++)
    {
        term *= x / static_cast<T>(i);
        sum += term;
        if (std::abs(term) < std::numeric_limits<T>::epsilon()) break;
    }

    return sum;
}

template<typename T>
void test_EXP(const T& x) {
    T exp_result = EXP(x);
    T std_exp_result = std::exp(x);
    std::cout << "EXP(" << x << ") = " << exp_result << ", std::exp(" << x << ") = " << std_exp_result << ", diff = " << std::abs(exp_result - std_exp_result) << '\n';
}

int main() {
    test_EXP(0.0f);
    test_EXP(0.0);
    test_EXP(0.0l);

    test_EXP(1.0f);
    test_EXP(1.0);
    test_EXP(1.0l);

    test_EXP(-1.0f);
    test_EXP(-1.0);
    test_EXP(-1.0l);

    test_EXP(10.0f);
    test_EXP(10.0);
    test_EXP(10.0l);

    test_EXP(-10.0f);
    test_EXP(-10.0);
    test_EXP(-10.0l);

    test_EXP(std::numeric_limits<float>::min());
    test_EXP(std::numeric_limits<double>::min());
    test_EXP(std::numeric_limits<long double>::min());

    test_EXP(std::numeric_limits<float>::max());
    test_EXP(std::numeric_limits<double>::max());
    test_EXP(std::numeric_limits<long double>::max());

    test_EXP(1e-30f);
    test_EXP(1e-30);
    test_EXP(1e-30l);

    test_EXP(20.0f);
    test_EXP(20.0);
    test_EXP(20.0l);

    return 0;
}

#ifndef RHS_H
#define RHS_H

namespace ADAI {
    class RHS {
    private:
        double const m_omega2;
    public:
        constexpr static int N = 4;
        RHS(double a_omega) : m_omega2(a_omega * a_omega) {}

        void operator()(const double a_t, const double a_y[N], double a_rhs[N]) const {
            std::copy(a_y, a_y + N, a_rhs);
        };
    };
}

#endif //RHS_H

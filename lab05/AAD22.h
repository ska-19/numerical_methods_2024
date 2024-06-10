#ifndef LAB05_AAD22_H
#define LAB05_AAD22_H

#include <cmath>

namespace ADAI {

    class AAD22 {
    private:
        double m_val; // value of the function
        double m_d1[2]; // df/dx, df/dy
        double m_d2[3]; // d^2f/dx^2, d^2f/dy^2, d^2f/dxdy

    public:
        AAD22() = delete;

        constexpr AAD22(double c) // Constructor AAD22 from a constant
                : m_val(c),
                  m_d1{0, 0},
                  m_d2{0, 0, 0} {}

    private:
        constexpr AAD22(int i, double v) // i == 0 for x, i == 1 for y
                : m_val(v),
                  m_d1{(i == 0) ? 1.0 : 0.0, (i == 1) ? 1.0 : 0.0},
                  m_d2{0, 0, 0} {}

    public:
        constexpr static AAD22 VarX(double v) { return AAD22(0, v); }

        constexpr static AAD22 VarY(double v) { return AAD22(1, v); }

        // Acsessors to m_val, m_d1, m_d2
        constexpr double val() const { return m_val; }

        constexpr double d1(int i) const { return m_d1[i]; }

        constexpr double d2(int i) const { return m_d2[i]; }


        // operator overloading:
        // binary: "+", "+=", "-", "-=", "*", "*=", "/", "/="


        AAD22 &operator+=(const AAD22 &right) {
            m_val += right.m_val;
            m_d1[0] += right.m_d1[0];
            m_d1[1] += right.m_d1[1];
            m_d2[0] += right.m_d2[0];
            m_d2[1] += right.m_d2[1];
            m_d2[2] += right.m_d2[2];
            return *this;
        }

        AAD22 &operator+=(const double &right) {
            m_val += right;
            return *this;
        }

        AAD22 operator+(const AAD22 &right) const {
            AAD22 res = *this;
            res += right;
            return res;
        }

        AAD22 operator+(const double &right) const {
            AAD22 res = *this;
            res += right;
            return res;
        }

        AAD22 &operator-=(const AAD22 &right) {
            m_val -= right.m_val;
            m_d1[0] -= right.m_d1[0];
            m_d1[1] -= right.m_d1[1];
            m_d2[0] -= right.m_d2[0];
            m_d2[1] -= right.m_d2[1];
            m_d2[2] -= right.m_d2[2];
            return *this;
        }

        AAD22 &operator-=(const double &right) {
            m_val -= right;
            return *this;
        }

        AAD22 operator-(const AAD22 &right) const {
            AAD22 res = *this;
            res -= right;
            return res;
        }

        AAD22 operator-(const double &right) const {
            AAD22 res = *this;
            res -= right;
            return res;
        }


        AAD22 &operator*=(const AAD22 &right) {
            m_d2[0] = m_d2[0] * right.m_val + 2 * m_d1[0] * right.m_d1[0] + m_val * right.m_d2[0];
            m_d2[1] = m_d2[1] * right.m_val + 2 * m_d1[1] * right.m_d1[1] + m_val * right.m_d2[1];
            m_d2[2] = m_d2[2] * right.m_val + m_d1[0] * right.m_d1[1] + m_d1[1] * right.m_d1[0] + m_val * right.m_d2[2];
            m_d1[0] = m_d1[0] * right.m_val + m_val * right.m_d1[0];
            m_d1[1] = m_d1[1] * right.m_val + m_val * right.m_d1[1];
            m_val *= right.m_val;
            return *this;
        }

        AAD22 &operator*=(const double &right) {
            m_val *= right;
            m_d1[0] *= right;
            m_d1[1] *= right;
            m_d2[0] *= right;
            m_d2[1] *= right;
            m_d2[2] *= right;
            return *this;
        }

        AAD22 operator*(const AAD22 &right) const {
            AAD22 res = *this;
            res *= right;
            return res;
        }

        AAD22 operator*(const double &right) const {
            AAD22 res = *this;
            res *= right;
            return res;
        }

        AAD22 &operator/=(const AAD22 &right) {
            m_d2[0] = (m_d2[0] * right.m_val - 2 * m_d1[0] * right.m_d1[0] - m_val * right.m_d2[0]) /
                      (right.m_val * right.m_val);
            m_d2[1] = (m_d2[1] * right.m_val - 2 * m_d1[1] * right.m_d1[1] - m_val * right.m_d2[1]) /
                      (right.m_val * right.m_val);
            m_d2[2] = (m_d2[2] * right.m_val - m_d1[0] * right.m_d1[1] - m_d1[1] * right.m_d1[0] -
                       m_val * right.m_d2[2]) / (right.m_val * right.m_val);
            m_d1[0] = (m_d1[0] * right.m_val - m_val * right.m_d1[0]) / (right.m_val * right.m_val);
            m_d1[1] = (m_d1[1] * right.m_val - m_val * right.m_d1[1]) / (right.m_val * right.m_val);
            m_val /= right.m_val;
            return *this;
        }

        AAD22 &operator/=(const double &right) {
            m_val /= right;
            m_d1[0] /= right;
            m_d1[1] /= right;
            m_d2[0] /= right;
            m_d2[1] /= right;
            m_d2[2] /= right;
            return *this;
        }

        AAD22 operator/(const AAD22 &right) const {
            AAD22 res = *this;
            res /= right;
            return res;
        }

        AAD22 operator/(const double &right) const {
            AAD22 res = *this;
            res /= right;
            return res;
        }

        // double+AAD22
        friend AAD22 operator+(double left, const AAD22 &right) {
            AAD22 res = right;
            res.m_val += left;
            return res;
        }

        // double-AAD22
        friend AAD22 operator-(double left, const AAD22 &right) {
            AAD22 res = right;
            res.m_val = left - res.m_val;
            res.m_d1[0] = -res.m_d1[0];
            res.m_d1[1] = -res.m_d1[1];
            res.m_d2[0] = -res.m_d2[0];
            res.m_d2[1] = -res.m_d2[1];
            res.m_d2[2] = -res.m_d2[2];
            return res;
        }

        // double*AAD22
        friend AAD22 operator*(const double left, const AAD22 &right) {
            AAD22 res = right;
            res.m_val *= left;
            res.m_d1[0] *= left;
            res.m_d1[1] *= left;
            res.m_d2[0] *= left;
            res.m_d2[1] *= left;
            res.m_d2[2] *= left;
            return res;
        }

        // double/AAD22
        friend AAD22 operator/(const double left, const AAD22 &right) {
            AAD22 res = right;
            res.m_val = left / res.m_val;
            res.m_d1[0] = -left * res.m_d1[0] / (res.m_val * res.m_val);
            res.m_d1[1] = -left * res.m_d1[1] / (res.m_val * res.m_val);
            res.m_d2[0] = -left * res.m_d2[0] / (res.m_val * res.m_val);
            res.m_d2[1] = -left * res.m_d2[1] / (res.m_val * res.m_val);
            res.m_d2[2] = -left * res.m_d2[2] / (res.m_val * res.m_val);
            return res;
        }

        // implement unary: "+", "-"
        AAD22 operator+() const {
            return *this;
        }

        AAD22 operator-() const {
            AAD22 res = *this;
            res.m_val = -res.m_val;
            res.m_d1[0] = -res.m_d1[0];
            res.m_d1[1] = -res.m_d1[1];
            res.m_d2[0] = -res.m_d2[0];
            res.m_d2[1] = -res.m_d2[1];
            res.m_d2[2] = -res.m_d2[2];
            return res;
        }

        // and elementary functions: sin, cos, exp
        friend AAD22 sin(const AAD22 &x) {
            AAD22 res = x;
            res.m_val = sin(x.m_val);
            res.m_d1[0] = cos(x.m_val) * x.m_d1[0];
            res.m_d1[1] = cos(x.m_val) * x.m_d1[1];
            res.m_d2[0] = -sin(x.m_val) * x.m_d1[0] * x.m_d1[0] + cos(x.m_val) * x.m_d2[0];
            res.m_d2[1] = -sin(x.m_val) * x.m_d1[1] * x.m_d1[1] + cos(x.m_val) * x.m_d2[1];
            res.m_d2[2] = -sin(x.m_val) * x.m_d1[0] * x.m_d1[1] + cos(x.m_val) * x.m_d2[2];
            return res;
        }

        friend AAD22 cos(const AAD22 &x) {
            AAD22 res = x;
            res.m_val = cos(x.m_val);
            res.m_d1[0] = -sin(x.m_val) * x.m_d1[0];
            res.m_d1[1] = -sin(x.m_val) * x.m_d1[1];
            res.m_d2[0] = -cos(x.m_val) * x.m_d1[0] * x.m_d1[0] - sin(x.m_val) * x.m_d2[0];
            res.m_d2[1] = -cos(x.m_val) * x.m_d1[1] * x.m_d1[1] - sin(x.m_val) * x.m_d2[1];
            res.m_d2[2] = -cos(x.m_val) * x.m_d1[0] * x.m_d1[1] - sin(x.m_val) * x.m_d2[2];
            return res;
        }

        friend AAD22 exp(const AAD22 &x) {
            AAD22 res = x;
            res.m_val = exp(x.m_val);
            res.m_d1[0] = exp(x.m_val) * x.m_d1[0];
            res.m_d1[1] = exp(x.m_val) * x.m_d1[1];
            res.m_d2[0] = exp(x.m_val) * x.m_d2[0] + exp(x.m_val) * x.m_d1[0] * x.m_d1[0];
            res.m_d2[1] = exp(x.m_val) * x.m_d2[1] + exp(x.m_val) * x.m_d1[1] * x.m_d1[1];
            res.m_d2[2] = exp(x.m_val) * x.m_d2[2] + exp(x.m_val) * x.m_d1[0] * x.m_d1[1];
            return res;
        }
    };

}


#endif //LAB05_AAD22_H

#ifndef NUMERICAL_METHODS_2024_DIFF
#define NUMERICAL_METHODS_2024_DIFF
#pragma once

// include mixed arithmetic
#include <cmath>
#include "AAD22.h"

namespace ADAI {
    enum class WhichD : int {
        x, // df/dx
        y, // df/dy
        xx, // d^2f/dx^2
        yy, // d^2f/dy^2
        xy, // d^2f/dxdy
    };
    enum class DiffMethod : int {
        stencil3,
        stencil3Extra, // Extrapolation
        stencil5,
        stencil5Extra, // Extrapolation
        FwdAAD, // Automatic Analytic Differentiation
    };

    template<WhichD W, DiffMethod M, typename Callable>
    double Differentiator(Callable const &F, double x, double y) {
        double h_x = 1e-4;
        double h_y = 1e-4;
        if (abs(x) > 1)
            h_x *= abs(x);
        if (abs(y) > 1)
            h_y *= abs(y);

        double res = 0;
        if constexpr (M == DiffMethod::stencil3) {
            if constexpr (W == WhichD::x) {
                res = (F(x + h_x, y) - F(x - h_x, y)) / (2 * h_x);
            } else if constexpr (W == WhichD::y) {
                res = (F(x, y + h_y) - F(x, y - h_y)) / (2 * h_y);
            } else if constexpr (W == WhichD::xx) {
                res = (F(x + h_x, y) - 2 * F(x, y) + F(x - h_x, y)) / (h_x * h_x);
            } else if constexpr (W == WhichD::yy) {
                res = (F(x, y + h_y) - 2 * F(x, y) + F(x, y - h_y)) / (h_y * h_y);
            } else if constexpr (W == WhichD::xy) {
                res = (F(x + h_x, y + h_y) - F(x + h_x, y - h_y) - F(x - h_x, y + h_y) + F(x - h_x, y - h_y)) /
                      (4 * h_x * h_y);
            }
        } else if constexpr (M == DiffMethod::stencil3Extra) {
            // Call whith stencil3
            // true value:f'(x)
            // stencil3: d_3(h) = f'(x) + ah^2 + O(h^4)
            // stencil3: d_3(h/n) = f'(x) + ah^2/n^2 + O(h^4)
            // n = 2,3,4,...
            // d_3(h) - n^2 * d_3(h/n) = f'(x) *(1 - n^2) + O(h^4)
            // f'(x) = (d_3(h) - n^2 * d_3(h/n)) / (1 - n^2) + O(h^4)
            double n = 2;
            double d_3_h = Differentiator<W, DiffMethod::stencil3>(F, x, y);
            double d_3_h_n = Differentiator<W, DiffMethod::stencil3>(F, x, y);
            res = (d_3_h - n * n * d_3_h_n) / (1 - n * n);

        } else if constexpr (M == DiffMethod::stencil5) {
            if constexpr (W == WhichD::x) {
                res = (-F(x + 2 * h_x, y) + 8 * F(x + h_x, y) - 8 * F(x - h_x, y) + F(x - 2 * h_x, y)) / (12 * h_x);
            } else if constexpr (W == WhichD::y) {
                res = (-F(x, y + 2 * h_y) + 8 * F(x, y + h_y) - 8 * F(x, y - h_y) + F(x, y - 2 * h_y)) / (12 * h_y);
            } else if constexpr (W == WhichD::xx) {
                res = (-F(x + 2 * h_x, y) + 16 * F(x + h_x, y) - 30 * F(x, y) +
                       16 * F(x - h_x, y) - F(x - 2 * h_x, y)) /
                      (12 * h_x * h_x);
            } else if constexpr (W == WhichD::yy) {
                res = (-F(x, y + 2 * h_y) + 16 * F(x, y + h_y) - 30 * F(x, y) +
                       16 * F(x, y - h_y) - F(x, y - 2 * h_y)) /
                      (12 * h_y * h_y);
            } else if constexpr (W == WhichD::xy) {
                res = (F(x + h_x, y + h_y) - F(x + h_x, y - h_y) - F(x - h_x, y + h_y) + F(x - h_x, y - h_y)) /
                      (4 * h_x * h_y);
//                res += (F(x + 2 * h_x, y + 2 * h_y) - F(x + 2 * h_x, y - 2 * h_y) - F(x - 2 * h_x, y + 2 * h_y) +
//                        F(x - 2 * h_x, y - 2 * h_y)) / (12 * h_x * h_y);
            }

        } else if constexpr (M == DiffMethod::stencil5Extra) {
            // Call whith stencil5
            // true value:f'(x)
            // stencil5: d_5(h) = f'(x) + ah^4 + O(h^6)
            // stencil5: d_5(h/n) = f'(x) + ah^4/n^4 + O(h^6)
            // n = 2,3,4,...
            // d_5(h) - n^4 * d_5(h/n) = f'(x) *(1 - n^4) + O(h^6)
            // f'(x) = (d_5(h) - n^4 * d_5(h/n)) / (1 - n^4) + O(h^6)
            double n = 2;
            double d_5_h = Differentiator<W, DiffMethod::stencil5>(F, x, y);
            double d_5_h_n = Differentiator<W, DiffMethod::stencil5>(F, x, y);
            res = (d_5_h - n * n * n * n * d_5_h_n) / (1 - n * n * n * n);
        } else if constexpr (M == DiffMethod::FwdAAD) {
            AAD22 X = AAD22::VarX(x);
            AAD22 Y = AAD22::VarY(y);
            AAD22 Res = F(X, Y);
            if constexpr (W == WhichD::x) {
                res = Res.d1(0);
            } else if constexpr (W == WhichD::y) {
                res = Res.d1(1);
            } else if constexpr (W == WhichD::xx) {
                res = Res.d2(0);
            } else if constexpr (W == WhichD::yy) {
                res = Res.d2(1);
            } else if constexpr (W == WhichD::xy) {
                res = Res.d2(2);
            }

        }
        return res;
    } // Differentiator<WhichD::x, DiffMethod::stencil3>(F, x, y);
}
#endif //NUMERICAL_METHODS_2024_DIFF

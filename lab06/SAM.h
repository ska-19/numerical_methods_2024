#pragma once

#include "Consts.h"

namespace ADAI {
    class SAM {
    public:
        std::pair<double, double> operator()(double h) {
            double Th;
            double p;
            double ro;
            double A;
            if (h0 <= h && h <= h1) {
                Th = T0 - r0 * (h - h0);
                p = p0 * std::exp(g * std::log(1 - (r0 * (h - h0)) / T0) / (R_air * r0));
                ro = p / (R_air * (T0 - r0 * (h - h0)));
                A = std::sqrt(p / ro);
            } else if (h1 < h && h <= h2) {
                Th = T1 - r1 * (h - h1);
                p = p1 * std::exp(-g * (h - h1) / (R_air * T1));
                ro = p / (R_air * (T1 - r1 * (h - h1)));
                A = std::sqrt(p / ro);
            } else if (r2 < h && h <= h3) {
                Th = T2 - r2 * (h - h2);
                p = p2 * std::exp(g * std::log(1 - (r2 * (h - h2)) / T2) / (R_air * r2));
                ro = p / (R_air * (T2 - r2 * (h - h2)));
                A = std::sqrt(p / ro);
            } else {
                Th = T3 - r3 * (h - h3);
                p = p3 * std::exp(g * std::log(1 - (r3 * (h - h3)) / T3) / (R_air * r3));
                ro = p / (R_air * (T3 - r3 * (h - h3)));
                A = std::sqrt(p / ro);
            }
            return std::make_pair(p, ro);
        }

        static double get_p(double h) {
            double Th;
            double p;
            if (h0 <= h && h <= h1) {
                Th = T0 - r0 * (h - h0);
                p = p0 * std::exp(g * std::log(1 - (r0 * (h - h0)) / T0) / (R_air * r0));
            } else if (h1 < h && h <= h2) {
                Th = T1 - r1 * (h - h1);
                p = p1 * std::exp(-g * (h - h1) / (R_air * T1));
            } else if (h2 < h && h <= h3) {
                Th = T2 - r2 * (h - h2);
                p = p2 * std::exp(g * std::log(1 - (r2 * (h - h2)) / T2) / (R_air * r2));
            } else {
                Th = T3 - r3 * (h - h3);
                p = p3 * std::exp(g * std::log(1 - (r3 * (h - h3)) / T3) / (R_air * r3));
            }
            return p;
        }

        static double get_ro(double h) {
            double p = get_p(h);
            double ro;
            if (h0 <= h && h <= h1) {
                ro = p / (R_air * (T0 - r0 * (h - h0)));
            } else if (h1 < h && h <= h2) {
                ro = p / (R_air * (T1 - r1 * (h - h1)));
            } else if (h2 < h && h <= h3) {
                ro = p / (R_air * (T2 - r2 * (h - h2)));
            } else {
                ro = p / (R_air * (T3 - r3 * (h - h3)));
            }
            return ro;
        }

        static double get_A(double h) {
            double p = get_p(h);
            double ro = get_ro(h);
            double A = std::sqrt(p / ro);
            return A;
        }
    };
}



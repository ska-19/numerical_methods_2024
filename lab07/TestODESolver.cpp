#include <iostream>
#include <vector>
#include <cmath>
#include "Over-all integrator.h"
#include "TimeStepperRKF45.h"
#include "Observer.h"
#include "Consts.h"
#include "gsl/gsl_odeiv2.h"
#include "gsl/gsl_errno.h"
#include "RHS.h"

void runTest_1a() {
    double max_range = 0;
    int best_alpha = 0;
    for (int alpha = 40; alpha <= 60; ++alpha) {
        ADAI::ObserverChecker observer;
        ADAI::RHS rhs;
        double v_x = ADAI::v0 * std::cos(static_cast<double>(ADAI::pi * alpha / 180));
        double v_y = ADAI::v0 * std::sin(static_cast<double>(ADAI::pi * alpha / 180));
        double a_y0[ADAI::RHS::N] = {ADAI::x0, v_x, ADAI::y0, v_y}, a_yEnd[ADAI::RHS::N];
        double t_0 = 0, a_tEnd = 5000.0;
        ADAI::TimeStepperRKF45<ADAI::RHS> timeStepperRkf45(&rhs);
        ADAI::ODE_integrator<ADAI::TimeStepperRKF45<ADAI::RHS>, ADAI::ObserverChecker> integrator(&timeStepperRkf45,
                                                                                                  &observer);
        double curr_max_range = integrator(t_0, ADAI::h, a_tEnd, a_y0, a_yEnd);
        if (max_range < curr_max_range) {
            best_alpha = alpha;
            max_range = curr_max_range;
        }
    }
    std::cout << "Max range is " << max_range << '\n';
    std::cout << "This is achievable when alpha=" << best_alpha << '\n';
}

void runTest_1b() {
    ADAI::ObserverPlotTrajectory observer;
    ADAI::RHS rhs;
    double v_x = ADAI::v0 * std::cos(ADAI::pi * 55.0 / 180);
    double v_y = ADAI::v0 * std::sin(ADAI::pi * 55.0 / 180);
    double a_y0[ADAI::RHS::N] = {ADAI::x0, v_x, ADAI::y0, v_y}, a_yEnd[ADAI::RHS::N];
    double t_0 = 0, a_tEnd = 5000.0;

    ADAI::TimeStepperRKF45<ADAI::RHS> timeStepperRkf45(&rhs);
    std::cout << "Plot the trajectory:\n";
    ADAI::ODE_integrator<ADAI::TimeStepperRKF45<ADAI::RHS>, ADAI::ObserverPlotTrajectory> integrator(&timeStepperRkf45,
                                                                                                     &observer);
    integrator(t_0, ADAI::h, a_tEnd, a_y0, a_yEnd);
    std::cout << "Finished!\n";
}

int gsl_rhs(double t, const double *a_y, double *a_y_next, void *params) {
    auto *rhs = static_cast<ADAI::RHS *>(params);
    rhs->operator()(t, a_y, a_y_next);
    return GSL_SUCCESS;
}

void runTest_2() {
    double t_0 = 0.0;
    double a_tEnd = 1.0;
    double h = 1e-6;
    double v_x = ADAI::v0 * std::cos(55.0);
    double v_y = ADAI::v0 * std::sin(55.0);
    double a_y0[ADAI::RHS::N] = {ADAI::x0, ADAI::y0, v_x, v_y}, a_yEnd[ADAI::RHS::N];
    ADAI::RHS rhs;
    ADAI::ObserverPlotAllVector observer;
    // Using TimeStepperRKF45
    ADAI::TimeStepperRKF45<ADAI::RHS> rkf45_stepper(&rhs);
    std::cout << "TimeStepperRKF45 results:\n";
    ADAI::ODE_integrator<ADAI::TimeStepperRKF45<ADAI::RHS>, ADAI::ObserverPlotAllVector> integrator(&rkf45_stepper, &observer);
    integrator(t_0, h, a_tEnd, a_y0, a_yEnd);

    // Using TimeStepperRKF45
    gsl_odeiv2_system sys = {gsl_rhs, nullptr, ADAI::RHS::N, &rhs};
    gsl_odeiv2_driver *driver = gsl_odeiv2_driver_alloc_y_new(&sys, gsl_odeiv2_step_rkf45, h, 1e-6, 1e-6);
    std::vector<double> gsl_steps;
    for (double cord : a_y0) gsl_steps.push_back(cord);
    std::vector<std::vector<double>> gsl_trajectory;
    gsl_trajectory.push_back(gsl_steps);

    while (t_0 < a_tEnd) {
        int status = gsl_odeiv2_driver_apply(driver, &t_0, t_0 + h, gsl_steps.data());
        if (status != GSL_SUCCESS) {
            std::cerr << "GSL driver error: " << status << std::endl;
            break;
        }
        gsl_trajectory.push_back(gsl_steps);
    }
    gsl_odeiv2_driver_free(driver);

    std::cout << "GSL RKF45 results:\n";
    for (const auto &step: gsl_trajectory) {
        for (const auto &el: step) std::cout << el << " ";
        std::cout << "\n";
    }
}

int main() {
    std::cout << "Task 1:\n\n";
    std::cout << "1a:\n";
    runTest_1a();

    std::cout << "\n1b:\n";
    runTest_1b();

    std::cout << "\nTask 2:\n\n";
    runTest_2();

    return 0;
}
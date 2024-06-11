#ifndef OVERALL_INTEGRATOR_H
#define OVERALL_INTEGRATOR_H

#include "TimeStepperRKF45.h"
#include "Observer.h"
#include "iostream"

namespace ADAI {
    template<typename Stepper, typename Observer>
    class ODE_integrator {
    public:
        ODE_integrator(Stepper *a_stepper, Observer const *a_observer) : m_stepper(a_stepper), m_observer(a_observer) {}

        double operator()(double t_0, double h, double a_tEnd, double a_y0[], double a_yEnd[]) {
            double curr_t = t_0;
            double curr_y[Stepper::N], y_next[Stepper::N];
            std::copy(a_y0, a_y0 + Stepper::N, curr_y);

            while (curr_t < a_tEnd) {
                if (curr_t + h > a_tEnd) h = a_tEnd - curr_t;

                //Make a step
                auto [t_next, h_next] = (*m_stepper)(curr_t, curr_y, h, y_next);

                // Observer
                if (!m_observer->operator()(curr_t, Stepper::N, curr_y)) {
                    break;
                }

                // Update curr_t and y
                curr_t = t_next;
                std::copy(y_next, y_next + Stepper::N, curr_y);
            }
            std::copy(curr_y, curr_y + Stepper::N, a_yEnd);
            return a_yEnd[0];
        }

    private:
        Stepper *const m_stepper;
        Observer const *const m_observer;
    };
}

#endif //OVERALL_INTEGRATOR_H

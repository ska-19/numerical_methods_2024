#ifndef OBSERVER_H
#define OBSERVER_H

#include "iostream"
#include "algorithm"

namespace ADAI {

    //Implements application-specific logic: what to do with the solution
    class ObserverChecker {
    public:
        // Return true if continue / Return false if stop
        bool operator()(const double a_curr_t, int a_n, double const *a_curr_y) const {
            return a_curr_y[1] > 0;
        };
    };

    class ObserverPlotTrajectory {
    public:
        // Return true if continue / Return false if stop
        bool operator()(const double a_curr_t, int a_n, double const *a_curr_y) const {
            std::cout << "Step: " << a_n << "\nt:(" << a_curr_t << ") x:(" << a_curr_y[0] << ") y:(" << a_curr_y[1]
                      << ")\n";
            return a_curr_y[1] > 0;
        };
    };

    class ObserverPlotAllVector {
    public:
        // Return true if continue / Return false if stop
        bool operator()(const double a_curr_t, int a_n, double const *a_curr_y) const {
            for (int i = 0; i < a_n; ++i)std::cout << a_curr_y[i] << ' ';
            std::cout << '\n';
            return a_curr_y[1] > 0;
        };
    };

}

#endif //OBSERVER_H

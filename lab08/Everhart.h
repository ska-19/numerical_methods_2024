#ifndef EVERHART_H
#define EVERHART_H

#include <vector>
#include <functional>

namespace ADAI {

    // Template class Everhart for solving differential equations using Everhart's method
    template<typename T>
    class Everhart {
    public:
        // Constructor
        // dt: time step for integration
        // initial_conditions: initial state of the system
        // f: function representing the differential equations
        Everhart(T dt, const std::vector<T> &initial_conditions,
                 const std::function<std::vector<T>(const std::vector<T> &)> &f);

        // Method to perform the integration over time until t_end
        std::vector<std::vector<T>> integrate(T t_end);

    private:
        T dt;
        std::vector<T> state; // Current state of the system
        std::function<std::vector<T>(const std::vector<T> &)> f; // Function representing the differential equations
        std::vector<std::vector<T>> previous_states; // Vector to store previous states for multi-step method

        // Method to perform a single integration step using Everhart's method
        void step();
    }; // Template class Everhart for solving differential equations using Everhart's method

    template<typename T>
    Everhart<T>::Everhart(T dt, const std::vector<T> &initial_conditions,
                          const std::function<std::vector<T>(const std::vector<T> &)> &f)
            : dt(dt), state(initial_conditions), f(f) {
        previous_states.push_back(state);
    } // Constructor implementation

    template<typename T>
    void Everhart<T>::step() {
        std::vector<T> k1 = f(state);

        if (previous_states.size() < 2) {
            // For the first step, use Euler's method as a simple approximation
            std::vector<T> new_state(state.size());
            for (size_t i = 0; i < state.size(); ++i) {
                new_state[i] = state[i] + dt * k1[i];
            }
            previous_states.push_back(new_state);
            state = new_state;
        } else {
            // For subsequent steps, use Everhart's method
            // Calculate the derivative at the previous state
            std::vector<T> k0 = f(previous_states[previous_states.size() - 2]);
            std::vector<T> new_state(state.size());

            // Update the state using a linear combination of the current and previous derivatives
            for (size_t i = 0; i < state.size(); ++i) {
                new_state[i] = state[i] + dt * (1.5 * k1[i] - 0.5 * k0[i]);
            }

            // Store the new state in previous states
            previous_states.push_back(new_state);
            // Keep only the last two previous states
            if (previous_states.size() > 3) {
                previous_states.erase(previous_states.begin());
            }

            state = new_state;
        }
    } // Method to perform a single integration step using Everhart's method

    template<typename T>
    std::vector<std::vector<T>> Everhart<T>::integrate(T t_end) {
        std::vector<std::vector<T>> trajectory;
        size_t steps = static_cast<size_t>(t_end / dt);
        for (size_t i = 0; i < steps; ++i) {
            step();
            trajectory.push_back(state);
        }
        return trajectory;
    } // Method to perform the integration over time until t_end

}

#endif // EVERHART_H
#pragma once

#include "EulerSolution.hpp"

// EulerRunner takes a EulerSolution and runs it, providing the answer
// and run time.

class EulerRunner
{
public:
    explicit EulerRunner(const EulerSolution &solution,
                         int num_runs = default_num_runs)
        : solution(solution), input(solution.get_default_input()),
          num_runs_requested(num_runs), num_runs_completed(0),
          answer(0), avg_time_ns(0)
        {}
    ~EulerRunner() = default;

    // Assert that we never move, copy or assign runners
    EulerRunner(const EulerRunner &) = delete;
    EulerRunner & operator=(const EulerRunner &) = delete;
    EulerRunner(EulerRunner &&) = delete;

    static const int default_num_runs = 1;

    // Getters
    EulerIntType get_answer() const       { return answer; }
    double get_avg_time_ns() const        { return avg_time_ns; }
    EulerIntType get_input() const        { return input; }
    std::string get_avg_time_formatted() const;

    // Setters
    void set_input(EulerIntType value) { input = value; }

    void run();

    // Summary of run
    void print_summary() const;
    void print_csv() const;

private:
    const EulerSolution &solution;
    EulerIntType input;
    int num_runs_requested;
    int num_runs_completed;

    EulerIntType answer;
    long avg_time_ns;
};

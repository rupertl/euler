#pragma once

#include <functional>
#include <list>
#include <string>

// EulerSolution defines a function that solves a problem in Project Euler

using EulerIntType = long long;
using EulerFunction = std::function<EulerIntType(EulerIntType)>;

using EulerSolutionList = std::list<class EulerSolution>;

class EulerSolution
{
public:
    EulerSolution(int problem_id, const char *solution_name,
                  EulerFunction function, EulerIntType default_input)
        : problem_id(problem_id), solution_name(solution_name),
          function(function), default_input(default_input)
        {}
    ~EulerSolution() = default;

    // Assert that we will only move solutions, never copy or assign
    EulerSolution(const EulerSolution &) = delete;
    EulerSolution & operator=(const EulerSolution &) = delete;
    EulerSolution(EulerSolution &&) = default;

    // Getters
    int get_problem_id() const             { return problem_id; }
    std::string get_solution_name() const  { return solution_name; }
    EulerFunction get_function() const     { return function; }
    EulerIntType get_default_input() const { return default_input; }

private:
    const int problem_id;
    const std::string solution_name;
    const EulerFunction function;
    const EulerIntType default_input;
};

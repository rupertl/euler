#pragma once

#include <string>
#include <map>
#include <set>

#include "EulerSolution.hpp"

// EulerCommandLine defines how the program will operate given the
// command line.

class EulerCommandLine
{
public:
    explicit EulerCommandLine(int argc, const char **argv)
        :argc(argc), argv(argv)
        {}

    ~EulerCommandLine() = default;

    // Assert that we never move, copy or assign this object
    EulerCommandLine(const EulerCommandLine &) = delete;
    EulerCommandLine & operator=(const EulerCommandLine &) = delete;
    EulerCommandLine(EulerCommandLine &&) = delete;

    bool is_valid();

    bool do_usage() const;
    void print_usage() const;

    bool do_all_problems() const;
    int problem_id() const;

    bool do_all_solutions() const;
    const std::string &solution_name() const;

    // Returns true if user specified inputs and updated the list
    bool get_inputs(std::list<EulerIntType> &inputs) const;

    int runs() const;

    bool do_csv() const;

private:
    const int argc;
    const char **argv;
    std::set<std::string> flags;
    std::map<std::string, std::string> params;
};

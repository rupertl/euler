#include <algorithm>
#include <iostream>
#include <list>
#include <sstream>

#include "EulerCommandLine.hpp"
#include "EulerRunner.hpp"

using std::list;
using std::string;

long stol_or_zero(const string &input)
{
    // Convert input to a number. If input is non-numeric, return 0.
    try
    {
        return std::stol(input);
    }
    catch (...)
    {
        return 0;
    }
}

struct EulerCommandLineArg
{
    string name;
    enum {FLAG, PARAM} type;    // params take one argument, flags zero
};

static list<EulerCommandLineArg> argument_spec =
{
    {"--problem", EulerCommandLineArg::PARAM},
    {"--solution", EulerCommandLineArg::PARAM},
    {"--runs", EulerCommandLineArg::PARAM},
    {"--input", EulerCommandLineArg::PARAM},
    {"--help", EulerCommandLineArg::FLAG},
    {"--csv", EulerCommandLineArg::FLAG},
};

static string usage = R"(
euler [--problem PROBLEM_NUMBER] [--solution SOLUTION_NAME]
      [--runs NUMBER_OF_RUNS] [--input N[,N1,N2...]] [--csv] [--help]
)";

bool EulerCommandLine::is_valid()
{
    // Validate that the command line matches the spec.

    for (int i = 1; i < argc; i++)
    {
        string name{argv[i]};

        auto it = find_if(begin(argument_spec), end(argument_spec),
                          [&name](const EulerCommandLineArg &arg)
                          {
                              return arg.name == name;
                          });

        if (it == end(argument_spec))
        {
            std::cerr << "ERROR: Unknown argument " << name << std::endl;
            return false;
        }

        if (it->type == EulerCommandLineArg::FLAG)
        {
            flags.insert(it->name);
        }
        else
        {
            if (++i >= argc)
            {
                std::cerr << "ERROR: Missing value for argument " << name
                          << std::endl;
                return false;
            }

            params[it->name] = argv[i];
        }
    }

    return true;
}

bool EulerCommandLine::do_usage() const
{
    return flags.find("--help") != end(flags);
}

void EulerCommandLine::print_usage() const
{
    std::cerr << usage << std::endl;
}

bool EulerCommandLine::do_all_problems() const
{
    return params.find("--problem") == end(params);
}

int EulerCommandLine::problem_id() const
{
    return stol_or_zero(params.find("--problem")->second);
}

bool EulerCommandLine::do_all_solutions() const
{
    return params.find("--solution") == end(params);
}

const string & EulerCommandLine::solution_name() const
{
    return params.find("--solution")->second;
}

bool EulerCommandLine::get_inputs(std::list<EulerIntType> &inputs) const
{
    // If a comma separated list of inputs was provided, add to inputs list
    // Return true if anything was added

    auto found = params.find("--input");
    if (found == end(params))
    {
        return false;
    }
    else
    {
        // I could use regex - but not available yet on my version of gcc
        std::stringstream sstr(found->second);
        string item;
        while (std::getline(sstr, item, ','))
        {
            inputs.push_back(stol_or_zero(item));
        }
        return true;
    }
}

int EulerCommandLine::runs() const
{
    auto it = params.find("--runs");

    if (it != end(params))
    {
        int runs = stol_or_zero(it->second);
        if (runs != 0)
        {
            return runs;
        }
    }

    return EulerRunner::default_num_runs;
}

bool EulerCommandLine::do_csv() const
{
    return flags.find("--csv") != end(flags);
}

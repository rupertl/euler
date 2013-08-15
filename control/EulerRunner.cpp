#include <iostream>
#include <chrono>
#include <sstream>

#include "EulerRunner.hpp"

void EulerRunner::run()
{
    // Run the solution num_runs times and get the average time

    using std::chrono::steady_clock;
    using std::chrono::duration_cast;

    auto fn = solution.get_function();
    auto input = get_input();

    auto start = steady_clock::now();
    for (int i = 0; i < num_runs_requested; i++)
    {
        answer = fn(input);
    }
    auto end = steady_clock::now();

    auto duration = duration_cast<std::chrono::nanoseconds>
                        (end - start).count();

    avg_time_ns = duration / num_runs_requested;
    num_runs_completed = num_runs_requested;
}

void EulerRunner::print_summary() const
{
    if (num_runs_completed == 0)
    {
        std::cout << "Solution has not been run yet" << std::endl;
        return;
    }

    std::cout << "Problem: " << solution.get_problem_id()
              << " solution: " << solution.get_solution_name()
              << " input: " << get_input()
              << " answer: " << get_answer()
              << " time: " << get_avg_time_formatted()
              << std::endl;
}

void EulerRunner::print_csv() const
{
    static bool csv_header_printed = false;

    if (num_runs_completed == 0)
    {
        std::cout << "Solution has not been run yet" << std::endl;
        return;
    }

    if (! csv_header_printed)
    {
        std::cout << "problem,solution,input,runs,answer,time_ns"
                  << std::endl;
        csv_header_printed = true;
    }

    std::cout << solution.get_problem_id() << ","
              << solution.get_solution_name() << ","
              << get_input() << ","
              << num_runs_completed << ","
              << get_answer() << ","
              << get_avg_time_ns()
              << std::endl;
}


std::string EulerRunner::get_avg_time_formatted() const
{
    // Adjust the unit to make the number betweem one and one million
    constexpr long one_thousand = 1000;
    constexpr long one_million = one_thousand * one_thousand;
    constexpr long one_billion = one_thousand * one_million;

    std::stringstream ss;

    if (avg_time_ns > one_billion)
    {
        ss << avg_time_ns / one_million;
        ss << "ms";
    }
    else if (avg_time_ns > one_million)
    {
        ss << avg_time_ns / one_thousand;
        ss << "us";
    }
    else
    {
        ss << avg_time_ns;
        ss << "ns";
    }

    return ss.str();
}

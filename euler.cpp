#include <list>

#include "EulerSolution.hpp"
#include "EulerCommandLine.hpp"
#include "EulerRegistry.hpp"
#include "EulerRunner.hpp"

EulerSolutionList extract_solutions(const EulerCommandLine &cmd)
{
    using namespace EulerRegistry;

    if (cmd.do_all_problems())
    {
        return extract_all_problems_solutions();
    }
    else
    {
        int problem_id = cmd.problem_id();

        if (cmd.do_all_solutions())
        {
            return extract_solutions_for_problem(problem_id);
        }
        else
        {
            return extract_solution(problem_id, cmd.solution_name());
        }
    }
}

void run_solutions(const EulerCommandLine &cmd,
                   const EulerSolutionList &solutions)
{
    for (const auto &s : solutions)
    {
        std::list<EulerIntType> inputs;

        if (! cmd.get_inputs(inputs))
        {
            inputs.push_back(s.get_default_input());
        }

        EulerRunner r(s, cmd.runs());
        for (const auto &input : inputs)
        {
            r.set_input(input);
            r.run();
            cmd.do_csv() ? r.print_csv() : r.print_summary();
        }
    }
}

int main(int argc, const char **argv)
{
    EulerCommandLine cmd(argc, argv);

    if (! cmd.is_valid())
    {
        return 1;
    }

    if (cmd.do_usage())
    {
        cmd.print_usage();
        return 0;
    }

    EulerSolutionList solutions = extract_solutions(cmd);

    run_solutions(cmd, solutions);

    return 0;
}

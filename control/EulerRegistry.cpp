#include <algorithm>
#include <map>

#include "EulerRegistry.hpp"

namespace EulerRegistry {

using EulerRegistryImpl = std::map<int, EulerSolutionList>;

EulerRegistryImpl & get_registry()
{
    // Construct on first use
    static EulerRegistryImpl impl;

    return impl;
}

bool register_solution(EulerSolution &&solution)
{
    // Move the solution into the registry
    get_registry()[ solution.get_problem_id() ]
        .push_back(std::move(solution));

    return true;
}

EulerSolutionList extract_all_problems_solutions()
{
    EulerSolutionList solutions;

    for (auto &it : get_registry())
    {
        solutions.splice(end(solutions), it.second);
    }

    return solutions;
}

EulerSolutionList extract_solutions_for_problem(int problem_id)
{
    EulerSolutionList solutions;
    solutions.splice(end(solutions), get_registry()[problem_id]);
    return solutions;
}


EulerSolutionList extract_solution(int problem_id,
                                   const std::string &solution_name)
{
    EulerSolutionList solutions;
    EulerSolutionList all_solutions = extract_solutions_for_problem(problem_id);

    // Find first solution name that matches
    auto it = find_if(begin(all_solutions), end(all_solutions),
                      [&solution_name](const EulerSolution &arg)
                      {
                          return arg.get_solution_name().find(solution_name)
                                 != std::string::npos;
                      });

    if (it != end(all_solutions))
    {
        solutions.splice(end(solutions), all_solutions, it);
    }
    return solutions;
}

};

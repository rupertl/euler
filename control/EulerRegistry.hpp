#pragma once

#include <string>
#include "EulerSolution.hpp"

// EulerRegistry holds all EulerSolutions defined in the project

namespace EulerRegistry {

// To register a solution, call as follows
// static bool registered =
//    EulerRegistry::register_solution({1, "brute_force", brute_force, 1000});

bool register_solution(EulerSolution &&solution);

// The extract functions will move the solutions requested into the
// returned list.

EulerSolutionList extract_all_problems_solutions();
EulerSolutionList extract_solutions_for_problem(int problem_id);

// Abbreviations are ok, eg 'closed' will match 'closed_form'
EulerSolutionList extract_solution(int problem_id,
                                   const std::string &solution_name);

};

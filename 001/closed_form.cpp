#include "EulerRegistry.hpp"

// PROBLEM
// If we list all the natural numbers below 10 that are multiples of 3
// or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
// Find the sum of all the multiples of 3 or 5 below 1000.


// SOLUTION
// sum_3or5(n) = sum3(n) + sum5(n) - sum15(n)
// sum_k(n) = k * ((n-1)/k) * (1 + ((n-1)/k)) / 2
// 3 * ((10-1)/3) * (1 + ((10-1)/3)) / 2 = 3 * 3 * 4 / 2 = 18


// Return the sum of all numbers that are divisible by k between 1 and n
EulerIntType sum_k_n(EulerIntType k, EulerIntType n)
{
    return k * ((n-1)/k) * (1 + ((n-1)/k)) / 2;
}

EulerIntType closed_form(EulerIntType n)
{
    return sum_k_n(3, n) + sum_k_n(5, n) - sum_k_n(15, n);
}


static bool registered =
    EulerRegistry::register_solution({1, "closed_form", closed_form, 1000});

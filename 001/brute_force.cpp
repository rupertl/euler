#include "EulerRegistry.hpp"

// PROBLEM
// If we list all the natural numbers below 10 that are multiples of 3
// or 5, we get 3, 5, 6 and 9. The sum of these multiples is 23.
// Find the sum of all the multiples of 3 or 5 below 1000.


// SOLUTION
// Count up to 1000 and sum all numbers with mod 3 / mod 5 = 0


EulerIntType brute_force(EulerIntType n)
{
    EulerIntType sum = 0;

    for (EulerIntType i = 0; i < n; i++)
    {
        if (i % 3 == 0 || i % 5 == 0)
        {
            sum += i;
        }
    }

    return sum;
}


static bool registered =
    EulerRegistry::register_solution({1, "brute_force", brute_force, 1000});

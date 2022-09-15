#include <math.h>

#include <collisions.hh>

quadratic_solutions get_quadratic_solutions(double a, double b, double c) {
  // Obtain solutions to quadratic equation of the form ax^2 + bx + c = 0;
  // To keep this function generic and testable, note that the form
  // from the book with constants factored out is not used.
  // Note: If there is only one solution because both the positive and negative
  // discriminant evaluate to the same value, we set the positive discriminant
  // to that value.
  quadratic_solutions qs;
  double discriminant = b * b - 4 * a * c;
  if (discriminant > 0) {
    qs.solutions_n = 2;
    qs.sol1 = (-b - sqrt(discriminant)) / (2 * a);
    qs.sol2 = (-b + sqrt(discriminant)) / (2 * a);
  } else {
    qs.solutions_n = 0;
    qs.sol1 = 0.0;
    qs.sol2 = 0.0;
  }
  return qs;
}

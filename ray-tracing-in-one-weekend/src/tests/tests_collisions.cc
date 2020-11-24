#include "collisions.hh"
#include "gtest/gtest.h"

namespace {

// TODO: Use a > 1 in tests
TEST(Collisions, QuadraticNoSolutions) {
  // y = 1x^2 + 0x + 3 has no real-valued solutions
  quadratic_solutions qs = get_quadratic_solutions(1, 0, 3);
  ASSERT_EQ(qs.solutions_n, 0);
  ASSERT_EQ(qs.sol1, 0.0);
  ASSERT_EQ(qs.sol2, 0.0);
}

TEST(Collisions, QuadraticOneSolution) {
  // y = 1x^2 + 0x + 0 has exactly one solution for y = 0,
  // 0.
  quadratic_solutions qs = get_quadratic_solutions(1, 0, 0);
  ASSERT_EQ(qs.solutions_n, 1);
  ASSERT_EQ(qs.sol1, 0.0);
  ASSERT_EQ(qs.sol2, 0.0);
}

TEST(Collisions, QuadraticTwoSolutions) {
  // y = 1x^2 + 0x - 3 has two real-valued solutions for
  // y = 0: -sqrt(3) and sqrt(3)
  quadratic_solutions qs = get_quadratic_solutions(1, 0, -3);
  ASSERT_EQ(qs.solutions_n, 2);
  ASSERT_EQ(qs.sol1, sqrt(3.0));
  ASSERT_EQ(qs.sol2, -sqrt(3.0));
}

}  // namespace

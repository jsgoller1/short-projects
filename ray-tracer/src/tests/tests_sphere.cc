#include "gtest/gtest.h"
#include "sphere.hh"

#define MAX_DOUBLE std::numeric_limits<double>::max()

namespace {

TEST(Spheres, RayIntersection) {
  // A sphere centered at (0,0,0) with radius 5 will have two intersections
  // with a ray centered at (10,0,0) and direction (-10,0,0), so long
  // as its magnitude is 15 or greater.
  sphere s(vec3(0, 0, 0), 5);
  ray r(vec3(10, 0, 0), vec3(-10, 0, 0));
  hit_record hr;
  ASSERT_TRUE(s.hit(r, 0.0, MAX_DOUBLE, hr));
}

TEST(Spheres, NoRayIntersection) {
  // A sphere centered at (0,0,0) with radius 5 will have no intersections
  // with a ray centered at (10,0,0) and direction (20,0,0)
  sphere s(vec3(0, 0, 0), 5);
  ray r(vec3(10, 0, 0), vec3(20, 0, 0));
  hit_record hr;
  ASSERT_FALSE(s.hit(r, 0.0, MAX_DOUBLE, hr));
}

}  // namespace

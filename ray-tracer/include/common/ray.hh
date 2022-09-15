#pragma once

#include <vec3.hh>

class ray {
 public:
  vec3 A;
  vec3 B;

  ray() {}
  ray(const vec3 &a, const vec3 &b) {
    A = a;
    B = b;
  }
  vec3 origin() const;
  vec3 direction() const;
  vec3 point_at_parameter(double t) const;
};

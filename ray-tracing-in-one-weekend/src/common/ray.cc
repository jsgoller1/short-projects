#include <ray.hh>

vec3 ray::origin() const { return A; }
vec3 ray::direction() const { return B; }
vec3 ray::point_at_parameter(double t) const { return A + t * B; }

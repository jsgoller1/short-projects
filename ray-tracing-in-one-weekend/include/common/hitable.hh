#pragma once

#include <ray.hh>

class material;

struct hit_record {
  double magnitude;
  vec3 intersection_point;
  vec3 normal;
  material* mat_ptr;
};

class hitable {
 public:
  virtual bool hit(const ray& r, double t_min, double t_max,
                   hit_record& rec) const = 0;
  virtual ~hitable();
};

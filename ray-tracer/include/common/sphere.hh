#pragma once

#include <hitable.hh>
#include <material.hh>

class sphere : public hitable {
 public:
  sphere() {}
  ~sphere();
  sphere(vec3 cen, double r, material* m) : center(cen), radius(r), mat(m) {}

  vec3 center;
  double radius;
  material* mat;

  virtual bool hit(const ray& r, double t_min, double t_max,
                   hit_record& rec) const;
};

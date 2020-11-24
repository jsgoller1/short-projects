#pragma once

#include <hitable.hh>

class hitable_list : public hitable {
 public:
  hitable_list() {}
  hitable_list(hitable** l, int n);

  hitable** list;
  int list_size;

  virtual bool hit(const ray& r, double t_min, double t_max,
                   hit_record& rec) const;
};

#include <hitable_list.hh>

hitable_list::hitable_list(hitable** l, int n) {
  list = l;
  list_size = n;
}

bool hitable_list::hit(const ray& r, double t_min, double t_max,
                       hit_record& rec) const {
  // Test intersection of a ray with each item in the scene;
  // we only want the closest one (in case the ray intersects
  // multiple things in the scene)
  hit_record temp_rec;
  bool hit_anything = false;
  double closest_so_far = t_max;
  for (int i = 0; i < list_size; i++) {
    if (list[i]->hit(r, t_min, closest_so_far, temp_rec)) {
      hit_anything = true;
      closest_so_far = temp_rec.magnitude;
      rec = temp_rec;
    }
  }
  return hit_anything;
}

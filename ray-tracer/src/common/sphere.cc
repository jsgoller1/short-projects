#include <cassert>
#include <collisions.hh>
#include <ray.hh>
#include <sphere.hh>

sphere::~sphere() { delete mat; }

bool sphere::hit(const ray& r, double t_min, double t_max,
                 hit_record& record) const {
  // Execute quadratic formula for roots test; for the full derivation of a
  // quadratic equation via dot products from the equations of a sphere and a
  // ray, see:
  // http://bugfree.dk/blog/2018/09/03/ray-tracing-computing-ray-sphere-intersections

  // oc is a hack to avoid re-computing the same part of a and c.
  vec3 oc = r.origin() - center;
  double a = dot(r.direction(), r.direction());
  double b = 2.0 * dot(oc, r.direction());
  double c = dot(oc, oc) - radius * radius;

  // TODO: Do we want to return both points?
  quadratic_solutions qs = get_quadratic_solutions(a, b, c);
  if (qs.solutions_n != 2) {
    return false;
  }

  bool valid_2 = t_min < qs.sol2 && qs.sol2 < t_max;
  bool valid_1 = t_min < qs.sol1 && qs.sol1 < t_max;

  if (valid_1 && !(valid_2)) {
    record.magnitude = qs.sol1;
  } else if (valid_2 && !(valid_1)) {
    record.magnitude = qs.sol2;
  } else if (valid_2 && valid_1) {
    record.magnitude = qs.sol1;  // std::min(qs.sol2, qs.sol1);
  } else {
    return false;
  }

  record.intersection_point = r.point_at_parameter(record.magnitude);
  record.normal = (record.intersection_point - center) / radius;
  record.mat_ptr = mat;
  assert(-1 <= record.normal.x() && record.normal.x() <= 1);
  assert(-1 <= record.normal.y() && record.normal.y() <= 1);
  assert(-1 <= record.normal.z() && record.normal.z() <= 1);
  return true;
}

#include "camera.hh"

ray camera::get_ray(double u, double v) {
  return ray(origin,
             lower_left_corner + (u * horizontal) + (v * vertical) - origin);
}

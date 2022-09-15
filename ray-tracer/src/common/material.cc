#include <material.hh>
#include <vec3.hh>

material::~material() {}

// input ray isn't used for lambertian scattering; instead, we just pick
// a random point on the sphere tangent to the intersection point and reflect
// there.
#pragma clang diagnostic ignored "-Wunused-parameter"
bool lambertian::scatter(const ray& r_in, const hit_record& rec,
                         vec3& attenuation, ray& scattered) const {
  vec3 target = rec.intersection_point + rec.normal + random_in_unit_sphere();
  scattered = ray(rec.intersection_point, target - rec.intersection_point);
  attenuation = albedo;
  return true;
}

lambertian::~lambertian() {}

bool metal::scatter(const ray& r_in, const hit_record& rec, vec3& attenuation,
                    ray& scattered) const {
  vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
  scattered = ray(rec.intersection_point, reflected);
  attenuation = albedo;
  return (dot(scattered.direction(), rec.normal) > 0);
}

metal::~metal() {}

bool dielectric::scatter(const ray& r_in, const hit_record& rec,
                         vec3& attenuation, ray& scattered) const {
  vec3 outward_normal;
  vec3 reflected = reflect(r_in.direction(), rec.normal);
  double ni_over_nt;
  attenuation = vec3(1.0, 1.0, 1.0);
  vec3 refracted;
  double reflect_prob;
  double cosine;
  if (dot(r_in.direction(), rec.normal) > 0) {
    outward_normal = -rec.normal;
    ni_over_nt = refractive_index;
    cosine = refractive_index * dot(r_in.direction(), rec.normal) /
             r_in.direction().length();
  } else {
    outward_normal = rec.normal;
    ni_over_nt = 1.0 / refractive_index;
    cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
  }

  if (refract(r_in.direction(), outward_normal, ni_over_nt, refracted)) {
    reflect_prob = schlick_approximation(cosine);
  } else {
    scattered = ray(rec.intersection_point, reflected);
    reflect_prob = 1.0;
  }
  if (drand48() < reflect_prob) {
    scattered = ray(rec.intersection_point, reflected);
  } else {
    scattered = ray(rec.intersection_point, refracted);
  }
  return true;
}

double dielectric::schlick_approximation(double cosine) const {
  double r0 = (1 - refractive_index) / (1 + refractive_index);
  r0 = r0 * r0;
  return r0 + (1 - r0) * pow((1 - cosine), 5);
}

dielectric::~dielectric() {}

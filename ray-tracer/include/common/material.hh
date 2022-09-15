#pragma once

#include <hitable.hh>
#include <ray.hh>

class material {
 public:
  virtual bool scatter(const ray& r_in, const hit_record& rec,
                       vec3& attenuation, ray& scattered) const = 0;
  virtual ~material();
};

class lambertian : public material {
 public:
  lambertian(const vec3& a) : albedo(a) {}

  virtual bool scatter(const ray& r_in, const hit_record& rec,
                       vec3& attenuation, ray& scattered) const;

  ~lambertian();
  vec3 albedo;
};

class metal : public material {
 public:
  metal(const vec3& a) : albedo(a) {}
  virtual bool scatter(const ray& r_in, const hit_record& rec,
                       vec3& attenuation, ray& scattered) const;

  ~metal();
  vec3 albedo;
};

class dielectric : public material {
 public:
  dielectric(double ri) : refractive_index(ri) {}
  virtual bool scatter(const ray& r_in, const hit_record& rec,
                       vec3& attenuation, ray& scattered) const;
  double schlick_approximation(double cosine) const;
  ~dielectric();
  double refractive_index;
};

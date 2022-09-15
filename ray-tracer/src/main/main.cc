#include <cassert>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <limits>

#include <camera.hh>
#include <hitable_list.hh>
#include <material.hh>
#include <ray.hh>
#include <sphere.hh>
#include <vec3.hh>

#define MAX_RGB_VAL double(255.99)
#define MAX_DOUBLE std::numeric_limits<double>::max()

#define IMAGE_PATH "execs/photo.ppm"
#define IMAGE_WIDTH 2000
#define IMAGE_HEIGHT 1000
#define AA_SAMPLE_COUNT 100

inline vec3 surface_normal_color(const ray& r, hitable_list* world) {
  /*
  If we hit an object in the scene, set pixel color based on the surface normal
  at the point of intersection. Otherwise, get the background color via a lerped
  blue sky.
  */

  hit_record rec;
  if (world->hit(r, 0.0, MAX_DOUBLE, rec)) {
    return 0.5 *
           vec3(rec.normal.x() + 1, rec.normal.y() + 1, rec.normal.z() + 1);
  } else {
    /*
    Lineraly blend from blue to white based on y coordinate via interpolation
    (lerp). lerp: blended_value = (1-t)*start_value +t*end_value,
    where 0 < t < 1.
    */
    vec3 unit_direction = unit_vector(r.direction());
    double t = 0.5 * (unit_direction.y() + 1.0);
    return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
  }
}

inline vec3 material_color(const ray& r, hitable_list* world, int depth,
                           bool sky_lerp) {
  // When a ray intersects an object, use information about the object's
  // material to determine pixel color. If no intersection occurs, use a generic
  // lerped blue sky background.
  hit_record rec;
  if (world->hit(r, 0.001, MAX_RGB_VAL, rec)) {
    ray scattered;
    vec3 attenuation;
    if (depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered)) {
      return attenuation *
             material_color(scattered, world, depth + 1, sky_lerp);
    } else {
      return vec3(0, 0, 0);
    }
  } else {
    if (sky_lerp) {
      // Blue sky background lerp
      vec3 unit_direction = unit_vector(r.direction());
      double t = 0.5 * (unit_direction.y() + 1.0);
      return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
    } else {
      // Constant color background if we disable lerping.
      return vec3(0.5, 0.7, 1.0);
    }
  }
}

inline vec3 constant_color(const ray& r, hitable_list* world) {
  // Color every pixel the same color; useful for testing.
  (void)r;
  (void)world;
  return vec3(0.0, 0.0, 0.0);
}

int main() {
  // Set up image for writing pixel data
  std::fstream image(IMAGE_PATH,
                     std::fstream::in | std::fstream::out | std::fstream::app);
  if (image.is_open()) {
    image << "P3\n" << IMAGE_WIDTH << " " << IMAGE_HEIGHT << "\n255\n";

    // Create world
    // TODO: have redemption read this from a JSON file
    camera cam;
    hitable* list[6];
    list[0] =
        new sphere(vec3(0, 0, -1), .5, new lambertian(vec3(0.1, 0.2, 0.5)));
    list[1] = new sphere(vec3(0, -100.5, -1), 100,
                         new lambertian(vec3(0.8, 0.8, 0.0)));
    list[2] = new sphere(vec3(1, 0.0, -1), .5, new metal(vec3(0.8, 0.6, 0.2)));
    list[3] = new sphere(vec3(-.5, -.25, -.25), .25, new dielectric(1.5));
    list[4] = new sphere(vec3(.45, -.25, -.25), .25, new dielectric(1.5));
    list[5] = new sphere(vec3(.45, -.25, -.25), -0.24, new dielectric(1.5));

    hitable_list* world = new hitable_list(list, 6);

    // Use current time as seed for RNG
    srand48(std::time(nullptr));

    // Write pixel data
    for (int curr_height = IMAGE_HEIGHT - 1; curr_height >= 0; curr_height--) {
      for (int curr_width = 0; curr_width < IMAGE_WIDTH; curr_width++) {
        vec3 col(0, 0, 0);
        for (int sample_n = 0; sample_n < AA_SAMPLE_COUNT; sample_n++) {
          double u = (double(curr_width) + drand48()) / double(IMAGE_WIDTH);
          double v = (double(curr_height) + drand48()) / double(IMAGE_HEIGHT);
          ray r = cam.get_ray(u, v);
          col += material_color(r, world, 0, true);
        }

        // Average for antialiasing
        col /= double(AA_SAMPLE_COUNT);

        // Gamma-correct pixel-values.
        // TODO: In some cases, the sqrt of the z-value has
        // been -nan, and I can't figure out why but then it
        // stopped happening
        col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
        assert(!(isnan(col[0])) && !(isnan(col[1])) && !(isnan(col[2])));

        int ir = int(MAX_RGB_VAL * col[0]);
        assert(0 <= ir && ir <= MAX_RGB_VAL);
        int ig = int(MAX_RGB_VAL * col[1]);
        assert(0 <= ig && ig <= MAX_RGB_VAL);
        int ib = int(MAX_RGB_VAL * col[2]);
        assert(0 <= ib && ib <= MAX_RGB_VAL);

        image << ir << " " << ig << " " << ib << "\n";
      }
    }
    for (auto s : list) {
      delete s;
    }
    delete world;
    image.close();
  } else {
    std::cout << "Couldn't open file" << IMAGE_PATH << "!" << std::endl;
  }
  return 0;
}

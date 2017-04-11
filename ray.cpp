#include "ray.h"

Ray::Ray() : origin(Vec3d()), direction(Vec3d(1.0, 0.0, 0.0)) {}
Ray::Ray(const Vec3d& o, const Vec3d& d) : origin(o), direction(d) {}



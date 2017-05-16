#include "brdf.h"

BRDF::BRDF(){}

BRDF::~BRDF(){}

Color BRDF::f(const Intersect& inter, const Vec3d& wi, const Vec3d& wo) const { return BLACK; }
Color BRDF::sample_f(const Intersect& inter, Vec3d& wi, const Vec3d& wo) const { return BLACK; }
Color BRDF::rho(const Intersect& inter, const Vec3d& wo) const { return BLACK; }

#include "lambertian.h"
#include "globals.h"

Lambertian::Lambertian()
{
    cd = BLUE;
    kd = 0.65;
}

Lambertian::~Lambertian()
{
    //dtor
}

Color Lambertian::f(const Intersect& inter, const Vec3d& wi, const Vec3d& wo) const
{

    return kd*cd*invPI;
}
Color Lambertian::sample_f(const Intersect& inter, Vec3d& wi, const Vec3d& wo) const
{
    return Color(0.0);
}
Color Lambertian::rho(const Intersect& inter, const Vec3d& wo) const
{
    return kd*cd;
}


void Lambertian::setCd(Color c) { cd = c; }
void Lambertian::setKd(float k) { kd = k; }

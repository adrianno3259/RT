#include "glossyspecular.h"
#include <cmath>

GlossySpecular::GlossySpecular()
{
    ks = 0.25;
    e = 30;
}

GlossySpecular::~GlossySpecular()
{
    //dtor
}


Color GlossySpecular::f(const Intersect& inter, const Vec3d& wi, const Vec3d& wo) const
{
    Color L = Color(0.0);

    float nDotWi = inter.normal * wi;
    Vec3d r = -wi + 2.0*inter.normal*nDotWi;
    float rDotWo = r * wo;

    if(rDotWo > 0.0)
        L = ks * pow(rDotWo, e);
    return L;
}
Color GlossySpecular::sample_f(const Intersect& inter, Vec3d& wi, const Vec3d& wo) const
{
    return BLACK;
}
Color GlossySpecular::rho(const Intersect& inter, const Vec3d& wo) const
{
    return BLACK;
}

void GlossySpecular::setKs(float k) { ks = k; }
void GlossySpecular::setExp(float e){ e = e; }

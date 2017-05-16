#include "perfectspecular.h"
#include <iostream>

PerfectSpecular::PerfectSpecular()
{
    kr = 0.75;
    cr = Color(1.0);
}

PerfectSpecular::~PerfectSpecular()
{
    //dtor
}

Color PerfectSpecular::sample_f(const Intersect& inter, Vec3d& wi, const Vec3d& wo) const
{
    float nDotWo = inter.normal * wo;
    //printVec(inter.normal); printVec(wo);
    //std::cout<<"nDotWi = "<<nDotWo<<std::endl;
    wi = -wo + (2.0 * (inter.normal * nDotWo));
    return (kr * cr) / (inter.normal * wi);
}

void PerfectSpecular::setKr(float k) { kr = k; }
void PerfectSpecular::setCr(Color c) { cr = c; }

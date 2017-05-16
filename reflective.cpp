#include "reflective.h"

Reflective::Reflective(const Color& c) : Phong(c)
{
    reflective_brdf = new PerfectSpecular();
}

Reflective::~Reflective()
{
    //dtor
}

Color Reflective::shade(const Scene& sc, Intersect& it) const
{

    Color L = Phong::shade(sc, it);
    Vec3d wo = -it.r.direction;
    Vec3d wi;
    Color fr = (reflective_brdf->sample_f(it, wi, wo));

    Ray reflected = Ray(it.hitPoint +(K_EPSILON*it.normal), wi);

    L+= fr * sc.traceRayWhitted(reflected, it.depth+1) * (it.normal*wi);
    return L;
}


void Reflective::setKr(const float k) { reflective_brdf->setKr(k); }
void Reflective::setCr(const Color& c) { reflective_brdf->setCr(c); }

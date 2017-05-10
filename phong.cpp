#include "phong.h"
#include <cmath>

Phong::Phong(const Color& col) : Material(col)
{
    //ctor
}

Phong::~Phong()
{
    //dtor
}

Color Phong::shade(const Scene& sc, Intersect& it)
{
    Vec3d wo = -it.r.direction;
    Color L = Color(0.0);
    for(unsigned int i = 0; i< sc.lights.size(); i++)
    {
        Color tmp;
        Vec3d wi = sc.lights[i]->getDirection(it.hitPoint); // Ângulo de incidência
        float ldDotN = (wi*it.normal);
        Vec3d r = -wi + 2.0*it.normal*ldDotN;
        float rDotWo = r * wo;
        float shadow = sc.lightHitsPoint(i, it, MAX_DISTANCE);

        if(rDotWo > 0.0) tmp = 0.5 * pow(rDotWo, 1000);

        if(ldDotN>0 && shadow <1.0)
        {
            L += ldDotN*(sc.lights[i]->getL())*c;
            L+=tmp;
        }
    }
    return L;
}

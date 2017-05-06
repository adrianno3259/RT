#include "matte.h"

Matte::Matte(const Color& col) : Material(col)
{
    //ctor
}

Matte::~Matte()
{
    //dtor
}

Color Matte::shade(const Scene& sc, Intersect& it)
{

    Color L = Color(0.0);
    for(unsigned int i = 0; i< sc.lights.size(); i++)
    {
        float ld_dot_n = (sc.lights[i]->getDirection(it.hitPoint)*it.normal);
        float shadow = sc.lightHitsPoint(i, it, MAX_DISTANCE);
        if(ld_dot_n>0 && shadow <1.0)
        {
            L += ld_dot_n*(sc.lights[i]->getL())*c;
        }
    }
    return L;
}

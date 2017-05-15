#include "phong.h"
#include <cmath>

Phong::Phong(const Color& col) : Material(col)
{
    diffuse_brdf = new Lambertian();
    specular_brdf = new GlossySpecular();
    diffuse_brdf->setCd(col);
}

Phong::~Phong()
{
    //dtor
}

Color Phong::shade(const Scene& sc, Intersect& it) const
{
    Color L = Color(0.0);
    // Adicionado com BRDF -------|
    Vec3d wo = -it.r.direction;//-|
    //----------------------------|
    for(unsigned int i = 0; i< sc.lights.size(); i++)
    {
        Vec3d wi = sc.lights[i]->getDirection(it.hitPoint);
        float ld_dot_n = (wi*it.normal);
        float shadow = sc.lightHitsPoint(i, it, MAX_DISTANCE);
        if(ld_dot_n>0 && shadow <1.0)
        {

            L += ld_dot_n*(sc.lights[i]->getL())*(diffuse_brdf->f(it, wi, wo) + specular_brdf->f(it, wi, wo));

        }
    }

    return L;

}

void Phong::setKd(const float k){ diffuse_brdf->setKd(k);}
void Phong::setKs(const float k){ specular_brdf->setKs(k); }
void Phong::setExp(const float exp){ specular_brdf->setExp(exp); }
void Phong::setCd(const Color& c){ diffuse_brdf->setCd(c); }

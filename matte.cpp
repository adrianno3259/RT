#include "matte.h"
#include <iostream>

Matte::Matte(const Color& col) : Material(col)
{
    diffuse_brdf = new Lambertian();
    diffuse_brdf->setCd(col);
    diffuse_brdf->setKd(1.0);
}

Matte::~Matte()
{
    //dtor
}

Color Matte::shade(const Scene& sc, Intersect& it) const
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
            // Alterado para BRDF --------------------|
            //L += ld_dot_n*(sc.lights[i]->getL())*c; |
            //----------------------------------------|
            //std::cout<<"teste "<<diffuse_brdf->f(it, wo, wi).r<<std::endl;
            L += ld_dot_n*(sc.lights[i]->getL())*diffuse_brdf->f(it, wi, wo);
            //std::cout<<"teste depois"<<std::endl;
        }
    }
    return L;
}


void Matte::setKa(const float k)
{

}
void Matte::setKd(const float k)
{
    diffuse_brdf->setKd(k);
}
void Matte::setCd(const Color& c)
{
    diffuse_brdf->setCd(c);
}

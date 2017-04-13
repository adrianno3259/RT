#include "material.h"
#include "globals.h"

Material::Material(const Color& col) : c(col){}

Color Material::shade(const Scene& sc, Intersect& it)
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


float Material::checkShadow(const Scene& sc, Light* l, const Intersect& it, float dist) const
{
    Vec3d lv = (l->position - it.hitPoint);
    printVec(lv);
    float d = lv.length();
    printVar(d);
    lv.normalize();

    Vec3d k = it.hitPoint +(it.normal*(0.01));
    //printVec(it.hitPoint); printVec(k);
    Ray r = Ray(k, lv);
    Intersect it_s = sc.hitObject(r);
 /*    //it_s.hit = false;
    printVec((l->position));
    printVec(it_s.hitPoint);    printVar(d);
    printVar(it_s.hit); printVar(it_s.t); printVar(d); printVar(it_s.t < dist);
    printVar(it_s.t > d); printVar((!it_s.hit ||it_s.t > d)); printVar(it_s.t < dist );
  std::cout<< "------------------- Shadow ----------------------"<<std::endl;

    printVar(d);

    printInters(it_s);*/
    if((!it_s.hit ||it_s.t > d) && it_s.t < dist ) return 0.0;
    else return 1.0;
}

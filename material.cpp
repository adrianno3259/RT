#include "material.h"


Material::Material(const Color& col) : c(col){}

Color Material::shade(const Scene& sc, Intersect& it)
{

    Color L = Color(0.0);

    for(int i = 0; i< sc.lights.size(); i++)
    {
            float ld_dot_n = (sc.lights[i]->getDirection(it.hitPoint)*it.normal);
            //printVar(i);
            //printLight((*sc.lights[i]));
            //printVec(it.hitPoint);
            //printVec(it.normal);
            //printVec(sc.lights[i]->getDirection(it.hitPoint));
            //printVar(ld_dot_n);

            //float shadow = checkShadow(sc, sc.lights[i], it, MAX_DISTANCE);
            //printVar(shadow);

        if(ld_dot_n>0)// && shadow > 0)
        {
            L += ld_dot_n*(sc.lights[i]->getL())*c;
        }
    }
    //printCol(L);
    return L;
}


float Material::checkShadow(const Scene& sc, Light* l, const Intersect& it, float dist) const
{


    Vec3d lv = (l->position - it.hitPoint);
    float d = lv.length();
    lv.normalize();

    Vec3d k = it.hitPoint +(it.normal*K_EPSILON);

    Ray r = Ray(k, lv);
    Intersect it_s = sc.hitObject(r);
    /*std::cout<< "------------------- Shadow ----------------------"<<std::endl;

    printVar(d);
    printVar(dist);
    printInters(it_s);*/
    if((!it_s.hit ||it_s.t > d) && it_s.t < dist ) return 1.0;
    else return 0.0;
}

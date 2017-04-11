#include "scene.h"
#include <cmath>

Scene::Scene()
{
    objects = std::vector<Object*>();
    lights = std::vector<Light*>();
    bg = Color(0.5);
}

Intersect Scene::hitObject(const Ray& ray) const
{
    Intersect i, ret;
    float t = INFINITY;
    i.hit = false;
    i.t = 0.0;

    //if(PIX_X%P_SKIP==0 && PIX_Y%P_SKIP ==0)
    //    QP(\nObjects -- \n);

    for(int o = 0; o < objects.size(); o++)
    {
        i = objects[o]->hit(ray);

        //printObject((*objects[o]));
        //printInters(i);


        if(i.hit)
        {
            if(i.t < t)
            {
                ret = i;
                t = i.t;
            }
        }
    }

    if(!ret.hit) ret.c = bg; //printCol(ret.c);}

    return ret;
}

void Scene::addObject(Object* o)
{
    objects.push_back(o);
}

void Scene::addLight(Light* l)
{
    lights.push_back(l);
}

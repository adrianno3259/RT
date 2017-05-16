#include "scene.h"
#include <cmath>
#include<iostream>
#include "material.h"

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
    i.entering = false;
    i.t = 0.0;
    ret.hit = false;
    ret.entering = false;
    ret.t = 0.0;

    for(int o = 0; o < objects.size(); o++)
    {

        i = objects[o]->hit(ray);
        if(i.hit)
        {
            if(i.t < t)
            {
                ret = i;
                t = i.t;
            }
        }
    }

    if(!ret.hit) ret.c = bg;
    return ret;
}

bool Scene::lightHitsPoint(int lightId, const Intersect& it, float maxDist) const
{
    Intersect i;
    Light* li = lights[lightId];
    Vec3d lightVector = (li->position - it.hitPoint);
    float distToLight = lightVector.length();
    lightVector.normalize();

    Vec3d origin = it.hitPoint +(it.normal*K_EPSILON);
    Ray r = Ray(origin, lightVector);

    i = hitObject(r);
    if(!i.hit || i.t > distToLight)
        if(distToLight < maxDist)
            return 0.0;
    else return 1.0;

}

void Scene::addObject(Object* o)
{
    objects.push_back(o);
}

void Scene::addLight(Light* l)
{
    lights.push_back(l);
}

Color Scene::traceRay(const Ray& ray) const
{
    Intersect intersect = hitObject(ray);
    Color L = Color(0.0);

    if(intersect.hit)
    {
        intersect.r = ray;
        L = intersect.m->shade((*this), intersect);
    }
    else
        L = intersect.c;

    return L;

}

Color Scene::traceRayWhitted(const Ray& ray, const int depth) const
{
    //std::cout<<"depth = "<<depth<<std::endl;
    if(depth > MAX_DEPTH)
        return BLACK;
    else
    {
        Intersect it = hitObject(ray);
        if(it.hit)
        {
            it.depth = depth;
            it.r = ray;
            return it.m->shade((*this), it);

        }
        else
            return it.c;
    }
}

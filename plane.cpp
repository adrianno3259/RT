#include "plane.h"
#include <iostream>
Plane::Plane() : point(Vec3d(0,0,-10)), normal(Vec3d(0,0,1))
{

}

Plane::~Plane()
{
    //dtor
}

Plane::Plane(const Vec3d& p, const Vec3d& n) : point(p), normal(n){}

Intersect Plane::hit(const Ray& r) const
{
    Intersect i;
    i.r = r;
    i.hit = false;

    float vd = (r.direction * normal);
    //printVec(r.direction);
    //printVec(normal);
    //std::cout<<"try hit  --- "<<vd<<std::endl;
    if(vd != 0)
    {
        //std::cout<<"vd != 0"<<std::endl;
        Vec3d tmp = (point - r.origin);
        float v0 = tmp * normal;
        float t =  v0/vd;

        if(t > K_EPSILON)
        {
//            std::cout<<"hitPlane"<<std::endl;
            i.hit = true;
            i.t = t;

            i.m = m;
            i.hitPoint = r.rayPoint(t);
            i.obj = (Object*)this;
            i.r = r;
            if(vd<0){ i.normal = normal; i.entering = true;}
            else{ i.normal = -normal; i.entering = false;}
        }
    }
    return i;
}

void Plane::printData(void) const
{
    printVec(point);
    printVec(normal);
}

Vec3d Plane::getNormal(const Vec3d& P) const
{
    return normal;
}

std::vector<Intersect> Plane::hitList(const Ray& r) const
{
    std::vector<Intersect> it;
    float vd = (r.direction * normal);
    if(vd != 0)
    {
        Vec3d tmp = (point - r.origin);
        float v0 = tmp * normal;
        float t =  v0/vd;

        if(t < K_EPSILON)
        {
            Intersect i;
            i.hit = true;
            i.t = t;

            i.m = m;
            i.hitPoint = r.rayPoint(t);
            i.obj = (Object*)this;
            i.r = r;

            i.entering = true;
            i.normal = normal;
            it.push_back(i);

            i.normal = -normal;
            i.entering = false;
            it.push_back(i);
        }
    }
    return it;
}

BoundingBox Plane::getBoudingBox(){ return BoundingBox();}

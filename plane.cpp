#include "plane.h"

#include <cmath>

Plane::Plane(const Vec3d& p, const Vec3d& n) : Object(), point(p), normal(n) {}
Plane::Plane() : Object(), point(Vec3d(1.0, 0.0, 0.0)), normal(Vec3d(0.0, 0.0, 1.0)) {}
Plane::~Plane(){}

Intersect Plane::hit(const Ray& ray) const
{
    Intersect i;
    i.hit = false;
    i.entering = false;

    //int D = normal * (-point);
    float vd = normal*ray.direction;
    //printVec(normal*ray); //printVec(ray.direction);
    //printVar((normal.x*ray.direction.x + normal.y*ray.direction.y+normal.z*ray.direction.z));
    if(vd != 0)
    {
        Vec3d tmp = point - ray.origin;
        int v0 = tmp*normal;
        int t = v0/vd;
        if(t>K_EPSILON)
        {
            i.hit = true;
            i.entering = true;
            i.obj = (Object*)(this);
            i.m = this->m;
            i.t = t;
            i.hitPoint = ray.rayPoint(i.t);
            //if(vd<0)
                i.normal = normal;
            //else
            //    i.normal = -normal;
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

#include "object.h"

Object::Object()
{
    //ctor
}

Intersect Object::hit(const Ray& r) const
{
    Intersect i;
    i.hit = false;
    return i;
}
void Object::printData(void) const{}
Vec3d Object::getNormal(const Vec3d& P) const{ return Vec3d();}
//float Object::shadowHit(const Scene& sc, Light* l, const Intersect& it, float maxDist) const{return 0.0;}

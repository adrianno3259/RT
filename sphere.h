#ifndef SPHERE_H
#define SPHERE_H

#include "object.h"


class Sphere : public Object
{
public:
    float radius;
    Vec3d center;
    Sphere();
    Sphere(float r);
    Sphere(const Vec3d& c, float r);
    virtual Intersect hit(const Ray& r) const;
    virtual void printData(void) const;
    virtual Vec3d getNormal(const Vec3d& P) const;
    virtual std::vector<Intersect> hitList(const Ray& ray) const;
};
#endif // SPHERE_H

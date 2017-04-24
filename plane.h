#ifndef PLANE_H
#define PLANE_H

#include "object.h"

class Plane : public Object
{
    public:
        Vec3d point;
        Vec3d normal;
        Plane();
        Plane(const Vec3d& p, const Vec3d& n);
        virtual ~Plane();
        virtual Intersect hit(const Ray& r) const ;
        virtual void printData(void) const;
        virtual Vec3d getNormal(const Vec3d& P) const ;
        virtual std::vector<Intersect> hitList(const Ray& ray) const;
    protected:
    private:
};

#endif // PLANE_H

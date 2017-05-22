#ifndef BOX_H
#define BOX_H

#include "object.h"


class Box : public Object
{
    public:
        Vec3d minPoint;
        Vec3d maxPoint;
        Box(const Vec3d& minp, const Vec3d& maxp);
        Box();
        virtual ~Box();
        virtual Intersect hit(const Ray& r) const ;
        virtual void printData(void) const;
        virtual Vec3d getNormal(const Vec3d& P) const ;
        virtual Vec3d getNormal(const int face) const;
        virtual std::vector<Intersect> hitList(const Ray& ray) const;
        virtual BoundingBox getBoudingBox();
    protected:
    private:
};

#endif // BOX_H

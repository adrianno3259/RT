#ifndef BOUNDINGBOX_H
#define BOUNDINGBOX_H

#include "ray.h"
#include "vec3.h"
#include "globals.h"


class BoundingBox
{
    public:
        BoundingBox(const Vec3d& minp, const Vec3d& maxp);
        BoundingBox();
        virtual ~BoundingBox();
        bool hit(const Ray& ray) const;
        bool hit(const Ray& ray, float& tf) const;
        bool hit(const Ray& ray, float& tf, float& ti) const;
        Vec3d getMinPoint() const;
        Vec3d getMaxPoint() const;
        void setMinPoint(const Vec3d& v);
        void setMaxPoint(const Vec3d& v);
        bool inside (const Ray& r) const;
    private:
        Vec3d maxPoint;
        Vec3d minPoint;
};




#endif // BOUNDINGBOX_H

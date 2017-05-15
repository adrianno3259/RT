#ifndef BRDF_H
#define BRDF_H

#include "color.h"
#include "vec3.h"
#include "intersect.h"

class BRDF
{
    public:
        BRDF();
        virtual ~BRDF();
        virtual Color f(const Intersect& inter, const Vec3d& wi, const Vec3d& wo) const;
        virtual Color sample_f(const Intersect& inter, Vec3d& wi, const Vec3d& wo) const;
        virtual Color rho(const Intersect& inter, const Vec3d& wo) const;
    protected:

    private:
};

#endif // BRDF_H

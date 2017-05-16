#ifndef LAMBERTIAN_H
#define LAMBERTIAN_H

#include "brdf.h"

class Lambertian : public BRDF
{
    public:
        Lambertian();
        virtual ~Lambertian();
        virtual Color f(const Intersect& inter, const Vec3d& wi, const Vec3d& wo) const;
        virtual Color sample_f(const Intersect& inter, Vec3d& wi, const Vec3d& wo) const;
        virtual Color rho(const Intersect& inter, const Vec3d& wo) const;
        void setCd(Color c);
        void setKd(float k);
    protected:
        float kd; // coeficiente de reflexão difusa
        Color cd; //cor difusa
    private:
};

#endif // LAMBERTIAN_H

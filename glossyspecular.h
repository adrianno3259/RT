#ifndef GLOSSYSPECULAR_H
#define GLOSSYSPECULAR_H

#include "brdf.h"


class GlossySpecular : public BRDF
{
    public:
        GlossySpecular();
        virtual ~GlossySpecular();
        virtual Color f(const Intersect& inter, const Vec3d& wi, const Vec3d& wo) const;
        virtual Color sample_f(const Intersect& inter, Vec3d& wi, const Vec3d& wo) const;
        virtual Color rho(const Intersect& inter, const Vec3d& wo) const;
        void setKs(float k);
        void setExp(float e);
    protected:
        float ks;
        float e;
    private:
};

#endif // GLOSSYSPECULAR_H

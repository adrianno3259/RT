#ifndef PERFECTSPECULAR_H
#define PERFECTSPECULAR_H

#include "brdf.h"


class PerfectSpecular : public BRDF
{
    public:
        PerfectSpecular();
        virtual ~PerfectSpecular();
        virtual Color sample_f(const Intersect& inter, Vec3d& wi, const Vec3d& wo) const;
        void setKr(float k);
        void setCr(Color c);
    protected:
        float kr;
        Color cr;
    private:
};

#endif // PERFECTSPECULAR_H

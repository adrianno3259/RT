#ifndef MATTE_H
#define MATTE_H

#include "material.h"

class Matte : public Material
{
    public:
        Matte(const Color& c);
        virtual ~Matte();
        virtual Color shade(const Scene& sc, Intersect& it) const ;
        void setKa(const float k);
        void setKd(const float k);
        void setCd(const Color& c);

    protected:
    private:
        Lambertian * diffuse_brdf;

};

#endif // MATTE_H

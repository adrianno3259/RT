#ifndef PHONG_H
#define PHONG_H

#include "material.h"
#include "lambertian.h"
#include "glossyspecular.h"

class Phong : public Material
{
    public:
        Phong(const Color& col);
        virtual ~Phong();
        virtual Color shade(const Scene& sc, Intersect& it) const;
        void setKd(const float k);
        void setKs(const float k);
        void setExp(const float);
        void setCd(const Color& c);
    protected:
        Lambertian* diffuse_brdf;
        GlossySpecular* specular_brdf;
    private:
};

#endif // PHONG_H

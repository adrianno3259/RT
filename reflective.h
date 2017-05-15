#ifndef REFLECTIVE_H
#define REFLECTIVE_H

#include "phong.h"
#include "perfectspecular.h"

class Reflective : public Phong
{
    public:

        Reflective(const Color& c);
        virtual ~Reflective();
        virtual Color shade(const Scene& sc, Intersect& it) const;
        void setKr(const float k);
        void setCr(const Color& c);

    protected:
        PerfectSpecular* reflective_brdf;
    private:
};

#endif // REFLECTIVE_H

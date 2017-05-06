#ifndef MATTE_H
#define MATTE_H

#include "material.h"

class Matte : public Material
{
    public:
        Matte(const Color& c);
        virtual ~Matte();
        virtual Color shade(const Scene& sc, Intersect& it);
    protected:
    private:
};

#endif // MATTE_H

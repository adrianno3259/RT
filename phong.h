#ifndef PHONG_H
#define PHONG_H

#include "material.h"


class Phong : public Material
{
    public:
        float ks, e;
        Phong(const Color& col);
        virtual ~Phong();
        virtual Color shade(const Scene& sc, Intersect& it);
    protected:

    private:
};

#endif // PHONG_H

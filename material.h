#ifndef MATERIAL_H
#define MATERIAL_H

#include "intersect.h"
#include "scene.h"

class Material
{
public:
    Color c;
    Material(const Color& c);
    Color shade(const Scene& sc, Intersect& it);
protected:
    float checkShadow(const Scene& sc, Light* l, const Intersect& it, float dist) const;
};

#endif // MATERIAL_H

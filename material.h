#ifndef MATERIAL_H
#define MATERIAL_H

#include "intersect.h"
#include "scene.h"

class Material
{
public:
    Material(const Color& c);
    virtual Color shade(const Scene& sc, Intersect& it) = 0;
protected:
    Color c;

};

#endif // MATERIAL_H

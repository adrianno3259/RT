#ifndef MATERIAL_H
#define MATERIAL_H

#include "intersect.h"
#include "scene.h"
#include "lambertian.h"

class Material
{
public:
    Material(const Color& c);
    virtual Color shade(const Scene& sc, Intersect& it) const = 0;
protected:
    Color c;
private:

};

#endif // MATERIAL_H

#ifndef OBJECT_H
#define OBJECT_H

#include "intersect.h"
#include "ray.h"
#include "globals.h"
#include "scene.h"
#include "light.h"
#include "boundingbox.h"
#include <iostream>
#include <vector>

#define printObject(A) std::cout<< #A << " ----------" <<std::endl; A.printData()
#define printObjectPtr(A) std::cout<< #A << " ----------" <<std::endl; A->printData()

class Material;
class Scene;

class Object{
public:
    Object();
    Material* m;
    Color c;
    virtual Intersect hit(const Ray& r) const;
    virtual void printData(void) const;
    virtual Vec3d getNormal(const Vec3d& P) const ;
    virtual std::vector<Intersect> hitList(const Ray& ray) const;
    virtual BoundingBox getBoudingBox();
};

#endif // OBJECT_H

#ifndef OBJECT_H
#define OBJECT_H

#include "intersect.h"
#include "ray.h"
#include "globals.h"
#include <iostream>

#define printObject(A) std::cout<< #A << " ----------" <<std::endl; A.printData()
#define printObjectPtr(A) std::cout<< #A << " ----------" <<std::endl; A->printData()

class Material;

class Object{
public:
    Object();
    Material* m;
    Color c;
    virtual Intersect hit(const Ray& r) const ;
    virtual void printData(void) const;
    virtual Vec3d getNormal(const Vec3d& P) const ;
};

#endif // OBJECT_H

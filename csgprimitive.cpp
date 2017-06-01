#include "csgprimitive.h"
#include <iostream>

CSGPrimitive::CSGPrimitive(Object* obj) : CSGNode(), object(obj)
{
    isPrimitive = true;
}

CSGPrimitive::~CSGPrimitive()
{
    //dtor
}

std::vector<Intersect> CSGPrimitive::getHitPoints(const Ray& r)
{
    //std::cout<<"primitive"<<std::endl;
    return object->hitList(r);
}


BoundingBox CSGPrimitive::getBoundingBox() const
{
    return object->getBoudingBox();
}

#include "compositeobject.h"
#include "math.h"
#include <iostream>

CompositeObject::CompositeObject()
{
    objs = std::vector<Object*>();
}

CompositeObject::~CompositeObject()
{
    //dtor
}

void CompositeObject::addObject(Object* o)
{
    objs.push_back(o);
}

Intersect CompositeObject::hit(const Ray& r) const
{
    //std::cout<<"---------- begin-----------"<<std::endl;
    int nObjs = objs.size();
    Intersect ret = Intersect();
    float tmin = INFINITY;
    for(int i = 0; i < nObjs; i++)
    {
        Intersect it = objs[i]->hit(r);
        if(it.t < tmin)
        {
            tmin = it.t;
            ret = it;

        }
    }
    return ret;
}
void CompositeObject::printData(void) const{}

Vec3d CompositeObject::getNormal(const Vec3d& P) const{}

std::vector<Intersect> CompositeObject::hitList(const Ray& ray) const{}


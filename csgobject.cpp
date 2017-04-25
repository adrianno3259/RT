#include "csgobject.h"
#include "globals.h"
#include <vector>

CSGObject::CSGObject(CSGNode* r)
{
    root = r;
}

CSGObject::~CSGObject()
{
    //dtor
}

Intersect CSGObject::hit(const Ray& r) const
{

    std::vector<Intersect> vl = root->getHitPoints(r);
    float tmin = 999999999999;
    int i;
    for(i = 0; i < vl.size(); i++)
    {

        if(vl[i].t > K_EPSILON){ return vl[i]; }
    }


}


std::vector<Intersect> CSGObject::hitList(const Ray& r) const
{
    return root->getHitPoints(r);
}

#include "csgoperation.h"
#include "mergehits.h"
#include <iostream>

CSGOperation::CSGOperation(CSGNode* l, CSGNode* r, char op)
{
    isPrimitive = false;
    left = l;
    right = r;
    operation = op;
}

CSGOperation::~CSGOperation()
{
    //dtor
}


std::vector<Intersect> CSGOperation::getHitPoints(const Ray& r)
{
    //std::cout<<"op -> "<<operation<<std::endl;

    if(operation == '+')
        return MergeHits::csg_or(left->getHitPoints(r), right->getHitPoints(r));
    else if(operation == '-')
        return MergeHits::csg_minus(left->getHitPoints(r), right->getHitPoints(r));
    else if(operation == '&')
        return MergeHits::csg_and(left->getHitPoints(r), right->getHitPoints(r));
    else
        return std::vector<Intersect>();
}



BoundingBox CSGOperation::getBoundingBox() const
{
    BoundingBox l, r;
    l = left->getBoundingBox();
    r = right->getBoundingBox();

    Vec3d   lminp = l.getMinPoint(),
            lmaxp = l.getMaxPoint(),
            rminp = r.getMinPoint(),
            rmaxp = r.getMaxPoint();

    Vec3d   minp = Vec3d((lminp.x < rminp.x ? lminp.x : rminp.x),
                         (lminp.y < rminp.y ? lminp.y : rminp.y),
                         (lminp.z < rminp.z ? lminp.z : rminp.z));

    Vec3d   maxp = Vec3d((lmaxp.x > rmaxp.x ? lmaxp.x : rmaxp.x),
                         (lmaxp.y > rmaxp.y ? lmaxp.y : rmaxp.y),
                         (lmaxp.z > rmaxp.z ? lmaxp.z : rmaxp.z));

    return BoundingBox(minp, maxp);
}

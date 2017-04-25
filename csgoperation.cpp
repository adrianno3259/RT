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

#include "csgnode.h"

CSGNode::CSGNode()
{

}

CSGNode::~CSGNode()
{

}

//std::vector<Intersect> CSGNode::getHitPoints(const Ray& r)
//{
//    std::vector<Intersect> v;
//
//    if(isPrimitive)
//    {
//        CSGPrimitive* p = (CSGPrimitive*) this;
//        return p->object->hitList(r);
//    }
//    else
//    {
//        CSGOperation* op = (CSGOperation*) this;
//        std::vector<Intersect> leftList, rightList;
//        if(op->operation == '+')
//            return MergeHits::csg_or(op->left->getHitPoints(r), op->right->getHitPoints(r));
//        else if(op->operation == '-')
//            return MergeHits::csg_minus(op->left->getHitPoints(r), op->right->getHitPoints(r));
//        else if(op->operation == '&')
//            return MergeHits::csg_and(op->left->getHitPoints(r), op->right->getHitPoints(r));
//        else
//            return std::vector<Intersect>();
//    }
//
//
//
//}

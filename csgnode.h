#ifndef CSGNODE_H
#define CSGNODE_H

#include <vector>
#include "intersect.h"
#include "ray.h"
#include "boundingbox.h"

class CSGNode
{
    public:
        bool isPrimitive;
        virtual std::vector<Intersect> getHitPoints(const Ray& r) =0;
        virtual ~CSGNode();
        virtual BoundingBox getBoundingBox() const =0;
    protected:
        CSGNode();

    private:
};

#endif // CSGNODE_H

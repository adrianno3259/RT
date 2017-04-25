#ifndef CSGPRIMITIVE_H
#define CSGPRIMITIVE_H

#include "object.h"
#include "csgnode.h"

class CSGPrimitive : public CSGNode
{
    public:
        Object* object;

        CSGPrimitive(Object* obj);
        virtual ~CSGPrimitive();
        virtual std::vector<Intersect> getHitPoints(const Ray& r);
    protected:

    private:
};

#endif // CSGPRIMITIVE_H

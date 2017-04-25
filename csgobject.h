#ifndef CSGOBJECT_H
#define CSGOBJECT_H

#include "object.h"
#include "csgnode.h"



class CSGObject : public Object
{
    public:
        CSGObject(CSGNode* r);
        CSGNode* root;
        virtual ~CSGObject();
        virtual Intersect hit(const Ray& r) const ;
        virtual std::vector<Intersect> hitList(const Ray& ray) const;
    protected:

    private:
};

#endif // CSGOBJECT_H

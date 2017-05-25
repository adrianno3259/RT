#ifndef COMPOSITEOBJECT_H
#define COMPOSITEOBJECT_H

#include "object.h"
#include <algorithm>

class CompositeObject : public Object
{
public:

    CompositeObject();
    virtual ~CompositeObject();

    void addObject(Object* o);

    virtual Intersect hit(const Ray& r) const;
    virtual void printData(void) const;
    virtual Vec3d getNormal(const Vec3d& P) const;
    virtual std::vector<Intersect> hitList(const Ray& ray) const;
private:
    std::vector<Object*> objs;


};

#endif // COMPOSITEOBJECT_H

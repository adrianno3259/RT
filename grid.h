#ifndef GRID_H
#define GRID_H

#include <vector>
#include "ray.h"
#include "object.h"
#include "boundingbox.h"
#include "compositeobject.h"
//class BoundingBox;

class Grid : public Object
{
    public:
        std::vector<Object*> objects;
        std::vector<Object*> cells;
        int nx, ny, nz;
        BoundingBox bbox;

        Vec3d minCoordinates();
        Vec3d maxCoordinates();

        Grid();
        virtual ~Grid();
        virtual BoundingBox getBoudingBox();
        void setup();
        virtual bool hitGrid(const Ray& r, float& t);
        virtual Intersect hit(const Ray& r) const;
        inline float clamp(const float x, const float minp, const float maxp) const { return ( x<minp? minp : (x>maxp? maxp : x) ); }
        void addObject(Object* o);
    protected:

    private:
};

#endif // GRID_H

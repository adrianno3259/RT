#ifndef LIGHT_H
#define LIGHT_H

#include "vec3.h"
#include "color.h"

#define printLight(A) std::cout<< #A << " ----------" <<std::endl; printVec(A.position); printVar(A.strength); printCol(A.color)

class Light
{
public:
    Vec3d position;
    float strength;
    Color color;

    Light(const Vec3d& p, const float s, const Color& c);
    Color getL() const;
    Vec3d getDirection(const Vec3d& pt) const;
};

#endif // LIGHT_H

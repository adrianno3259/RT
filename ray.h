#ifndef RAY_H
#define RAY_H

#include "vec3.h"

#define printRay(R) cout<< #R << " ----------" <<endl; printVec(R.origin); printVec(R.direction);

class Ray
{
public:
    Vec3d origin, direction;
    Ray();
    Ray(const Vec3d& o, const Vec3d& d);
    inline Vec3d rayPoint(float t) const;
};

inline Vec3d Ray::rayPoint(const float t) const { return (t * direction + origin); }

#endif // RAY_H

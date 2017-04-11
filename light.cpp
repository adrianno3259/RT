#include "light.h"


Light::Light(const Vec3d& p, const float s, const Color& c)
    : position(p), strength(s), color(c)
{

}

Color Light::getL() const
{
    return color*strength;
}

Vec3d Light::getDirection(const Vec3d& pt) const
{
    return (position - pt).hat();
}

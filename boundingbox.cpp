#include "boundingbox.h"
#include <iostream>

BoundingBox::BoundingBox(const Vec3d& minp, const Vec3d& maxp) : minPoint(minp), maxPoint(maxp)
{
    //ctor
}

BoundingBox::BoundingBox() : minPoint(Vec3d()), maxPoint(Vec3d())
{
    //ctor
}

BoundingBox::~BoundingBox()
{
    //dtor
}

bool BoundingBox::hit(const Ray& ray) const
{
    float ox = ray.origin.x, oy = ray.origin.y, oz = ray.origin.z;
    float dx = ray.direction.x, dy = ray.direction.y, dz = ray.direction.z;

    float txMin, tyMin, tzMin;
    float txMax, tyMax, tzMax;

    double a = 1.0/dx;
    // PP X
    if(a >= 0)
    {
        txMin = (minPoint.x - ox)*a;
        txMax = (maxPoint.x - ox)*a;
    }
    else
    {
        txMin = (maxPoint.x - ox)*a;
        txMax = (minPoint.x - ox)*a;
    }

    // PP Y

    double b = 1.0/dy;
    if(b >= 0)
    {
        tyMin = (minPoint.y - oy)*b;
        tyMax = (maxPoint.y - oy)*b;
    }
    else
    {
        tyMin = (maxPoint.y - oy)*b;
        tyMax = (minPoint.y - oy)*b;
    }

    // PP Z

    double c = 1.0/dz;
    if(c>=0){
        tzMin = (minPoint.z - oz)*c;
        tzMax = (maxPoint.z - oz)*c;
    } else {
        tzMin = (maxPoint.z - oz)*c;
        tzMax = (minPoint.z - oz)*c;
    }

    float t0, t1;

    // Maior ponto de entrada
    if( txMin > tyMin){
        t0 = txMin;
    } else {
        t0 = tyMin;
    }
    if( tzMin > t0){
        t0 = tzMin;
    }

    // Menor ponto de saída

    if( txMax < tyMax){
        t1 = txMax;
    } else {
        t1 = tyMax;
    }
    if( tzMax < t1){
        t1 = tzMax;
    }

    return (t0 < t1 && t1 > K_EPSILON);

}

bool BoundingBox::hit(const Ray& ray, float& tf) const
{
    float ox = ray.origin.x, oy = ray.origin.y, oz = ray.origin.z;
    float dx = ray.direction.x, dy = ray.direction.y, dz = ray.direction.z;

    float txMin, tyMin, tzMin;
    float txMax, tyMax, tzMax;

    double a = 1.0/dx;
    // PP X
    if(a >= 0)
    {
        txMin = (minPoint.x - ox)*a;
        txMax = (maxPoint.x - ox)*a;
    }
    else
    {
        txMin = (maxPoint.x - ox)*a;
        txMax = (minPoint.x - ox)*a;
    }

    // PP Y

    double b = 1.0/dy;
    if(b >= 0)
    {
        tyMin = (minPoint.y - oy)*b;
        tyMax = (maxPoint.y - oy)*b;
    }
    else
    {
        tyMin = (maxPoint.y - oy)*b;
        tyMax = (minPoint.y - oy)*b;
    }

    // PP Z

    double c = 1.0/dz;
    if(c>=0){
        tzMin = (minPoint.z - oz)*c;
        tzMax = (maxPoint.z - oz)*c;
    } else {
        tzMin = (maxPoint.z - oz)*c;
        tzMax = (minPoint.z - oz)*c;
    }

    float t0, t1;

    // Maior ponto de entrada
    if( txMin > tyMin){
        t0 = txMin;
    } else {
        t0 = tyMin;
    }
    if( tzMin > t0){
        t0 = tzMin;
    }

    // Menor ponto de saída

    if( txMax < tyMax){
        t1 = txMax;
    } else {
        t1 = tyMax;
    }
    if( tzMax < t1){
        t1 = tzMax;
    }

    if(t0 > K_EPSILON){
        tf = t0;
    } else {
        tf = t1;
    }

    return (t0 < t1 && t1 > K_EPSILON);

}


void BoundingBox::setMinPoint(const Vec3d& v)
{
    minPoint = v;
}
void BoundingBox::setMaxPoint(const Vec3d& v){
    maxPoint = v;
}

Vec3d BoundingBox::getMinPoint() const { return minPoint; }
Vec3d BoundingBox::getMaxPoint() const { return maxPoint; }

bool BoundingBox::inside(const Ray& r) const
{
    bool mi = (r.origin.x > minPoint.x) && (r.origin.y > minPoint.y) && (r.origin.z > minPoint.z);
    bool ma = (r.origin.x < maxPoint.x) && (r.origin.y < maxPoint.y) && (r.origin.z < maxPoint.z);

    return mi && ma;
}

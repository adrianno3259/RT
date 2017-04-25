#include "box.h"

Box::Box(const Vec3d& minp, const Vec3d& maxp) : minPoint(minp), maxPoint(maxp)
{
}

Box::Box() : minPoint(Vec3d(-10, -10, -10)), maxPoint(Vec3d(10, 10, 10))
{
}

Box::~Box()
{
}

Intersect Box::hit(const Ray& r) const
{
    Intersect i = Intersect();

    float ox = r.origin.x, oy = r.origin.y, oz = r.origin.z;
    float dx = r.direction.x, dy = r.direction.y, dz = r.direction.z;

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
    int face_in, face_out;

    // Maior ponto de entrada
    if( txMin > tyMin){
        t0 = txMin;
        face_in = (a >= 0.0) ? 0 : 3;
    } else {
        t0 = tyMin;
        face_in = (b >= 0.0) ? 1 : 4;
    }
    if( tzMin > t0){
        t0 = tzMin;
        face_in = (c >= 0.0) ? 2 : 5;
    }

    // Menor ponto de saída

    if( txMax < tyMax){
        t1 = txMax;
        face_out = (a >= 0.0) ? 3 : 0;
    } else {
        t1 = tyMax;
        face_out = (b >= 0.0) ? 4 : 1;
    }
    if( tzMax < t1){
        t1 = tzMax;
        face_out = (c >= 0.0) ? 5 : 2;
    }

    if(t0 < t1 && t1 > K_EPSILON){
        if(t0 > K_EPSILON){
            i.t = t0;
            i.normal = getNormal(face_in);
            i.entering = true;
        } else {
            i.t = t1;
            i.normal = getNormal(face_out);
        }
        i.hit = true;
        i.obj = (Object*) this;
        i.m = this->m;
        i.hitPoint = r.rayPoint(i.t);
        return i;
    } else {
        return i;
    }
}


void Box::printData(void) const { printVec(minPoint); printVec(maxPoint);}

Vec3d Box::getNormal(const Vec3d& p) const{

    if(p.x == minPoint.x)
        return getNormal(0);
    else if(p.y == minPoint.y)
        return getNormal(1);
    else if (p.z == minPoint.z)
        return getNormal(2);
    else if(p.x == maxPoint.x)
        return getNormal(3);
    else if(p.y == maxPoint.y)
        return getNormal(4);
    else if(p.z == maxPoint.z)
        return getNormal(5);
}

Vec3d Box::getNormal(const int face) const
{
    switch(face){
        case 0: return Vec3d(-1.0, 0.0, 0.0);
        case 1: return Vec3d(0.0, -1.0, 0.0);
        case 2: return Vec3d(0.0, 0.0, -1.0);
        case 3: return Vec3d(1.0, 0.0, 0.0);
        case 4: return Vec3d(0.0, 1.0, 0.0);
        case 5: return Vec3d(0.0, 0.0, 1.0);
    }
}



std::vector<Intersect> Box::hitList(const Ray& r) const
{
    std::vector<Intersect> v = std::vector<Intersect>();
    Intersect i = Intersect();

    float ox = r.origin.x, oy = r.origin.y, oz = r.origin.z;
    float dx = r.direction.x, dy = r.direction.y, dz = r.direction.z;

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
    int face_in, face_out;

    // Maior ponto de entrada
    if( txMin > tyMin){
        t0 = txMin;
        face_in = (a >= 0.0) ? 0 : 3;
    } else {
        t0 = tyMin;
        face_in = (b >= 0.0) ? 1 : 4;
    }
    if( tzMin > t0){
        t0 = tzMin;
        face_in = (c >= 0.0) ? 2 : 5;
    }

    // Menor ponto de saída

    if( txMax < tyMax){
        t1 = txMax;
        face_out = (a >= 0.0) ? 3 : 0;
    } else {
        t1 = tyMax;
        face_out = (b >= 0.0) ? 4 : 1;
    }
    if( tzMax < t1){
        t1 = tzMax;
        face_out = (c >= 0.0) ? 5 : 2;
    }

    if(t0 < t1  && t1 > K_EPSILON){
        i.hit = true;
        i.obj = (Object*) this;
        i.m = this->m;
        i.t = t0;
        i.hitPoint = r.rayPoint(i.t);
        i.normal = getNormal(face_in);
        i.entering = true;
        v.push_back(i);


        i.t = t1;
        i.hitPoint = r.rayPoint(i.t);
        i.normal = getNormal(face_out);
        i.entering = false;
        i.normal = -i.normal;
        v.push_back(i);
    }
    return v;
}

#include "sphere.h"
#include <cmath>

Sphere::Sphere() : center(Vec3d()), radius(1.0), Object() {}
Sphere::Sphere(float r) : center(Vec3d()), radius(r), Object() {}
Sphere::Sphere(const Vec3d& c, float r) : center(c), radius(r), Object() {}

Intersect Sphere::hit(const Ray& ray) const
{
    Intersect i;
    float t;
    Vec3d temp = ray.origin - center;
    double a = ray.direction * ray.direction;
    double b = 2.0 * temp * ray.direction;
    double c = temp*temp - radius*radius;
    double disc = b * b - (4.0 * a * c);

    i.hit = false;
    i.entering = false;
    i.t = 0.0;
    i.hitPoint = Vec3d();
    i.normal = Vec3d();
    i.obj = NULL;

    //printVar(a); printVar(b); printVar(c); printVar(disc);
    if(disc < 0.0) {i.hit = false; return i;}
    else {
        float e = sqrt(disc);
        float denom = 2.0*a;
        t = ((-b) -e)/denom;
        if (t > K_EPSILON ) {
            i.t= t;
            i.entering = true;
            i.hit = true;
            i.obj = (Object*) this;
            i.c = this->c;
            i.m = this->m;
            i.hitPoint = ray.rayPoint(t);
            i.normal = this->getNormal(i.hitPoint);
            return i;
        }

        t = (-b + e)/denom;
        if (t > K_EPSILON) {
            i.t= t;
            i.entering = false;
            i.hit = true;
            i.obj = (Object*)this;
            i.c = this->c;
            i.m = this->m;
            i.hitPoint = ray.rayPoint(t);
            i.normal = this->getNormal(i.hitPoint);
            return i;
        }
    }
    i.hit = false;
    return i;
}

void Sphere::printData(void) const
{
    printVar(radius);
    printVec(center);
}

Vec3d Sphere::getNormal(const Vec3d& P) const
{
    Vec3d tmp = P - center;
    tmp.normalize();
    return tmp;
}


std::vector<Intersect> Sphere::hitList(const Ray& ray) const
{

    std::vector<Intersect> li = std::vector<Intersect>();
    Intersect i1, i2;
    float t;
    Vec3d temp = ray.origin - center;
    double a = ray.direction * ray.direction;
    double b = 2.0 * temp * ray.direction;
    double c = temp*temp - radius*radius;
    double disc = b * b - (4.0 * a * c);

    if(disc > 0.0){

        float e = sqrt(disc);
        float denom = 2.0*a;
        t = ((-b) -e)/denom; //printVar(t);
        i1.t= t;
        i1.entering = true;
        i1.hit = true;
        i1.obj = (Object*) this;
        i1.c = this->c;
        i1.m = this->m;
        i1.hitPoint = ray.rayPoint(t);
        i1.normal = this->getNormal(i1.hitPoint);
        li.push_back(i1);

        t = (-b + e)/denom; //printVar(t);
        i2.t= t;
        i2.entering = false;
        i2.hit = true;
        i2.obj = (Object*)this;
        i2.c = this->c;
        i2.m = this->m;
        i2.hitPoint = ray.rayPoint(i2.t);
        i2.normal = -this->getNormal(i2.hitPoint);
        li.push_back(i2);

    }

    return li;
}

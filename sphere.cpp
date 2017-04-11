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
    //printVec(temp);
    double a = ray.direction * ray.direction;
    double b = 2.0 * temp * ray.direction;
    double c = temp*temp - radius*radius;
    double disc = b * b - (4.0 * a * c);
    //printVar(a); printVar(b); printVar(c); printVar(disc);

    if(disc < 0.0) {i.hit = false; return i;}
    else {
        float e = sqrt(disc);
        float denom = 2.0*a;
        t = ((-b) -e)/denom;
        //std::cout<<"t1 is "<<t<<std::endl;
        if (t > K_EPSILON ) {
            i.t= t;
            i.entering = true;
            i.hit = true;
            i.obj = (Object*) this;
            i.c = this->c;
            i.m = this->m;
            i.hitPoint = ray.rayPoint(t);
            i.normal = this->getNormal(i.hitPoint);
            //i.normal = (temp + t*ray.d)/radius;
            //sr.hit_point = ray.o + t*ray.d;
            return i;
        }

        t = (-b + e)/denom;
        //std::cout<<"t2 is "<<t<<std::endl;
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

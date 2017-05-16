#ifndef INTERSECT_H
#define INTERSECT_H

#include "color.h"
#include "vec3.h"
#include "ray.h"

#define printInters(A) std::cout <<"Intersection "<< #A <<":"<<std::endl; printVar(A.hit); printVar(A.t); printVec(A.hitPoint); printVar(A.entering); printCol(A.c)

class Object;
class Material;

typedef struct Intersect
{
    Intersect(bool ht, const float tnum, Object* o, bool ent, const Vec3d& htp, const Vec3d& norm, Material* mat, const Color& col)
    : hit(ht), t(tnum), obj(o), entering(ent), hitPoint(htp), normal(norm), m(mat), c(col) {}
    Intersect()
    {
        this->depth = 0;
        this->hit = false;
        this->entering = false;
        this->t = 0.0;
        this->hitPoint = Vec3d();
        this->normal = Vec3d();
        this->obj = 0;
        this->m = 0;
        this->c = Color();
    }
    Ray r;
    bool hit;
    float t; // ponto paramétrico t no raio que atingiu o objeto
    Object* obj; // objeto atingido
    bool entering; // se o raio da interseção está entrando ou não no objeto
    int depth;
    Vec3d hitPoint;
    Vec3d normal;
    Material* m;
    Color c;
} Intersect;

#endif // INTERSECT_H

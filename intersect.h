#ifndef INTERSECT_H
#define INTERSECT_H

#include "color.h"
#include "vec3.h"

#define printInters(A) std::cout <<"Intersection "<< #A <<":"<<std::endl; printVar(A.hit); printVar(A.t); printVec(A.hitPoint); printVar(A.entering); printCol(A.c)

class Object;
class Material;

typedef struct
{
    public:
    bool hit;
    float t; // ponto paramétrico t no raio que atingiu o objeto
    Object* obj; // objeto atingido
    bool entering; // se o raio da interseção está entrando ou não no objeto
    Vec3d hitPoint;
    Vec3d normal;
    Material* m;
    Color c;
} Intersect;

#endif // INTERSECT_H

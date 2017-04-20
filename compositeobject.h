#ifndef COMPOSITEOBJECT_H
#define COMPOSITEOBJECT_H

#include "object.h"
#include <algorithm>




class CompositeObject : public Object
{


    bool primitive; // variável que informa se um objeto composto é uma "folha" da árvore de objetos
    Object* prim; // usado apenas se o objeto for um nó primitivo e não de operação
    char operation; // usado se o nó é uma operação booleana, e pode assumir 3 valores: '-', '&' e '|'
    CompositeObject();
    virtual ~CompositeObject();

    virtual Intersect hit(const Ray& r) const = 0;
    virtual void printData(void) const = 0;
    virtual Vec3d getNormal(const Vec3d& P) const = 0;

private:


};

#endif // COMPOSITEOBJECT_H

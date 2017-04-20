#ifndef COMPOSITEOBJECT_H
#define COMPOSITEOBJECT_H

#include "object.h"
#include <algorithm>




class CompositeObject : public Object
{


    bool primitive; // vari�vel que informa se um objeto composto � uma "folha" da �rvore de objetos
    Object* prim; // usado apenas se o objeto for um n� primitivo e n�o de opera��o
    char operation; // usado se o n� � uma opera��o booleana, e pode assumir 3 valores: '-', '&' e '|'
    CompositeObject();
    virtual ~CompositeObject();

    virtual Intersect hit(const Ray& r) const = 0;
    virtual void printData(void) const = 0;
    virtual Vec3d getNormal(const Vec3d& P) const = 0;

private:


};

#endif // COMPOSITEOBJECT_H

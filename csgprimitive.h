#ifndef CSGPRIMITIVE_H
#define CSGPRIMITIVE_H

#include "object.h"
#include "csgnode.h"

/*
    Class: CSGPrimitive

    Nó CSG que contém uma forma primitiva

    Super-Class:
        -CSGNode

    See Also:
        <CSGNode>, <CSGOperation>
*/
class CSGPrimitive : public CSGNode
{
    public:

        /*
            Constructor: CSGPrimitive

            Inicializa o nó que contém uma forma primitiva do CSG.

            Parameters:

                obj - Objeto primitivo contido no nó
        */
        CSGPrimitive(Object* obj);
        /*
            Destructor: ~CSGPrimitive
        */
        virtual ~CSGPrimitive();
        /*
            Method: getHitPoints

            Retorna uma lista de pontos de interseção após realizar sua respectiva operação

            Parameters:

                r - Raio com o qual as interseções serão calculadas.
        */
        virtual std::vector<Intersect> getHitPoints(const Ray& r);
    protected:
        /*
            Variable: object

            Objeto primitivo que compõe o nó
        */
        Object* object;
    private:
};

#endif // CSGPRIMITIVE_H

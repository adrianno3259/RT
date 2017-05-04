#ifndef CSGPRIMITIVE_H
#define CSGPRIMITIVE_H

#include "object.h"
#include "csgnode.h"

/*
    Class: CSGPrimitive

    N� CSG que cont�m uma forma primitiva

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

            Inicializa o n� que cont�m uma forma primitiva do CSG.

            Parameters:

                obj - Objeto primitivo contido no n�
        */
        CSGPrimitive(Object* obj);
        /*
            Destructor: ~CSGPrimitive
        */
        virtual ~CSGPrimitive();
        /*
            Method: getHitPoints

            Retorna uma lista de pontos de interse��o ap�s realizar sua respectiva opera��o

            Parameters:

                r - Raio com o qual as interse��es ser�o calculadas.
        */
        virtual std::vector<Intersect> getHitPoints(const Ray& r);
    protected:
        /*
            Variable: object

            Objeto primitivo que comp�e o n�
        */
        Object* object;
    private:
};

#endif // CSGPRIMITIVE_H

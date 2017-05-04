#ifndef CSGOPERATION_H
#define CSGOPERATION_H

#include <vector>
#include "intersect.h"
#include "csgnode.h"

/*
    Class: CSGOperation
    Cont�m as informa��es necess�rias para um n� de opera��o da �rvore CSG

    Super-Class:
        CSGNode

    See Also:
        <CSGNode>, <CSGPrimitive>
*/
class CSGOperation : public CSGNode
{
    public:
        /*
            Constructor: CSGOperation

            Inicializa o n� de opera��o do CSG.

            Parameters:

                l - N�-filho esquerdo, pode ser uma opera��o CSG (CSGOperation) ou uma primitiva CSG(CSGPrimitive).
                r - N�-filho direito, pode ser uma opera��o CSG (CSGOperation) ou uma primitiva CSG(CSGPrimitive).
                op - Caracter que armazena o tipo de opera��o a ser realizada nos filhos.
        */
        CSGOperation(CSGNode* l, CSGNode* r, char op);
        /*
            Destructor: ~CSGOperation

            Destrutor default
        */
        virtual ~CSGOperation();
        /*
            Method: getHitPoints

            Retorna uma lista de pontos de interse��o ap�s realizar sua respectiva opera��o.

            Parameters:

                r - Raio com o qual as interse��es ser�o calculadas.
        */
        virtual std::vector<Intersect> getHitPoints(const Ray& r);
    protected:
        /*
            Variable: left
            Ponteiro para o n�-filho � esquerda
        */
        CSGNode *left;
        /*
            Variable: right
            Ponteiro para o n�-filho � direita
        */
        CSGNode *right;
        /*
            Variable: operation
            Cont�m a opera��o que o n� representa, podendo ser:
            + -> uni�o
            - -> diferen�a
            & -> interse��o
        */
        char operation;

    private:
};

#endif // CSGOPERATION_H

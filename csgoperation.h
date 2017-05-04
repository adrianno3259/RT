#ifndef CSGOPERATION_H
#define CSGOPERATION_H

#include <vector>
#include "intersect.h"
#include "csgnode.h"

/*
    Class: CSGOperation
    Contém as informações necessárias para um nó de operação da árvore CSG

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

            Inicializa o nó de operação do CSG.

            Parameters:

                l - Nó-filho esquerdo, pode ser uma operação CSG (CSGOperation) ou uma primitiva CSG(CSGPrimitive).
                r - Nó-filho direito, pode ser uma operação CSG (CSGOperation) ou uma primitiva CSG(CSGPrimitive).
                op - Caracter que armazena o tipo de operação a ser realizada nos filhos.
        */
        CSGOperation(CSGNode* l, CSGNode* r, char op);
        /*
            Destructor: ~CSGOperation

            Destrutor default
        */
        virtual ~CSGOperation();
        /*
            Method: getHitPoints

            Retorna uma lista de pontos de interseção após realizar sua respectiva operação.

            Parameters:

                r - Raio com o qual as interseções serão calculadas.
        */
        virtual std::vector<Intersect> getHitPoints(const Ray& r);
    protected:
        /*
            Variable: left
            Ponteiro para o nó-filho à esquerda
        */
        CSGNode *left;
        /*
            Variable: right
            Ponteiro para o nó-filho à direita
        */
        CSGNode *right;
        /*
            Variable: operation
            Contém a operação que o nó representa, podendo ser:
            + -> união
            - -> diferença
            & -> interseção
        */
        char operation;

    private:
};

#endif // CSGOPERATION_H

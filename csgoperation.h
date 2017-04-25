#ifndef CSGOPERATION_H
#define CSGOPERATION_H

#include <vector>
#include "intersect.h"
#include "csgnode.h"

class CSGOperation : public CSGNode
{
    public:
        CSGNode *left, *right;
        char operation; // +/-/&
        CSGOperation(CSGNode* l, CSGNode* r, char op);
        virtual ~CSGOperation();
        virtual std::vector<Intersect> getHitPoints(const Ray& r);
    protected:

    private:
};

#endif // CSGOPERATION_H

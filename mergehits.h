#ifndef MERGEHITS_H
#define MERGEHITS_H

#include <vector>
#include "intersect.h"

class MergeHits
{
    public:
        MergeHits();
        static std::vector<Intersect> csg_and(const std::vector<Intersect>& v1, const std::vector<Intersect>& v2);
        static std::vector<Intersect> csg_or(const std::vector<Intersect>& v1, const std::vector<Intersect>& v2);
        //static std::vector<Intersect> csg_minus(const std::vector<Intersect>& v1, const std::vector<Intersect>& v2);

    protected:

    private:
};

#endif // MERGEHITS_H

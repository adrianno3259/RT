#include "interval.h"
#include "globals.h"

Interval::Interval() {}

Interval::~Interval(){}


Interval Interval::intervalOr(const Interval& i)
{
    Interval ret;
    int smaller = points.size() < i.points.size() ;// 1 se for o objeto e 0 se for o parâmetro
    int it, minSize = smaller ? points.size() : i.points.size(), maxSize = (smaller ?  i.points.size():points.size()) ;
    bool in = true;

    printVar(smaller); printVar(minSize); printVar(maxSize);


    for(it = 0; it < minSize; it++)
    {

        if(in)
        {
            ret.points.push_back((points[it] < i.points[it])? points[it] : i.points[it]);

        }
        else
        {
            ret.points.push_back((points[it] > i.points[it])? points[it] : i.points[it]);
        }
        in = !in;
    }

    if(smaller)
    for(it = minSize; it < maxSize; it++)
         ret.points.push_back(points[it]);
    else
    for(it = minSize; it < maxSize; it++)
        ret.points.push_back(i.points[it]);
    return ret;
}

Interval Interval::intervalAnd(const Interval& i)
{

}
Interval Interval::intervalMinus(const Interval& i)
{

}

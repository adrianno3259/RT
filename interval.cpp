#include "interval.h"
#include "globals.h"

Interval::Interval() {}

Interval::~Interval(){}


Interval Interval::intervalOr(const Interval& i)
{

    Interval ret;
    int smaller = points.size() < i.points.size() ;// 1 se for o objeto e 0 se for o parâmetro
    int it, jt, minSize = smaller ? points.size() : i.points.size(),
                maxSize = (smaller ?  i.points.size():points.size()) ;
    //bool in = true;

    //Ordenar listas caso venhas desordenads: std::sort(...)

    printVar(smaller); printVar(minSize); printVar(maxSize);
    bool itFirst;
    //Interval* L1;
    //Interval* L2;
    int it_L1, it_L2;

    for(it = 0, jt = 0; (it < points.size()) && (jt < i.points.size());)
    {
        itFirst = points[it] < i.points[jt];
        const Interval* L1 = (itFirst)?(this):(&i);
        const Interval* L2 = (itFirst)?(&i):(this);

        it_L1 = (itFirst)?(it):(jt);
        it_L2 = (itFirst)?(jt):(it);

        //(itFirst)? (L1 = this, L2 = &i) : (L1 = &i, L2 = this); //estude e entenda

        //if() { L1 = this; L2 = &i; }
        //else                          { L1 = &i; L2 = this; }

        ret.points.push_back(L1->points[it_L1]);
        if(L1->points[it_L1+1] < L2->points[it_L2]) // intervalos sem interseção
        {
            ret.points.push_back(L1->points[it_L1+1]);
            it_L1+=2;
        }
        else // com inters
        {
            if(L1->points[it_L1+1] < L2->points[it_L2+1]) // se j n está contido em i
            {
                ret.points.push_back(L2->points[it_L2+1]);
                it_L2+=2;
                it_L1+=2;
            }
            else
            {
                ret.points.push_back(L1->points[it_L1+1]);
                it_L2+=2; it_L1+=2;
            }
        }

        it = (itFirst)?(it_L1):(it_L2);
        jt = (itFirst)?(it_L2):(it_L1);
    }


    for(; it < points.size(); it++)
         ret.points.push_back(points[it]);
    for(;jt<i.points.size();jt++)
        ret.points.push_back(i.points[jt]);

    return ret;
}

Interval Interval::intervalAnd(const Interval& i)
{

}
Interval Interval::intervalMinus(const Interval& i)
{

}

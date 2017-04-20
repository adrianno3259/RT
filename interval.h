#ifndef INTERVAL_H
#define INTERVAL_H

#include<vector>
#include<iostream>

#define printInterval(A) std::cout<<#A<<std::endl; \
                         for(int i = 0; i < A.points.size(); i++)\
                            std::cout<<A.points[i]<<" "; \
                         std::cout<<std::endl;

class Interval
{
    public:
    Interval();
    virtual ~Interval();
    std::vector<float> points;
    Interval intervalOr(const Interval& i) ;
    Interval intervalAnd(const Interval& i);
    Interval intervalMinus(const Interval& i);


};

#endif // INTERVAL_H

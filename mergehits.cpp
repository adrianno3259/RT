#include "mergehits.h"
#include "globals.h"
#include <iostream>

MergeHits::MergeHits(){}

std::vector<Intersect> MergeHits::csg_minus(const std::vector<Intersect>& v1, const std::vector<Intersect>& v2) // v1 - v2 != v2 - v1
{
     std::vector<Intersect> ret;

    int it, jt;

    for(it = 0, jt = 0; (it < v1.size()) && (jt < v2.size());)
    {
        if(v1[it].t < v2[jt].t) {
            ret.push_back(v1[it]);
            if(v1[it+1].t < v2[jt].t) // primeiro intervalo sem interseção com o segundo
            {
                ret.push_back(v1[it+1]);
                it+=2;
            }
            else // com interseção
            {
                if(v1[it+1].t < v2[jt+1].t) // se o segundo nao está contido no primeiro intervalo
                {
                    ret.push_back(v2[jt]);
                    it+=2;
                    jt+=2;
                }
                else
                {
                    ret.push_back(v2[jt]);
                    ret.push_back(v2[jt+1]);
                    ret.push_back(v1[it+1]);
                    it+=2; jt+=2;
                }
            }
        }
        else { // segundo intervalo começa antes do primeiro
            if(v2[jt+1].t < v1[it].t) // segundo intervalo sem interseção com o primeiro
            {
                ret.push_back(v1[it]);
                ret.push_back(v1[it+1]);
                jt+=2;
            }
            else // com interseção
            {
                if(v2[jt+1].t < v1[it+1].t) // se o primeiro nao está contido no segundo intervalo
                {
                    ret.push_back(v2[jt+1]);
                    ret.push_back(v1[it+1]);
                    it+=2;
                    jt+=2;
                }
                else
                {
                    it+=2; jt+=2;
                }
            }
        }
    }

    for(;it < v1.size(); it++)
         ret.push_back(v1[it]);

    return ret;
}

std::vector<Intersect> MergeHits::csg_and(const std::vector<Intersect>& v1, const std::vector<Intersect>& v2)
{
    std::vector<Intersect> ret;

    int it, jt;

    for(it = 0, jt = 0; (it < v1.size()) && (jt < v2.size());)
    {

        if(v1[it].t < v2[jt].t) {
            if(v1[it+1].t < v2[jt].t) // primeiro intervalo sem interseção com o segundo
                it+=2;
            else // com interseção
            {
                if(v1[it+1].t < v2[jt+1].t) // se o segundo nao está contido no primeiro intervalo
                {
                    ret.push_back(v2[jt]);
                    ret.push_back(v1[it+1]);
                    it+=2;
                    jt+=2;
                }
                else
                {
                    ret.push_back(v2[jt]);
                    ret.push_back(v2[jt+1]);
                    it+=2; jt+=2;
                }
            }
        }
        else { // segundo intervalo começa antes do primeiro
            if(v2[jt+1].t < v1[it].t) // segundo intervalo sem interseção com o primeiro
                jt+=2;
            else // com interseção
            {
                if(v2[jt+1].t < v1[it+1].t) // se o primeiro nao está contido no segundo intervalo
                {
                    ret.push_back(v1[it]);
                    ret.push_back(v2[jt+1]);
                    it+=2;
                    jt+=2;
                }
                else
                {
                    ret.push_back(v1[it]);
                    ret.push_back(v1[it+1]);
                    it+=2; jt+=2;
                }
            }
        }

    }
    return ret;
}

std::vector<Intersect> MergeHits::csg_or(const std::vector<Intersect>& v1, const std::vector<Intersect>& v2){


    std::vector<Intersect> ret;

    int it, jt;
    for(it = 0, jt = 0; (it < v1.size()) && (jt < v2.size());) {
        if(v1[it].t < v2[jt].t) {
            ret.push_back(v1[it]);
            if(v1[it+1].t < v2[jt].t) // primeiro intervalo sem interseção com o segundo
            {
                ret.push_back(v1[it+1]);
                it+=2;
            }
            else // com interseção
            {
                if(v1[it+1].t < v2[jt+1].t) // se o segundo nao está contido no primeiro intervalo
                {
                    ret.push_back(v2[jt+1]);
                    it+=2;
                    jt+=2;
                }
                else
                {
                    ret.push_back(v1[it+1]);
                    it+=2; jt+=2;
                }
            }
        }
        else // segundo intervalo começa antes do primeiro
        {
            ret.push_back(v2[jt]);
            if(v2[jt+1].t < v1[it].t) // segundo intervalo sem interseção com o primeiro
            {
                ret.push_back(v2[jt+1]);
                jt+=2;
            }
            else // com interseção
            {
                if(v2[jt+1].t < v1[it+1].t) // se o segundo nao está contido no primeiro intervalo
                {
                    ret.push_back(v1[it+1]);
                    it+=2;
                    jt+=2;
                }
                else
                {
                    ret.push_back(v2[jt+1]);
                    it+=2; jt+=2;
                }
            }
        }
    }

    for(;it < v1.size(); it++)
         ret.push_back(v1[it]);
    for(;jt<v2.size();jt++)
        ret.push_back(v2[jt]);
    return ret;
}

#include "grid.h"
#include "math.h"

#define prIdx(Txt,A,B,C) std::cout<<Txt<<std::endl; printVar(A); printVar(B); printVar(C);
#define pr3(A,B,C) printVar(A); printVar(B); printVar(C)
using namespace std;

Grid::Grid() : bbox(BoundingBox(Vec3d(), Vec3d()))
{
    objects = std::vector<Object*>();
}

Grid::~Grid()
{
    //dtor
}

bool Grid::hitGrid(const Ray& r, float& t)
{
    bool hit = bbox.hit(r, t);
    return hit;
}

#include<cstdlib>

Intersect Grid::hit(const Ray& r) const
{
    //std::cout<<"antes da bbox"<<std::endl;
    Intersect inter = Intersect();
    int ix, iy, iz;
    float ox = r.origin.x, oy = r.origin.y, oz = r.origin.z, t0, t1;

    // Verifica se o raio atinge a grid em algum ponto

    if(bbox.hit(r, t0, t1)) // Se o raio atinge a grid, calcula a célula mais próxima da origem
    {

            Vec3d minp = bbox.getMinPoint(), maxp = bbox.getMaxPoint();
        /* ---------------------------------------------------------------------------------- */

        	double ox = r.origin.x;
            double oy = r.origin.y;
            double oz = r.origin.z;
            double dx = r.direction.x;
            double dy = r.direction.y;
            double dz = r.direction.z;

            double x0 = minp.x;
            double y0 = minp.y;
            double z0 = minp.z;
            double x1 = maxp.x;
            double y1 = maxp.y;
            double z1 = maxp.z;

            double txMin, tyMin, tzMin;
            double txMax, tyMax, tzMax;

            // the following code includes modifications from Shirley and Morley (2003)

            double a = 1.0 / dx;
            if (a >= 0) {
                txMin = (x0 - ox) * a;
                txMax = (x1 - ox) * a;
            }
            else {
                txMin = (x1 - ox) * a;
                txMax = (x0 - ox) * a;
            }

            double b = 1.0 / dy;
            if (b >= 0) {
                tyMin = (y0 - oy) * b;
                tyMax = (y1 - oy) * b;
            }
            else {
                tyMin = (y1 - oy) * b;
                tyMax = (y0 - oy) * b;
            }

            double c = 1.0 / dz;
            if (c >= 0) {
                tzMin = (z0 - oz) * c;
                tzMax = (z1 - oz) * c;
            }
            else {
                tzMin = (z1 - oz) * c;
                tzMax = (z0 - oz) * c;
            }


//            pr3(txMin, tyMin, tzMin);
//            pr3(txMax, tyMax, tzMax);

            //double t0, t1;

            if (txMin > tyMin)
                t0 = txMin;
            else
                t0 = tyMin;

            if (tzMin > t0)
                t0 = tzMin;

            if (txMax < tyMax)
                t1 = txMax;
            else
                t1 = tyMax;

            if (tzMax < t1)
                t1 = tzMax;

            if (t0 > t1){
                inter.hit = false;
                return inter;

            }


        if (bbox.inside(r)) {  			// does the ray start inside the grid?
            ix = clamp((ox - x0) * nx / (x1 - x0), 0, nx - 1);
            iy = clamp((oy - y0) * ny / (y1 - y0), 0, ny - 1);
            iz = clamp((oz - z0) * nz / (z1 - z0), 0, nz - 1);
        }
        else {
            Vec3d p = r.origin + t0 * r.direction;  // initial hit point with grid's bounding box
            ix = clamp((p.x - x0) * nx / (x1 - x0), 0, nx - 1);
            iy = clamp((p.y - y0) * ny / (y1 - y0), 0, ny - 1);
            iz = clamp((p.z - z0) * nz / (z1 - z0), 0, nz - 1);
        }

        /*------------------------------------------------------------------------------------ */

/*
        if(bbox.inside(r)) { // Verificando se o raio está dentro ou fora da grid
            // obtendo o índice da célula da grid na qual o raio está contido
            ix = clamp((ox - minp.x)*nx/(maxp.x - minp.x), 0, nx-1);
            iy = clamp((oy - minp.y)*ny/(maxp.y - minp.y), 0, ny-1);
            iz = clamp((oz - minp.z)*nz/(maxp.z - minp.z), 0, nz-1);

        } else {

            //std::cout<<"TO FORA!"<<std::endl;
            // obtendo o índice da primeira célula da grid atingida pelo raio
            Vec3d p = r.rayPoint((t0 > 0)? t0 : t1);
            ix = clamp((p.x - minp.x)*nx/(maxp.x - minp.x), 0, nx);
            iy = clamp((p.y - minp.y)*ny/(maxp.y - minp.y), 0, ny);
            iz = clamp((p.z - minp.z)*nz/(maxp.z - minp.z), 0, nz);

        }
*/


//
//        float txMax = maxp.x, tyMax = maxp.y, tzMax = maxp.z;
//        float txMin = minp.x, tyMin = minp.y, tzMin = minp.z;
//
//        Ray pMin = r.rayPoint(t0), pMax = r.rayPoint(t1);
//        float txMax = pMax.x, tyMax = pMax.y, tzMax = pMax.z;
//        float txMin = pMin.x, tyMin = pMin.y, tzMin = pMin.z;


        // interseção com a grid

        float dtx = (txMax - txMin) / nx;
        float dty = (tyMax - tyMin) / ny;
        float dtz = (tzMax - tzMin) / nz;

        float txNext, tyNext, tzNext;
        int ixStep, iyStep, izStep;
        int ixStop, iyStop, izStop;

        if(r.direction.x > 0)
        {
            txNext = txMin + (ix + 1) *dtx;
            ixStep = +1;
            ixStop = nx;
        }
        else if (r.direction.x < 0)
        {
            txNext = txMin + (nx - ix) * dtx;
            ixStep = -1;
            ixStop = -1;
        }
        else
        {
            txNext = INFINITY;
            ixStep = -1;
            ixStop = -1;
        }


        if(r.direction.y > 0)
        {
            tyNext = tyMin + (iy + 1) *dty;
            iyStep = +1;
            iyStop = ny;
        }
        else if(r.direction.y < 0)
        {
            tyNext = tyMin + (ny - iy) * dty;
            iyStep = -1;
            iyStop = -1;
        }
        else
        {
            tyNext = INFINITY;
            iyStep = -1;
            iyStop = -1;
        }


        if(r.direction.z > 0)
        {
            tzNext = tzMin + (iz + 1) *dtz;
            izStep = +1;
            izStop = nz;
        }
        else if(r.direction.z < 0)
        {
            tzNext = tzMin + (nz - iz) * dtz;
            izStep = -1;
            izStop = -1;
        }
        else
        {
            tzNext = INFINITY;
            izStep = -1;
            izStop = -1;
        }


        while(true)
        {
//            system("pause");
//            std::cout<<"testandoooo 1 2 3 ------"<<std::endl;

            Object* obj = cells[ ix + (nx*iy) + (nx*ny*iz) ];
//            printVar( ix + (nx*iy) + (nx*ny*iz) );
            //std::cout<<"PIXELLLLL!!!!!!!!"<<(int)obj<<std::endl;

//            printVar(txNext);
//            printVar(tyNext);
//            printVar(tzNext);
//            printVar(txNext < tyNext);
//            printVar(txNext < tzNext);
            if(txNext < tyNext && txNext < tzNext) // avança no eixo X
            {

//                std::cout<<"X pode avançar..."<<std::endl;
//                printVar(ix);
//                printVar(iy);
//                printVar(iz);
                if(obj) // Se célula não é vazia
                {
                    inter = obj->hit(r);
//                    std::cout<<"PIXELLLLL!!!!!!!!"<<std::endl;
                    // raio atingiu um objeto antes de sair da célula
                    if(inter.hit){
//                        std::cout<<"X pode avançar..."<<std::endl;
//                        printVar(ix);
//                        printVar(iy);
//                        printVar(iz);
//                        std::cout<<"acerteeeei -------------------- "<<std::endl;
//                        printVar(inter.t < txNext);
//                        printVar(inter.t);
//                        printVar(txNext);
//                        printObjectPtr((inter.obj));
                    }

                    if(inter.hit && inter.t < txNext)
                    {
//                        printObjectPtr(obj);
                        return inter;
                    }

                }
                txNext += dtx;
                ix+=ixStep;

                if(ix == ixStop)
                {
                    inter.hit = false;
                    return inter;
                }

            }
            else if(tyNext < tzNext)
            {
//                std::cout<<std::endl;
//                prIdx("Y pode avançar...",ix,iy,iz);
                if(obj) // Se célula não é vazia
                {
                    inter = obj->hit(r);
//                    std::cout<<(inter.hit ? "acerteeeei ------------------- >>>>" : "Erreeeei")<<std::endl;
//                    printVar(inter.t < tyNext);
                    // raio atingiu um objeto antes de sair da célula
                    if(inter.hit){
//                        std::cout<<"Y pode avançar..."<<std::endl;
//                        printVar(ix);
//                        printVar(iy);
//                        printVar(iz);
//                        std::cout<<"acerteeeei -------------------- "<<std::endl;
//                        printVar(inter.t < tyNext);
//                        printObjectPtr((inter.obj));
                    }
                    if(inter.hit && inter.t < tyNext)
                    {
//                        printObjectPtr(obj);
                        return inter;
                    }
                }
                tyNext += dty;
                iy+=iyStep;
//
//                prIdx("to perto? ---------- >", tyNext, dty, iyStep);
//                printVar(iy == iyStop);
                if(iy == iyStop)
                {
                    inter.hit = false;
                    return inter;
                }
            }
            else
            {
//                std::cout<<std::endl;
//                prIdx("Z pode avançar...",ix,iy,iz);
                if(obj) // Se célula não é vazia
                {
//                    std::cout<<"PIXELLLLL!!!!!!!!"<<(int)obj<<std::endl;
                    inter = obj->hit(r);
//                    std::cout<<"PIXELLLLL!!!!!!!!"<<std::endl;
                    // raio atingiu um objeto antes de sair da célula
//                    std::cout<<(inter.hit ? "acerteeeei" : "Erreeeei")<<std::endl;
//                    printVar(inter.t < tzNext);
                    if(inter.hit){
//                        std::cout<<"Z pode avançar..."<<std::endl;
//                        printVar(ix);
//                        printVar(iy);
//                        printVar(iz);
//                        std::cout<<"acerteeeei -------------------- "<<std::endl;
//                        printVar(inter.t < tyNext);
//                        printObjectPtr((inter.obj));
                    }
                    if(inter.hit && inter.t < tzNext)
                    {
//                        printObjectPtr(obj);
                        return inter;
                    }

                }
                tzNext += dtz;
                iz+=izStep;

//                prIdx("to perto? ---------- >", tzNext, dtz, izStep);
//                printVar(iz == izStop);

                if(iz == izStop)
                {
                    inter.hit = false;
                    return inter;
                }
            }

        }
    }
    else
    {
        //std::cout<<"ERROOOOOU!"<<std::endl;
        inter.hit = false;
        return inter;
    }

}

void Grid::setup()
{
    // pontos minimo e máximo da grid
    Vec3d p0 = minCoordinates();
    Vec3d p1 = maxCoordinates();

    // alterar bounding box
    bbox.setMinPoint(p0);
    bbox.setMaxPoint(p1);

    //computar o número de células

    int numObjs = objects.size();
    cout<<numObjs<<endl;
    float wx = p1.x - p0.x;
    float wy = p1.y - p0.y;
    float wz = p1.z - p0.z;
    float multiplier = 1.0;
    float s = pow(wx*wy*wz/numObjs, 0.3333333);
    nx = multiplier * wx / s + 1;
    ny = multiplier * wy / s + 1;
    nz = multiplier * wz / s + 1;

    // setup do array de células com ponteiros nulos

    int numCells = nx*ny*nz;
    cells.reserve(numCells);

    for(int j = 0; j < numCells; j++)
        cells.push_back(NULL);

    // array temporário para guardar o num de objs em cada célula

    std::vector<int> counts;
    counts.reserve(numCells);

    for(int j = 0; j < numCells; j++)
        counts.push_back(0);

    //armazenando objetos nas células

    BoundingBox objBB; // bounding box do objeto
    int index; //índice do array de células

    for(int j = 0; j < numObjs; j++)
    {
        objBB = objects[j]->getBoudingBox();
        Vec3d bbmin = objBB.getMinPoint();
        Vec3d bbmax = objBB.getMaxPoint();
        // calculando o índice das células que contêm os cantos da BBox do objeto
        int ixmin = clamp( (bbmin.x - p0.x)*nx/(p1.x - p0.x), 0, nx - 1 );
        int iymin = clamp( (bbmin.y - p0.y)*ny/(p1.y - p0.y), 0, ny - 1 );
        int izmin = clamp( (bbmin.z - p0.z)*nz/(p1.z - p0.z), 0, nz - 1 );
        int ixmax = clamp( (bbmax.x - p0.x)*nx/(p1.x - p0.x), 0, nx - 1 );
        int iymax = clamp( (bbmax.y - p0.y)*ny/(p1.y - p0.y), 0, ny - 1 );
        int izmax = clamp( (bbmax.z - p0.z)*nz/(p1.z - p0.z), 0, nz - 1 );

        // Adicionando o objeto às celulas

        for(int iz = izmin; iz <= izmax; iz++)
        for(int iy = iymin; iy <= iymax; iy++)
        for(int ix = ixmin; ix <= ixmax; ix++)
        {
            index = ix + nx *iy + nx*ny*iz;
            if(counts[index] == 0)
            {
                cells[index] = objects[j];
                counts[index] += 1;
            }
            else
            {
                if(counts[index] == 1)
                {
                    // cria um CompositeObject (um conjunto de objetos)
                    CompositeObject* comp = new CompositeObject();
                    // adiciona o objeto da célula ao conjunto
                    comp->addObject(cells[index]);
                    comp->addObject(objects[j]);
                    // adicionar o objeto composto à célula
                    cells[index] = comp;
                    counts[index]+=1;
                }
                else
                {
                    ((CompositeObject*)cells[index])->addObject(objects[j]);
                    counts[index] += 1;
                }
            }
        } // for ix, iy, iz

    } // for j

    objects.erase(objects.begin(), objects.end());
    /*
    for(int iz = 0; iz < nz; iz++)
    for(int iy = 0; iy < ny; iy++)
    for(int ix = 0; ix < nx; ix++)
    {
        int idx = ix + nx*iy + nx*ny*iz;
        printVar(ix);
        printVar(iy);
        printVar(iz);
        printVar(idx);
        printVar(counts[idx]);
    }
    */


	int num_zeroes 	= 0;
	int num_ones 	= 0;
	int num_twos 	= 0;
	int num_threes 	= 0;
	int num_greater = 0;

	for (int j = 0; j < numCells; j++) {
		if (counts[j] == 0)
			num_zeroes += 1;
		if (counts[j] == 1)
			num_ones += 1;
		if (counts[j] == 2)
			num_twos += 1;
		if (counts[j] == 3)
			num_threes += 1;
		if (counts[j] > 3)
			num_greater += 1;
	}

	cout << "num_cells =" << numCells << endl;
	cout << "numZeroes = " << num_zeroes << "  numOnes = " << num_ones << "  numTwos = " << num_twos << endl;
	cout << "numThrees = " << num_threes << "  numGreater = " << num_greater << endl;
    counts.erase(counts.begin(), counts.end());
}

void Grid::addObject(Object* o)
{
    objects.push_back(o);
}

BoundingBox Grid::getBoudingBox()
{
    return BoundingBox(minCoordinates(), maxCoordinates());
}

Vec3d Grid::maxCoordinates()
{
    BoundingBox bb;
    Vec3d p1 = Vec3d(-INFINITY);
    int nObjects = objects.size();
    printVar(nObjects);
    for(int i = 0; i < nObjects; i++)
    {
        bb = objects[i]->getBoudingBox();
        Vec3d maxp = bb.getMaxPoint();
        if (maxp.x > p1.x)
            p1.x = maxp.x;
        if (maxp.y > p1.y)
            p1.y = maxp.y;
        if (maxp.z > p1.z)
            p1.z = maxp.z;
    }
    p1.x += K_EPSILON;
    p1.y += K_EPSILON;
    p1.z += K_EPSILON;

    return p1;
}

Vec3d Grid::minCoordinates()
{
    BoundingBox bb;
    Vec3d p0 = Vec3d(INFINITY);

    int nObjects = objects.size();

    for(int i = 0; i < nObjects; i++)
    {
        bb = objects[i]->getBoudingBox();
        Vec3d minp = bb.getMinPoint();
        if (minp.x < p0.x)
            p0.x = minp.x;
        if (minp.y < p0.y)
            p0.y = minp.y;
        if (minp.z < p0.z)
            p0.z = minp.z;
    }
    p0.x -= K_EPSILON;
    p0.y -= K_EPSILON;
    p0.z -= K_EPSILON;

    return p0;
}


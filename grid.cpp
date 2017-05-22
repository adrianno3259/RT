#include "grid.h"
#include "math.h"

Grid::Grid() : bbox(BoundingBox(Vec3d(), Vec3d()))
{

}

Grid::~Grid()
{
    //dtor
}


bool Grid::hitGrid(const Ray& r)
{

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
    float wx = p1.x - p0.x;
    float wy = p1.y - p0.y;
    float wz = p1.z - p0.z;
    float multiplier = 2.0;
    float s = pow(wx*wy*wz/numObjs, 0.3333333);
    nx = multiplier * wx / s + 1;
    ny = multiplier * wy / s + 1;
    nz = multiplier * wz / s + 1;

    // setup do array de células com ponteiros nulos

    int numCells = nx*ny*nz;
    cells.reserve(numObjs);

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


    counts.erase(counts.begin(), counts.end());
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


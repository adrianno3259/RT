#include <iostream>
#include <cstdlib>

#include "color.h"
#include "vec3.h"
#include "image.h"
#include "ray.h"
#include "sphere.h"
#include <cmath>
#include "plane.h"

#include "camera.h"
#include "scene.h"
#include "material.h"
#include "matte.h"
#include "box.h"
#include "globals.h"


#include "mergehits.h"
#include "interval.h"

#include "csgnode.h"
#include "csgprimitive.h"
#include "csgoperation.h"
#include "csgobject.h"


#include <ctime>
#include "phong.h"
#include "reflective.h"

#include "boundingbox.h"
#include "grid.h"
#include "compositeobject.h"

#define printHitList(A)     cout<<"-------------------------"<<endl<<"inters "<<#A<<": "<<endl;        \
                            for(int l = 0; l < A.size(); l++)                                          \
                            {                                                                          \
                                printVar(l);                                                           \
                                printVec(A[l].hitPoint);                                               \
                                printVec(r.rayPoint(A[l].t));                                          \
                                cout<<A[l].t<<endl;                                                    \
                            }                                                                          \
                            cout<<endl<<endl;



#define DIFFUSE 0
#define SPECULAR 1
#define MIRROR 2

using namespace std;
/*
namespace debug
{
    void T_Color();
    void T_Vec3d();
    void T_Image();
    void T_Ray();
    void T_Sphere();
}*/


void startChrono();
double stopChrono();
//void setupCamera();

void objsLightsSetup();
void csgExemple();
void randomSpheres(int ns, int mat, float radius);
void camSceneSetup();
void render();

time_t timeT0, timeTf;
Camera CAMERA;
Scene SCENE;
Grid* g;
int VERTICAL_RES = 400;
int HORIZONTAL_RES = 400;
float ZOOM = 2;

int main(int argc, char** argv)
{

    cout<< "Iniciando setup..."<<endl;

    //startChrono();
    camSceneSetup();
    //csgExemple();

    int BM=5, Bm=-5, R=5;
    Vec3d bbmax = Vec3d(BM);
    Vec3d bbmin = Vec3d(Bm);

    g = new Grid();
    SCENE.useGrid(true);
    randomSpheres(25000, MIRROR, 10);
    printVar( g->objects.size());

    Box *b1 = new Box(bbmin+Vec3d(-10,0,0), bbmax+Vec3d(-10,0,0));
    Sphere *s2 = new Sphere(Vec3d(0), R);
    Sphere *s1 = new Sphere(Vec3d(10), R);
    Box *b2 = new Box(bbmin+Vec3d(10,0,0), bbmax+Vec3d(10,0,0));

    g->addObject(b1); g->addObject(b2);
    g->addObject(s1); g->addObject(s2);
    g->setup();
    printVar(g->nx); printVar(g->ny); printVar(g->nz);
    cout<< "BoundingBox b:"<<endl;
    printVec(g->bbox.getMinPoint());
    printVec(g->bbox.getMaxPoint());
    SCENE.addObject(g);
    printVar(SCENE.objects.size());




    //



//    printVar(b.inside(r));
//    printVar(b.inside(r2));
//    printVar(b.inside(r3));




    /*

    cout<< "BoundingBox b:"<<endl;
    printVec(bbmin);
    printVec(bbmax);
    BoundingBox b = BoundingBox(bbmin, bbmax);
    Ray r = Ray(Vec3d(0, 0, 0), Vec3d(1.0, 0.0, 0.0));
    Ray r2 = Ray(Vec3d(-9.99999, 0, 0), Vec3d(1.0, 0.0, 0.0));
    Ray r3 = Ray(Vec3d(-20, 0, 0), Vec3d(1.0, 0.0, 0.0));


    Vec3d min_point = Vec3d(-10);
    Vec3d max_point = Vec3d(10);
    Box* box = new Box(min_point, max_point);

    Color col = Color(1.0);



    CompositeObject* co = new CompositeObject();
    Sphere* s2 = new Sphere(Vec3d(1.0, 0, 0), 10);
    co->addObject(box);
    co->addObject(s2);
    Intersect it = (co->hit(r));
    printVec(it.hitPoint);



    g->objects.push_back(box);
    g->objects.push_back(s);
    printVec(g->minCoordinates());
    printVec(g->maxCoordinates());

    cout << "bounding box calculation: "<<endl;
    Ray r = Ray(Vec3d(-200, 0, 0), Vec3d(1.0, 0.0, 0.0));
    printRay(r);

    cout<<"hit: "<<boolalpha<<b.hit(r)<<endl;
    cout<< "Box bx:"<<endl;
    cout<<"hit: "<<boolalpha<<bx.hit(r).hit<<endl;

    r = Ray(Vec3d(-200, 0, 50), Vec3d(1.0, 0.0, 0.0));
    printRay(r);
    cout<<"hit bb: "<<boolalpha<<b.hit(r)<<endl;
    cout<<"hit bx: "<<boolalpha<<bx.hit(r).hit<<endl;
    */
    Light* l = new Light(Vec3d(100.0, 100.0, 100.0),
             2.0,
             Color(1.0));
    SCENE.addLight(l);
    Light* l1 = new Light(Vec3d(-500.0, -500.0, 500.0),
             1.0,
             Color(1.0));
    SCENE.addLight(l1);
    Light* l3 = new Light(Vec3d(500.0, 0.0, 0.0),
     1.0,
     Color(1.0));
    SCENE.addLight(l3);
    render();

    return 0;
}

void render()
{
    Image im = CAMERA.render(SCENE);
    im.save("image.ppm");
    system("start image.ppm");
}


void camSceneSetup()
{

    CAMERA = Camera(Vec3d(500, 500, 500.0),
            Vec3d(0, 0.0, 0.0),
            Vec3d(0.0, 0.0, 1.0),
            HORIZONTAL_RES,
            VERTICAL_RES,
            500.0);
    /*

    CAMERA = Camera(Vec3d(-25, 25, 20.0),
            Vec3d(0, 0.0, 0.0),
            Vec3d(0.0, 0.0, 1.0),
            HORIZONTAL_RES,
            VERTICAL_RES,
            500.0);
    */
    CAMERA.pixelSize /= ZOOM;

    // Setup da Cena

    SCENE = Scene();
    SCENE.bg = Color();

}

void csgExemple()
{


    //SCENE.setShadows(false);

    Color col = Color(0.3, 0.3, 0.3);
    Phong* spec = new Phong(Color(1.0, 0.3, 0.6));

    Reflective* reflect = new Reflective(Color(1.0, 0.5, 0.0));
    reflect->setKd(0.5);
    reflect->setCd(WHITE);
    reflect->setKs(0.8);
    reflect->setExp(20);
    reflect->setKr(0.9);
    reflect->setCr(WHITE);

    Phong* reflect2 = new Phong(Color(1.0, 0.5, 0.0));
    reflect2->setKd(.5);
    reflect2->setKs(0.15);
    reflect2->setCd(ORANGE);
    reflect2->setExp(30.0);


    ////////////////////////////////////////////////////////////////////////////////////
    // (b - s3) - s

    Sphere* s = new Sphere(Vec3d(-10.0, 0.0, 0.0), 8);
    Box* b = new Box(Vec3d(-23, -10, -10), Vec3d(-10, 10, 10));
    Sphere* s3 = new Sphere(Vec3d(-20.0, 0.0, 10.0), 5);

    CSGNode* node = new CSGPrimitive(s);
    CSGNode* node2 = new CSGPrimitive(b);
    CSGNode* node3 = new CSGPrimitive(s3);

    CSGNode* nodeOp1 = new CSGOperation(node2, node3, '-');
    CSGNode* nodeOp2 = new CSGOperation(nodeOp1, node, '-');

    CSGObject * obj = new CSGObject(nodeOp2);
    obj->m = reflect;//new Matte(col);
    SCENE.addObject(obj);

    ////////////////////////////////////////////////////////////////////////////////////

    Sphere* s2 = new Sphere(Vec3d(0.0, 0.0, 0.0), 6);
    Box* b2 = new Box(Vec3d(-5, -5, -5), Vec3d(5, 5, 5));

    CSGNode *box = new CSGPrimitive(b2);
    CSGNode *sph = new CSGPrimitive(s2);

    CSGNode *BSMinus = new CSGOperation(box, sph, '-');

    CSGObject* obj2 = new CSGObject(BSMinus);
    obj2->m = new Matte(Color(1.0, 0.0, 0.0));
    SCENE.addObject(obj2);

    ////////////////////////////////////////////////////////////////////////////////////


    Sphere* s5 = new Sphere(Vec3d(15.0, 0.0, 0.0), 6);
    Box* b5 = new Box(Vec3d(13, -2, -10), Vec3d(17, 2, 10));
    Box* b6 = new Box(Vec3d(13, -10, -2), Vec3d(17, 10, 2));

    CSGNode *sph2 = new CSGPrimitive(s5);
    CSGNode *box2 = new CSGPrimitive(b5);
    CSGNode *box3 = new CSGPrimitive(b6);

    CSGNode *BSMinus2 = new CSGOperation(sph2, box2, '-');
    CSGNode *BSMinus3 = new CSGOperation(BSMinus2, box3, '-');

    CSGObject* obj3 = new CSGObject(BSMinus3);
    obj3->m = reflect;// new Matte(Color(1.0, 1.0, 0.0));
    //SCENE.addObject(obj3);

    ///////////////////////////////////////////////////////////////////////////

    Plane* p = new Plane(Vec3d(0, 0, -11), Vec3d(0.0, 0.0, 1.0));
    p->m = new Matte(Color(1.0));
    SCENE.addObject(p);

    Sphere *sphere = new Sphere(Vec3d(0,0,15), 5);
    sphere->m = reflect2;
    //SCENE.addObject(sphere);

    Sphere *sphere2 = new Sphere(Vec3d(20,-20,15), 8);
    sphere2->m = reflect;
    SCENE.addObject(sphere2);
}

void randomSpheres(int ns, int mat, float r)
{
    int NUM_SPH = ns;
    //cin >> NUM_SPH;
    cout<<"Esferas: " << NUM_SPH<<endl;
    Sphere * s;


    for(int j = 0; j < NUM_SPH; j++)
    {
        srand(ns+j);
        float x = rand() % 400 - 200, y = rand() % 200 -100, z = rand() % 200 -100;
        float radius;
        Color col2 = Color(1.0, 0.0, (j%11)*0.1);
        if(r == 0)
        {
            srand(ns+2*j);
            radius = (rand() % 5) + 2;
        }
        else
            radius = r;

        s = new Sphere(Vec3d(x, y, z), radius);
        switch(mat)
        {
            case SPECULAR:
                s->m = new Phong(col2); break;
            case MIRROR:
                s->m = new Reflective(col2); break;
            case DIFFUSE:
            default:
                s->m = new Matte(col2); break;
        }
        if(SCENE.useGrid())
            g->addObject(s);
        else
            SCENE.addObject(s);
    }
}

void objsLightsSetup()
{


    int nObjs = 0, nLights = 0, i;

    /**
    **  Setup Objects
    **/

    cin>>nObjs;
    cout<<nObjs<<" objetos..."<<endl;
    for(i = 0; i < nObjs; i++)
    {
        string type;
        cin >> type;
        cout<<"objeto "<<i<<endl;
        if(type == "sphere")
        {
            /**
                sphere
                <center_coords>
                <radius>
                <color>
            **/
            float a, b, c, r;
            cin>>a>>b>>c;
            Vec3d center = Vec3d(a, b, c);
            cin>>r;
            cin>>a>>b>>c;
            Color col = Color(a, b, c);
            Sphere* s = new Sphere(center, r);
            s->c = col;
            s->m = new Matte(col);
            SCENE.addObject(s);
        }
        else if(type == "plane")
        {
            /**
                plane
                <point_coords>
                <plane_normal>
                <color>
            **/
            float a, b, c;
            cin>>a>>b>>c;
            Vec3d point = Vec3d(a, b, c);
            cin>>a>>b>>c;
            Vec3d normal = Vec3d(a, b, c);
            cin>>a>>b>>c;
            Color col = Color(a, b, c);
            Plane* p = new Plane(point, normal);
            p->c = col;
            p->m = new Matte(col);
            SCENE.addObject(p);
        }
        else if(type == "box")
        {
            /**
                box
                <min_point>
                <max_point>
                <color>
            **/
            float a, b, c;
            cin>>a>>b>>c;
            Vec3d min_point = Vec3d(a, b, c);
            cin>>a>>b>>c;
            Vec3d max_point = Vec3d(a, b, c);
            cin>>a>>b>>c;
            Color col = Color(a, b, c);
            Box* box = new Box(min_point, max_point);
            box->c = col;
            box->m = new Matte(col);
            SCENE.addObject(box);
        }

    }

    /**
    **  Setup Lights
    **/

    cin>>nLights;

    for(i = 0; i < nLights; i++)
    {
        string type;
        cin >> type;
        cout<<"Luz "<<i<<endl;
        if(type == "point")
        {
            float a, b, c, s;
            cin>>a>>b>>c;
            Vec3d pos = Vec3d(a, b, c);
            cin>>s;
            cin>>a>>b>>c;
            Color col = Color(a, b, c);
            Light* l = new Light(pos, s, col);
            SCENE.addLight(l);
        }
    }


}


void startChrono()
{
    time(&timeT0);
}

double stopChrono()
{
    time(&timeTf);
    return difftime(timeTf, timeT0);
}

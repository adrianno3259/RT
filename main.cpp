#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <typeinfo>
#include <string>
#include <sstream>

/************ UTILS ************/

#include "color.h"
#include "vec3.h"
#include "image.h"
#include "ray.h"

/************ OBJECTS ************/

// Simple objects

#include "sphere.h"
#include "plane.h"
#include "box.h"
#include "compositeobject.h"

// CSG Objects

#include "csgnode.h"
#include "csgprimitive.h"
#include "csgoperation.h"
#include "csgobject.h"
#include "mergehits.h"

/************ MATERIALS ************/

#include "material.h"
#include "matte.h"
#include "phong.h"
#include "reflective.h"

/************ CAMERA, SCENE & GLOBAL VARIABLES ************/

#include "globals.h"
#include "camera.h"
#include "scene.h"

/************ GRID ************/

#include "boundingbox.h"
#include "grid.h"


/************************ DEFINES ************************/

/************ MATERIALS ************/

#define MATERIAL_DIFFUSE 0
#define MATERIAL_SPECULAR 1
#define MATERIAL_MIRROR 2


/************ USE MODES ************/


#define MODE_RANDOM_SPHERES 0
#define MODE_CSG_EXAMPLE 1
#define MODE_RANDOM_BOXES 2
#define MODE_RANDOM_BOX_SPHERE 3
#define MODE_CUSTOM 4

using namespace std;

void startChrono();
double stopChrono();

void objsLightsSetup();
void csgExemples();
void randomSpheres(int ns, int mat, float radius);
void camSceneSetup();
void render(const string& s);
void errorExit(const string& message);

// Global

time_t timeT0, timeTf;
Camera CAMERA;
Scene SCENE;
Grid* g;

int HORIZONTAL_RES = 600;
int VERTICAL_RES = 600;
float ZOOM = 1.5;

int mode;
bool useGrid;
int nObjects;
bool shadows;
int material;

int main(int argc, char** argv)
{

    cerr<< "Iniciando setup..."<<endl;

    camSceneSetup();

    cin>>mode;
    cin>>useGrid;
    cin>>material;
    cin>>shadows;
    cin>>nObjects;

    printVar(mode);
    printVar(useGrid);
    printVar(material);
    printVar(shadows);
    printVar(nObjects);

    SCENE.setShadows(shadows);

    if(useGrid)
    {
        g = new Grid();
        SCENE.useGrid(useGrid);
        randomSpheres(nObjects, material, 20);
        g->setup();
        SCENE.addObject(g);
    }
    else randomSpheres(nObjects, material, 20);

    Light* l = new Light(Vec3d(700.0, 700.0, 700.0),
             2.0,
             Color(1.0));
    SCENE.addLight(l);

    Light* l1 = new Light(Vec3d(-700.0, -700.0, 700.0),
             1.0,
             Color(1.0));
    SCENE.addLight(l1);

    Light* l3 = new Light(Vec3d(0.0, 0.0, 700.0),
             1.0,
             Color(1.0));
    SCENE.addLight(l3);

    startChrono();

    string fname;
    ostringstream conv;
    conv<<"image_"<<useGrid<<"_"<<material<<"_"<<shadows<<"_"<<nObjects;
    fname = conv.str();
    std::cout<<" BEFORE RENDER ------------------------------------"<<std::endl;
    render(fname);
    std::cout<<" AFTER RENDER ------------------------------------"<<std::endl;

    double t = stopChrono();

    cout<<"Tempo: "<<t<<"s "<<endl;
    cerr<<"Tempo: "<<t<<"s "<<endl;

    return 0;
}

void render(const string& n)
{
    string name = n;
    name+=".ppm";
    std::cout<<" RENDER BG ------------------------------------"<<std::endl;
    Image im = CAMERA.render(SCENE);
    std::cout<<" RENDER ------------------------------------"<<std::endl;
    im.save(name.c_str());
    std::cout<<" RENDER END ------------------------------------"<<std::endl;
    //system("start image.ppm");
}

void camSceneSetup()
{

    CAMERA = Camera(Vec3d(500, 500, 500),
            Vec3d(0, 0.0, 0.0),
            Vec3d(0.0, 0.0, 1.0),
            HORIZONTAL_RES,
            VERTICAL_RES,
            500.0);

/*
    CAMERA = Camera(Vec3d(0, 20, 15.0),
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


    SCENE.setShadows(false);

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
    //SCENE.addObject(obj);

    ////////////////////////////////////////////////////////////////////////////////////

    Sphere* s2 = new Sphere(Vec3d(0.0, 0.0, 0.0), 6);
    Box* b2 = new Box(Vec3d(-5, -5, -5), Vec3d(5, 5, 5));

    CSGNode *box = new CSGPrimitive(b2);
    CSGNode *sph = new CSGPrimitive(s2);

    CSGNode *BSMinus = new CSGOperation(box, sph, '-');

    CSGObject* obj2 = new CSGObject(BSMinus);
    obj2->m = new Matte(Color(1.0, 0.0, 0.0));
    //SCENE.addObject(obj2);

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
    SCENE.addObject(sphere);

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
        float x = rand() % 600 - 300, y = rand() % 800 - 400, z = rand() % 800 - 400;
        float radius;
        Color col2 = Color(1.0, 0.0, (j%11)*0.1);
        if(r == 0)
        {
            srand(ns+2*j);
            radius = ((rand() % 2) + 5);
        }
        else
            radius = r;

        s = new Sphere(Vec3d(x, y, z), radius);
        switch(mat)
        {
            case MATERIAL_SPECULAR:
                s->m = new Phong(col2); break;
            case MATERIAL_MIRROR:
                s->m = new Reflective(col2); break;
            case MATERIAL_DIFFUSE:
            default:
                s->m = new Matte(col2); break;
        }
        if(useGrid)
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


void errorExit(const string& msg)
{

    cerr << "Erro: "<<endl;
    cerr << msg <<endl;
    exit(EXIT_FAILURE);

}

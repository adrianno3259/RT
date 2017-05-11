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

#include "phong.h"


#define printHitList(A)     cout<<"-------------------------"<<endl<<"inters "<<#A<<": "<<endl;        \
                            for(int l = 0; l < A.size(); l++)       \
                            {                                       \
                                printVar(l);                        \
                                printVec(A[l].hitPoint);             \
                                printVec(r.rayPoint(A[l].t));       \
                                cout<<A[l].t<<endl;                 \
                            } cout<<endl<<endl;



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
void objsLightsSetup();
void csgExemple();
void randomSpheres(int ns);
void camSceneSetup();

Camera CAMERA;
Scene SCENE;
int VERTICAL_RES = 800;
int HORIZONTAL_RES = 800;
float ZOOM = 0.7;

int main(int argc, char** argv)
{
    int i;


    camSceneSetup();
    csgExemple();
    randomSpheres(200);

    Light* l = new Light(Vec3d(100.0, 100.0, 100.0),
             1.0,
             Color(1.0));
    SCENE.addLight(l);
    Light* l1 = new Light(Vec3d(-100.0, -100.0, 100.0),
             0.5,
             Color(1.0));
    SCENE.addLight(l1);





    Image im = CAMERA.render(SCENE);
    im.save("image.ppm");
    system("start image.ppm");
    return 0;
}



void camSceneSetup()
{
    CAMERA = Camera(Vec3d(20, 20, 20.0),
                Vec3d(0, 0.0, 0.0),
                Vec3d(0.0, 0.0, 1.0),
                HORIZONTAL_RES,
                VERTICAL_RES,
                500.0);

    CAMERA.pixelSize /= ZOOM;
    SCENE = Scene();
    SCENE.bg = Color();
}

void csgExemple()
{
    Color col = Color(0.3, 0.3, 0.3);



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
    obj->m = new Matte(col);
    SCENE.addObject(obj);

    ////////////////////////////////////////////////////////////////////////////////////

    Sphere* s2 = new Sphere(Vec3d(0.0, 0.0, 0.0), 6);
    Box* b2 = new Box(Vec3d(-5, -5, -5), Vec3d(5, 5, 5));

    CSGNode *box = new CSGPrimitive(b2);
    CSGNode *sph = new CSGPrimitive(s2);

    CSGNode *BSMinus = new CSGOperation(box, sph, '-');

    CSGObject* obj2 = new CSGObject(BSMinus);
    obj2->m = new Matte(Color(0.0, 0.0, 1.0));
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
    obj3->m = new Matte(Color(1.0, 1.0, 0.0));
    SCENE.addObject(obj3);

    ///////////////////////////////////////////////////////////////////////////

    Plane* p = new Plane(Vec3d(0, 0, -11), Vec3d(0.0, 0.0, 1.0));
    p->m = new Matte(Color(1.0));
    SCENE.addObject(p);

    Sphere *sphere = new Sphere(Vec3d(0,0,15), 5);
    sphere->m = new Phong(Color(1.0, 0.3, 0.6));
    SCENE.addObject(sphere);
}

void randomSpheres(int ns)
{
    int NUM_SPH = ns;
    cin >> NUM_SPH;
    cout<<"Esferas: " << NUM_SPH<<endl;
    Sphere * s;
    for(int j = 0; j < NUM_SPH; j++)
    {
        float x = rand() % 200 -100, y = rand() % 200 -100, z = rand() % 200 -100;
        Color col2 = Color(1.0, 0.0, (j%11)*0.1);
        s = new Sphere(Vec3d(x, y, z), 3);
        s->m = new Material(col2);
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


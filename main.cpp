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
#include "box.h"
#include "globals.h"


#include "mergehits.h"

#include "interval.h"

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


Camera CAMERA;
Scene SCENE;
int VERTICAL_RES = 800;
int HORIZONTAL_RES = 800;
float ZOOM = 1.0;

int main(int argc, char** argv)
{
    int i;

    CAMERA = Camera(Vec3d(150.0, 0.0, 0.0),
                    Vec3d(),
                    Vec3d(0.0, 0.0, 1.0),
                    HORIZONTAL_RES,
                    VERTICAL_RES,
                    200.0);


    Color col = Color(1.0, 0.0, 0.0);

    Sphere* s = new Sphere(Vec3d(-10.0, 0.0, 0.0), 5);
    s->c = col;
    s->m = new Material(col);

    Box* b = new Box(Vec3d(-20, -5, -5), Vec3d(-10, 5, 5));
    b->c = col;
    b->m = new Material(col);


    Sphere* s2 = new Sphere(Vec3d(0.0, 0.0, 0.0), 2);
    s2->c = col;
    s2->m = new Material(col);


    Box* b2 = new Box(Vec3d(5,-10,-10), Vec3d(15, 10, 10));
    b2->c = col;
    b2->m = new Material(col);


    Sphere* s3 = new Sphere(Vec3d(-15.0, 0.0, 0.0), 2);
    s3->c = col;
    s3->m = new Material(col);


    Ray r = Ray(Vec3d(-25.0, 0.0, 0.0), Vec3d(1.0, 0.0, 0.0));

    vector<Intersect> v1 = b->hitList(r);
    vector<Intersect> v2 = s->hitList(r);
    vector<Intersect> v4 = b2->hitList(r);
    vector<Intersect> v3 = s2->hitList(r);
    vector<Intersect> v5 = s3->hitList(r);

    cout<<"inters v1 :"<<endl;
    for(int l = 0; l < v1.size(); l++)
    {
        printVar(l);
        cout<<v1[l].t<<endl;
        printVec(v1[l].normal);
    }
    cout<<"inters v2:"<<endl;
    for(int l = 0; l < v2.size(); l++)
    {
        printVar(l);
        cout<<v2[l].t<<endl;
        printVec(v2[l].normal);
    }
    cout<<"inters v3 :"<<endl;
    for(int l = 0; l < v1.size(); l++)
    {
        printVar(l);
        cout<<v3[l].t<<endl;
        printVec(v3[l].normal);
    }
    cout<<"inters v4:"<<endl;
    for(int l = 0; l < v4.size(); l++)
    {
        printVar(l);
        cout<<v4[l].t<<endl;
        printVec(v4[l].normal);
    }

    vector<Intersect> vr = MergeHits::csg_and(v1, v2);
    cout<<"inters:"<<endl;
    for(int l = 0; l < vr.size(); l++)
    {
        printVar(l);
        cout<<vr[l].t<<endl;
        printVec(vr[l].normal);
    }

/*



    vr = MergeHits::csg_or(vr, v3);
    cout<<"inters:"<<endl;
    for(int l = 0; l < vr.size(); l++)
    {
        printVar(l);
        cout<<vr[l].t<<endl;
        printVec(vr[l].normal);
    }



    vr = MergeHits::csg_or(vr, v4);
    vr = MergeHits::csg_or(vr, v5);
    cout<<"inters:"<<endl;
    for(int l = 0; l < vr.size(); l++)
    {
        printVar(l);
        cout<<vr[l].t<<endl;
        printVec(vr[l].normal);
    }
*/
    SCENE = Scene();
    SCENE.bg = Color();
////

    Light* l = new Light(Vec3d(100.0, 100.0, 100.0),
             1.0,
             Color(1.0));
    //printLight((*l));
    SCENE.addLight(l);


    int nObjs = 0, nLights = 0;
    /**
    **  Setup Objects
    **/

    //cin>>nObjs;
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
            s->m = new Material(col);
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
            p->m = new Material(col);
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
            box->m = new Material(col);
            SCENE.addObject(box);
        }

    }

    /**
    **  Setup Lights
    **/

    //cin>>nLights;

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
    Image im = CAMERA.render(SCENE);
    im.save("image.ppm");
    //cout<<true<<endl; system("start image.ppm");
    return 0;
}


void testScene()
{
    Sphere* s = new Sphere(30.0);
    Color col = Color(1.0, 0.0, 0.0);
    s->c = col;
    s->m = new Material(col);
    SCENE.addObject(s);


    Sphere* s2 = new Sphere(Vec3d(0.0, 100.0, 0.0),
                            30.0);
    Color col2 = Color(1.0, 1.0, 0.0);
    s2->c = col2;
    s2->m = new Material(col2);
    SCENE.addObject(s2);


    Sphere* s3 = new Sphere(Vec3d(0.0, -100.0, 0.0),
                            30.0);
    Color col3 = Color(1.0, 1.0, 1.0);
    s3->c = col2;
    s3->m = new Material(col3);
    SCENE.addObject(s3);


    Sphere* s4 = new Sphere(Vec3d(0.0, 0.0, 90.0),
                            30.0);
    Color col4 = Color(1.0, 0.0, 1.0);
    s4->c = col2;
    s4->m = new Material(col4);
    SCENE.addObject(s4);


    Sphere* s5 = new Sphere(Vec3d(0.0, 0.0, -90.0),
                            40.0);
    s5->c = col2;
    s5->m = new Material(col2);
    SCENE.addObject(s5);



    Light* l2 = new Light(Vec3d(100.0, 0.0, 0.0),
                     1.0,
                     Color(1.0));
    printLight((*l2));
    SCENE.addLight(l2);

    Light* l = new Light(Vec3d(100.0, 0.0, 100.0),
                 1.0,
                 Color(1.0));
    printLight((*l));
    SCENE.addLight(l);


}


/*
void debug::T_Color()
{
    Color red = Color(1.0, 0.0, 0.0);
    Color white = Color(1.0);
    Color black = Color();
    Color red2 = Color(red);
    Color white2 = white;

    printCol(red);
    printCol(white);
    printCol(black);

    printCol(red2);
    printCol(white2);
    printCol(red+black);
    printCol(white * 0.5);
    printCol(white-red);
    printCol(red/2);
}

void debug::T_Vec3d()
{
        Vec3d zero = Vec3d(),
            v1 = Vec3d(1.0),
            X = Vec3d(1.0, 0.0, 0.0),
            X2 = Vec3d(X),
            v2 = v1;
    QP(-----------------------------------Vec3d-----------------------------------------);
    //constructors + assignment
    printVec(zero);
    printVec(v1);
    printVec(X);
    printVec(X2);
    printVec(v2);
    //printVectors(5, &zero, &v1, &X, &X2, &v2);
    // menos unário --------
    QP(Menos unário);
    printVec(-v1);
    // produto por escalar --------
    QP(Produto por escalar);
    Vec3d tmp = 2*X;
    printVec(2*X);
    printVec(X*2);
    // divisão por escalar
    QP(Divisão por escalar);
    printVec(X/2);
    //soma
    QP(Soma);
    printVec(v1+X);
    //soma e atribuição
    QP(Soma e atribuição);
    v2 += X;
    printVec(v2);
    //subtração
    QP(Subtração);
    printVec(v2 - X);
    printVec(X - v2);
    // Dot
    QP(Dot Product);
    cout<<(X*v1)<<endl;
    //cross
    Vec3d c1 = Vec3d(3, -3, 1), c2 = Vec3d(4, 9, 2);
    QP(Cross Product);
    QP(Expected Result: (-15, -2, 39));
    printVec(c1 ^ c2);
}

void debug::T_Image()
{
    QP(--------------------------------------image----------------------------------------);
    Image im = Image();
    for(int i = 0; i < im.w; i++)
    for(int j = 0; j < im.h; j++)
    {
        //cout<<"i = "<<i <<" j = "<<j<<endl;
        //printCol(im.getPixel(i, j));
        if( (int)sqrt(i*i + j*j) % 40 > 35 || (int)sqrt(i*i + j*j) % 40 <10)
            im.setPixel(i, j, Color(2.0, 2.0, 2.0));
    }
    im.save("teste.ppm");
}

void debug::T_Ray()
{
    QP(-------------------------------------- Ray ----------------------------------------);
    Vec3d o1 = Vec3d(1.0), d1 = Vec3d(1.0);
    d1.normalize();
    printVec(o1); printVec(d1);
    Ray r1 = Ray(o1, d1), r2 = Ray(), r3 = Ray(r1), r4 = r2;
    printRay(r1); printRay(r2);
    printRay(r3); printRay(r4);

}

void debug::T_Sphere()
{

    QP(--------------------------------------Sphere----------------------------------------);
    Vec3d v1(1.0, 0.0, 0.0);
    float r1 = 1.0;
    Ray r = Ray(Vec3d(-2.0, 0.0, 0.0), Vec3d(1.0, 0.0, 0.0));
    Intersect i;

    Sphere s1 = Sphere(v1, r1), s2 = Sphere();
    printRay(r);
    printObject((s1));
    printObject(s2);
    //cout<<"hit s1: "<<s1.hit(r, i)<<endl;
    printInters(i);
    printVec(r.rayPoint(i.t));
    printVec(s1.getNormal(r.rayPoint(i.t)));

}
*/





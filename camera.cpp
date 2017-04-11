#include "camera.h"
#include "material.h"


Camera::Camera(){};
Camera::Camera(const Vec3d& e, const Vec3d& l, const Vec3d& upv, const int hr, const int vr, const float vpd)
/*                          |               |                |              |             |               |
                            |               |                |              |             |               +--> Viewplane distance
                            |               |                |              |             +------------------> vertical resolution
                            |               |                |              +--------------------------------> horizontal res
                            |               |                +-----------------------------------------------> up vector
                            |               +----------------------------------------------------------------> look point
                            +--------------------------------------------------------------------------------> eye point
*/
{

    hres = hr;
    vres = vr;
    lookpt = l;
    eye = e;
    up = upv;
    dist = vpd;

    //printVar(hres);printVar(vres);
    //printVec(eye);
    //printVec(lookpt);

    pixelSize = 1.0;

    lookDirection = l - e;
    lookDirection.normalize();

    w = -lookDirection; //(eye - lookpt);
    //printVec(w);
    w.normalize();
    //printVec(w); printVec(up);
    u = up ^ w;
    u = -u;
    //u = Vec3d(up.y * w.z - up.z * w.y, up.z * w.x - up.x * w.z, up.x * w.y - up.y * w.x);
    u.normalize();
    v = w ^ u;

    printVec(u);
    printVec(v);

}

Ray Camera::generateRay(const int r, const int c) const
{
    float x = pixelSize*(c - 0.5*hres);
    float y = pixelSize*(r - 0.5*vres);
    //printVar(x); printVar(y);
    Vec3d origin, direction;

    direction = x*u + y*v - dist * w;
    direction.normalize();
    //printVec(direction);

    Ray ray = Ray(eye, direction);
    //printRay(ray);
    return ray;
}

Image Camera::render(const Scene& sc){

    Ray R; //ray
    // int depth; // para reflexão especular
    Color L; // pixel color
    Intersect intersect;
    Image i = Image(hres, vres);

    for(int r = 0; r < vres; r++)
    for(int c = 0; c < hres; c++)
    {

        L = Color();
        R = generateRay(r, c);
        intersect = sc.hitObject(R);

        if(intersect.hit)
        {
            //printVar(r); printVar(c);
            L = intersect.m->shade(sc, intersect);
        }
        else
            L = intersect.c;

        i.setPixel(r, c, L.clamp());
    }

    return i;
}

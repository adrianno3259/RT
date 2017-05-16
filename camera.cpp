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
    pixelSize = 1.0;
    lookDirection = l - e;
    lookDirection.normalize();
    w = -lookDirection;
    w.normalize();
    u = up ^ w;
    u = -u;
    u.normalize();
    v = w ^ u;
}

Ray Camera::generateRay(const int r, const int c) const
{
    float x = pixelSize*(c - 0.5*hres);
    float y = pixelSize*(r - 0.5*vres);
    Vec3d origin, direction;
    direction = x*u + y*v - dist * w;
    direction.normalize();
    Ray ray = Ray(eye, direction);
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
        if(r%50 == 0 && c%50 == 0){ printVar(r); printVar(c);}

        if(intersect.hit)
        {
            L = intersect.m->shade(sc, intersect);
        }
        else
            L = intersect.c;

        i.setPixel(r, c, L.clamp());
    }

    return i;
}

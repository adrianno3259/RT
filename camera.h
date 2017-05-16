#ifndef CAMERA_H
#define CAMERA_H

#include "vec3.h"
#include "scene.h"
#include "ray.h"
#include "image.h"


class Camera
{
public:
    Vec3d eye, lookpt, lookDirection, up, gaze, u, v, w;
    int hres, vres, samples;
    float pixelSize, dist, exposure;
    Image img;
    Camera();
    Camera(const Vec3d& e, const Vec3d& l, const Vec3d& upv, const int hr, const int vr, const float vpd);
    Ray generateRay(const int r, const int c) const;
    Image render(const Scene& sc);
private:
    static const int INIT_DEPTH = 0;

};

#endif // CAMERA_H

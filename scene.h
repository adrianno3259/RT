#ifndef SCENE_H
#define SCENE_H

#include "color.h"
#include "object.h"
#include "light.h"
#include <vector>

//class Object;
//class Light;

class Scene
{
public:
    Color bg;
    std::vector <Object*> objects;
    std::vector <Light*> lights;

    Scene();
    void addObject(Object* o);
    void addLight(Light* l);
    Intersect hitObject(const Ray& ray) const;
    bool lightHitsPoint(int lightId, const Intersect& it, float dist) const;

    Color traceRay(const Ray& ray) const;
    Color traceRayWhitted(const Ray& ray, const int depth) const;

    void setShadows(bool v);

private:
    bool shadows = true;
    static const int MAX_DEPTH = 4;
};

#endif // SCENE_H

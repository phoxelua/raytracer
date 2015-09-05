#pragma once
#include "stdafx.h"
#include "Shape.h"
#include "Light.h"
#include "Camera.h"
#include "Film.h"
#include "Transformation.h"



class Scene {
public:
    std::list<Shape*> allShapes;
    std::list<DirLight> allDirLights;
    std::list<PtLight> allPtLights;
    Camera camera;
    Film film;
    Transformation transformation;
    int depth, distrib, aaFactor;
    bool environment, antialiasing;


    cimg_library::CImg<double> front, back, top, bottom, left, right;

    Scene();
    Scene(int depth, int distrib = 4, int apR=50);
    void render();
    bool closestIntersect(Ray& ray, float& minT, Intersection& closest);
    bool closestIntersect(Ray& ray);
    vec2 computeUV(double a, double b, double c);
    vec3 cubeMap(vec3& ray);
    void raytrace(Ray& ray, int depth, vec3* color);
    vec3 phongShading(Material mat, Intersection intersect);

    void debug();

};


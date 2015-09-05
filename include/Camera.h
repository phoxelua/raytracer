#pragma once
#include "stdafx.h"
#include "Ray.h"
class Camera {
public:
    vec3 lookFrom, lookAt;
    vec3 upperLeft, upperRight, lowerLeft, lowerRight;
    vec3 up, hBasis, vBasis;
    float fov, width, height, focalDist, apR;
    vec3 apX, apY;
    Camera() {};
    Camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fov, float width, float height, float apR=0.0);

    void setBoundaries();
    Ray generateRay(vec3 s);
    vec3 getPixel(float i, float j);
};


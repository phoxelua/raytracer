#pragma once
#include "stdafx.h"
#include "Intersection.h"
#include "Ray.h"

//class Light {
//    public:
//        vec3 color;
//        vec3 pos;
//        Light(vec3, vec3);
//		virtual void generateLightRay(Intersection& intersect, Ray* ray, vec3* color){}
//
//};


class PtLight {
public:
    vec3 color;
    vec3 pos;
    PtLight(vec3 c, vec3 p);
    void generateLightRay(Intersection& intersect, Ray* ray, vec3* color);
};

class DirLight {
public:
    vec3 color;
    vec3 dir;
    DirLight(vec3 c, vec3 v);
    void generateLightRay(Intersection& intersect, Ray* ray, vec3* color);
};


#pragma once
#include "stdafx.h"

class Ray {
public:
    vec3 pos;
    vec3 dir;
    float tMin, tMax;
    Ray() {}
    Ray(vec3 pos, vec3 dir, float tMin, float tMax);
    vec3 evaluate(float t);
};


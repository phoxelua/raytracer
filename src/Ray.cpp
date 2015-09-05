#include "stdafx.h"
#include "Ray.h"


Ray::Ray(vec3 pos, vec3 dir, float tMin, float tMax) {
    this->pos = pos;
    this->dir = dir.normalize();
    this->tMin = tMin;
    this->tMax = tMax;
}

vec3 Ray::evaluate(float t) {
    if (t <= this->tMin || t >= this->tMax) {
        std::cout << "Bad t, outside of bounds for ray" << std::endl;
        exit(1);
    } else {
        return this->pos + (this->dir*t);
    }
}
#pragma once
#include "stdafx.h"


class Shape;

class Intersection {
public:
    vec3 normal;
    vec3 point;
    Shape* shape;
    Intersection() {};
    Intersection(vec3 normal, vec3 point, Shape* shape);
};


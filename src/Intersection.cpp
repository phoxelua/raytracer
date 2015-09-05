#include "stdafx.h"
#include "Intersection.h"


Intersection::Intersection(vec3 normal, vec3 point, Shape* shape) {
    this->normal = normal.normalize();
    this->point = point;
    this->shape = shape;
}

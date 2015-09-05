#pragma once
#include "stdafx.h"


class Material {
public:
    vec3 ambient, diffuse, specular, reflect, emissive, refract;
    float coeff, indexRefract;
    Material() {};

    Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 reflect, float coeff,
             vec3 emissive = vec3(0,0,0), vec3 refract = vec3(0,0,0), float indexRefract = 50);
};


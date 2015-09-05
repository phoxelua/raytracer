#include "stdafx.h"
#include "Material.h"


Material::Material(vec3 ambient, vec3 diffuse, vec3 specular, vec3 reflect, float coeff,
                   vec3 emissive, vec3 refract, float indexRefract) {
    this->ambient = ambient;
    this->diffuse = diffuse;
    this->specular = specular;
    this->reflect = reflect;
    this->coeff = coeff;
    this->emissive = emissive;
    this->refract = refract;
    this->indexRefract = indexRefract;
}


#include "stdafx.h"
#include "Light.h"


//Light::Light(vec3 c, vec3 v) {
//	this->color = c;
//	this->pos = v;
//}

PtLight::PtLight(vec3 c, vec3 p) {
    this->color = c;
    this->pos = p;
}

void PtLight::generateLightRay(Intersection& intersect, Ray* ray, vec3* color) {
    vec3 local = intersect.point;
    ray->pos = local;
    ray->dir = (this->pos - local).normalize();
    ray->tMin = 0.8;
    ray->tMax = (this->pos - local).length(); //distance
    *color = this->color;
}

DirLight::DirLight(vec3 c, vec3 v) {
    this->color = c;
    this->dir = v.normalize();
}

void DirLight::generateLightRay(Intersection& intersect, Ray* ray, vec3* color) {
    ray->pos = intersect.point;
    ray->dir = this->dir.normalize();
    ray->tMin = 0.8; //might have to adjust epsilon
    ray->tMax = POS_INF;
    *color = this->color;
}

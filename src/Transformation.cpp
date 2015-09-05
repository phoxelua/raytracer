#include "stdafx.h"
#include "Transformation.h"


Transformation::Transformation() {
    this->transform = mat4(vec4(1,0,0,0), vec4(0,1,0,0), vec4(0,0,1,0), vec4(0,0,0,1));
    this->transformI = this->transform; // inverse
    this->transformTI = this->transform; //transpose of inverse
}

void Transformation::push() {
    pastTransform.push(transform);
}

void Transformation::pop() {
    this->transform = pastTransform.top();
    this->transformI = this->transform.inverse();
    this->transformTI = this->transformI.transpose();
    pastTransform.pop();
}

void Transformation::translate(vec3 offset) {
    this->transform = transform * translation3D(offset);
    this->transformI = this->transform.inverse();
    this->transformTI = this->transformI.transpose();
}

void Transformation::scale(vec3 scale) {
    this->transform = transform * scaling3D(scale);
    this->transformI = this->transform.inverse();
    this->transformTI = this->transform.inverse().transpose();
}

void Transformation::rotate(vec3 axis, float angle) {
    this->transform = transform * rotation3D(axis, angle);
    this->transformI = this->transform.inverse();
    this->transformTI = this->transformI.transpose();
}

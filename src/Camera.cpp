#include "stdafx.h"
#include "Camera.h"



Camera::Camera(vec3 lookFrom, vec3 lookAt, vec3 up, float fov,
               float width, float height, float apR) {
    this->lookFrom = lookFrom;
    this->lookAt = lookAt;
    this->up = up;
    this->fov = fov*PI/180;
    this->apR = apR;
    this->width = width;
    this->height = height;
    if (this->fov > PI || this->fov < 0.0) {
        std::cout << "BAD FOV" << std::endl;
        exit(0);
    }
    this->setBoundaries();
}

void Camera::setBoundaries() {
    vec3 viewDirection = this->lookAt - this->lookFrom;
    this->focalDist = viewDirection.length();
    this->hBasis = (viewDirection^this->up).normalize();
    this->vBasis = (hBasis^viewDirection).normalize();
    float halfHeight = tan(this->fov/2) * focalDist;
    float aspectRatio =  this->width / this->height;
    float halfWidth = aspectRatio * halfHeight;

    this->apX = hBasis * this->apR;
    this->apY = vBasis * this->apR;
    this->upperLeft = this->lookAt + vBasis*halfHeight - hBasis*halfWidth;//flipped these
    this->upperRight = this->lookAt + vBasis*halfHeight + hBasis*halfWidth;
    this->lowerLeft = this->lookAt - vBasis*halfHeight -hBasis*halfWidth;
    this->lowerRight = this->lookAt - vBasis*halfHeight + hBasis*halfWidth;
}


Ray Camera::generateRay(vec3 pos) {
    float randx = (rand() / float(RAND_MAX)) * 2 - 1;
    float randy = (rand() / float(RAND_MAX)) * 2 - 1;
    vec3 randEye = this->lookFrom + this->apX*randx + this->apY*randy;
    return Ray(randEye, (pos - randEye).normalize(), 1,POS_INF);
}

vec3 Camera::getPixel(float i, float j) {
    float u = float(i+.5)/width;
    float v = float(j+.5)/height;
    return u*(v*lowerLeft+(1-v)*upperLeft)+(1-u)*
           (v*lowerRight+(1-v)*upperRight);
}

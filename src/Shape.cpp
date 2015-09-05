#include "stdafx.h"
#include "Shape.h"



Shape::Shape(void) {
}

Sphere::Sphere(vec3 center, float radius, Transformation& transformation, float velocity) {
    this->transform = transformation.transform;
    this->transformI = transformation.transformI;
    this->transformTI = transformation.transformTI;
    this->isSphere = true;
    this->center = center;
    this->radius = radius;
    this->material = Material(vec3(0.2,0.2,0.2), vec3(0,0,0), vec3(0,0,0), vec3(0,0,0), 1);
    this->velocity = velocity;
    this->originalCenter = center;
}

Sphere::Sphere(vec3 center, float radius, Material material, Transformation& transformation, float velocity) {
    this->transform = transformation.transform;
    this->transformI = transformation.transformI;
    this->transformTI = transformation.transformTI;
    this->isSphere = true;
    this->center = center;
    this->radius = radius;
    this->material = material;
    this->velocity = velocity;
    this->originalCenter = center;
}

bool Sphere::intersect(Ray& ray, float& tHit, Intersection* intersect) {
    vec3 e = ray.pos;
    vec3 d = ray.dir;

    float a = d*d;
    float b = 2*d*(e - this->center);
    float c = (e - this->center)*(e - this->center) - this->radius*this->radius;

    if (a == 0) {
        std::cout << "Ray is just a point!" << std::endl;
        return false;
    }

    float discriminant = b*b - 4*a*c;

    //float tMin = std::numeric_limits<float>::max();
    if (discriminant >= 0) {
        float tPos = (-b + sqrt(discriminant)) / (2.0f*a);
        float tNeg = (-b - sqrt(discriminant)) / (2.0f*a);

        tHit = /*(tNeg<0 && tPos>0)? tPos :*/ tNeg;
        if (tHit >= ray.tMax || tHit <= ray.tMin) return false;

        intersect->point = vec3(transform * vec4(ray.evaluate(tHit),1),VW);
        intersect->normal  = vec3(transformTI * vec4(intersect->point - this->center, 0),VW).normalize();
        //if (tNeg<0 && tPos>0) {
        //	intersect->normal = -1*intersect->normal;
        //}
        intersect->shape = this;
        return true;
    }
    return false;
}

bool Sphere::intersect(Ray& ray) {
    vec3 e = ray.pos;
    vec3 d = ray.dir;

    float tHit = POS_INF;

    float a = d*d;
    float b = 2*d*(e - this->center);
    float c = (e - this->center)*(e - this->center) - this->radius*this->radius;

    if (a == 0) {
        std::cout << "Ray is just a point!" << std::endl;
        return false;
    }

    float discriminant = b*b - 4*a*c;

    //float tMin = std::numeric_limits<float>::max();
    if (discriminant >= 0) {
        float tPos = (-b + sqrt(discriminant)) / (2.0f*a);
        float tNeg = (-b - sqrt(discriminant)) / (2.0f*a);

        tHit = /*(tNeg<0 && tPos>0)? tPos :*/ tNeg;
        if (tHit >= ray.tMax || tHit <= ray.tMin) return false;

        return true;
    }
    return false;
}

void Sphere::moveShape(float t) {
    float offset = this->velocity*t;
    this->center += vec3(offset, offset, offset);
}

void Sphere::restoreShape() {
    this->center = originalCenter;
}

Triangle::Triangle(vec3 v1,vec3 v2, vec3 v3, Material material, Transformation& transformation) {
    this->transform = transformation.transform;
    this->transformI = transformation.transformI;
    this->transformTI = transformation.transformTI;

    this->v1 = transform*v1;
    this->v2 = transform*v2;
    this->v3 = transform*v3;

    this->isSphere=false;

    this->material = material;

    this->n1 = ((v2-v1)^(v3-v1)).normalize();
    this->n2 = n1;
    this->n3 = n1;
}

Triangle::Triangle(vec3 v1,vec3 v2, vec3 v3, vec3 n1, vec3 n2, vec3 n3, Material material, Transformation& transformation) {
    this->transform = transformation.transform;
    this->transformI = transformation.transformI;
    this->transformTI = transformation.transformTI;

    this->v1 = v1;
    this->v2 = v2;
    this->v3 = v3;

    this->material = material;

    this->isSphere=false;

    this->n1 = n1.normalize();
    this->n2 = n2.normalize();
    this->n3 = n3.normalize();
}

bool Triangle::intersect(Ray& ray, float& tHit, Intersection* intersect) {
    vec3 eye = ray.pos;
    vec3 dir = ray.dir;

    float a = v1[VX] - v2[VX],  d = v1[VX] - v3[VX],   g = dir[VX];
    float b = v1[VY] - v2[VY],  e = v1[VY] - v3[VY],   h = dir[VY];
    float c = v1[VZ] - v2[VZ],  f = v1[VZ] - v3[VZ],   i = dir[VZ];

    float j = v1[VX]-eye[VX];
    float k = v1[VY]-eye[VY];
    float l = v1[VZ]-eye[VZ];

    float m = (a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g));

    float t = (f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/-m;
    if (t < ray.tMin || t > ray.tMax) return false;

    float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c)) / m;
    if (gamma < 0 || gamma > 1) return false;

    float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/m;
    if (beta < 0 || beta > 1-gamma) return false;

    tHit = t;
    intersect->point = ray.evaluate(t);
    intersect->shape = this;

    float mag = (v1-intersect->point).length() + (v2-intersect->point).length() + (v3-intersect->point).length();

    intersect->normal = (((v1-intersect->point).length()/mag)*n1 + ((v2-intersect->point).length()/mag)*n2 + ((v3-intersect->point).length()/mag)*n3).normalize();

    return true;
}

bool Triangle::intersect(Ray& ray) {
    vec3 eye = ray.pos;
    vec3 dir = ray.dir;

    float a = v1[VX] - v2[VX],  d = v1[VX] - v3[VX],   g = dir[VX];
    float b = v1[VY] - v2[VY],  e = v1[VY] - v3[VY],   h = dir[VY];
    float c = v1[VZ] - v2[VZ],  f = v1[VZ] - v3[VZ],   i = dir[VZ];

    float j = v1[VX]-eye[VX];
    float k = v1[VY]-eye[VY];
    float l = v1[VZ]-eye[VZ];

    float m = (a*(e*i - h*f) + b*(g*f - d*i) + c*(d*h - e*g));

    float t = (f*(a*k - j*b) + e*(j*c - a*l) + d*(b*l - k*c))/-m;
    if (t < ray.tMin || t > ray.tMax) return false;

    float gamma = (i*(a*k - j*b) + h*(j*c - a*l) + g*(b*l - k*c)) / m;
    if (gamma < 0 || gamma > 1) return false;

    float beta = (j*(e*i - h*f) + k*(g*f - d*i) + l*(d*h - e*g))/m;
    if (beta < 0 || beta > 1-gamma) return false;

    return true;
}

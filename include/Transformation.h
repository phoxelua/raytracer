#pragma once
class Transformation {
public:
    mat4 transform, transformI, transformTI;
    stack<mat4> pastTransform;

    Transformation();

    //past transform memory operations
    void push();
    void pop();

    //transformations
    void translate(vec3 offset);
    void scale(vec3 scale);
    void rotate(vec3 axis, float angle);
};


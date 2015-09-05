#pragma once
#include "stdafx.h"
#include "CImg.h"

class Film {
public:
    int width, height;
    cimg_library::CImg<float> image;
    Film() {};
    Film(int width, int height);
    void writePixel(int i, int j, vec3 color);
    void display();
    void writeFile(string filename);
};


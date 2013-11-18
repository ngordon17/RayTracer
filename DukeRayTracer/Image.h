//
//  Image.h
//  Ray Tracer
//
//  Created by Dustin Alin on 11/1/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Image__
#define __RayTracer__Image__

#include <iostream>
#include <cmath>
#include <string>
#include <fstream>
#include "Color.h"
#include <stdio.h>
#include <stdlib.h>
using namespace std;

class Image {
public:
    Image();
    Image(int width, int height);
    Image(int width, int height, Color background);
    ~Image(void);
    
    bool set(int x, int y, const Color& color);
    void gammaCorrect(float gamma);
    
    void writePPM(ostream& out);
    void readPPM(string file_name);
    int width();
    int height();
    Color getPixel(int i, int j);
    
private:
    Color** raster; //2D raster array of RGB colors for each pixel
    int nx;
    int ny;
    
};

#endif /* defined(__Ray_Tracer__Image__) */
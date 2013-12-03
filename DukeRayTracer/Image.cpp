//
//  Image.cpp
//  Ray Tracer
//
//  Created by Dustin Alin on 11/1/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Image.h"
#include <iostream>

Image::Image() {}


//Initializes a raster array where the default color for each pixel is black.
Image::Image(int width, int height) {
    nx = width;
    ny = height;
    
    raster = new Color*[nx];
    for (int i = 0; i < nx; i++) {
        raster[i] = new Color[ny];
    }
}

/*
 Initializes a raster array where each pixel is set to the color specified by the argument
 'background.'
 */
Image::Image(int width, int height, Color background) {
    nx = width;
    ny = height;
    
    raster = new Color*[nx];
    for (int i = 0; i < nx; i++) {
        raster[i] = new Color[ny];
        for (int j = 0; j < ny; j++) {
            raster[i][j] = background;
        }
    }
}

Image::~Image(void) {
    for (int i = 0; i < nx; i++) {
        delete [] raster[i];
    }
    delete [] raster;
}

//sets a pixel value (x, y) in the raster to color
bool Image::set(int x, int y, const Color& color) {
    if (x < 0 || x >= nx) return false;
    if (y < 0 || y >= ny) return false;
    raster[x][y] = color;
    return true;
}

//corrects pixel color values by accounting for the nonlinear intensity on the screen
void Image::gammaCorrect(float gamma) {
    float power = 1.0 / gamma;
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            Color temp = raster[i][j];
            raster[i][j] = Color(pow(temp.getRed(), power), pow(temp.getGreen(), power),
                                 pow(temp.getBlue(), power));
        }
    }
}

//writes a binary PPM with the values in the raster array
void Image::writePPM(ostream& out) {
    //output header with magic number and number of pixels for width and height
    out << "P3\n";
    out << nx << ' ' << ny << '\n';
    out << "255\n";
    
    unsigned int ired, igreen, iblue;
    unsigned char red, green, blue;
    
    //for each pixel, get the color value form the raster array and output in
    //the PPM file
    for (int i = ny-1; i >= 0; i--) {
        for (int j = 0; j < nx; j++) {
            ired = (unsigned int)(256*raster[j][i].getRed());
            igreen = (unsigned int)(256*raster[j][i].getGreen());
            iblue = (unsigned int)(256*raster[j][i].getBlue());
            if (ired > 255) ired = 255;
            if (igreen > 255) igreen = 255;
            if (iblue > 255) iblue = 255;
            red = (unsigned char)(ired);
            green = (unsigned char)(igreen);
            blue = (unsigned char)(iblue);

            out << ired << '\n';
            out << igreen << '\n';
            out << iblue << '\n';
        }
    }
}

//reads in a binary PPM
void Image::readPPM(string file_name) {
    //open stream to file
    ifstream in;
    in.open(file_name.c_str());
    if (!in.is_open()) {
        cerr << " ERROR -- Couldn't open file \'" << file_name << "\'";
        exit(-1);
    }
    
    char ch, type;
    char red, green, blue;
    int cols, rows;
    int num;
    
    //read in header info
    in.get(ch);
    in.get(type);
    in >> cols >> rows >> num;
    nx = cols;
    ny = rows;
    
    //allocate raster
    raster = new Color*[nx];
    for (int i = 0; i < nx; i++) {
        raster[i] = new Color[ny];
    }
    
    //clean up newline
    in.get(ch);
    
    //store PPM pixel values in raster
    for (int i = ny-1; i >= 0; i--) {
        for (int j = 0; j <nx; j++) {
            in.get(red);
            in.get(green);
            in.get(blue);
            raster[j][i] = Color((float)((unsigned char)red)/255.0,
                                 (float)((unsigned char)green)/255.0,
                                 (float)((unsigned char)blue)/255.0);
        }
    }
}

int Image::width() {
    return nx;
}

int Image::height() {
    return ny;
}

Color Image::getPixel(int i, int j) {
    //printf("%d %d", i, j);
    return raster[i][j];
}

Color** Image::getRaster() {
    return raster;
}

float* Image::getPixels() {
    float* imageDisplayArray = new float[nx*ny*3];
    
    for (int i = 0; i < ny; i++) {
        for (int j = 0; j < nx; j++) {
            int index = nx*ny*3 - (ny*(nx - j - 1) + ny - i)*3; //fix this?......
            imageDisplayArray[index] = raster[i][j].getRed();
            imageDisplayArray[index + 1] = raster[i][j].getGreen();
            imageDisplayArray[index + 2] = raster[i][j].getBlue();
        }
    }
    
    return imageDisplayArray;
}




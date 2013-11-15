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

Image::Image(int width, int height) {
    nx = width;
    ny = height;
    
    raster = new Color*[nx];
    for (int i = 0; i < nx; i++) {
        raster[i] = new Color[ny];
    }
}

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

bool Image::set(int x, int y, const Color& color) {
    if (x < 0 || x >= nx) return false;
    if (y < 0 || y >= ny) return false;
    raster[x][y] = color;
    return true;
}

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

void Image::writePPM(ostream& out) {
    //output header
    out << "P3\n";
    out << nx << ' ' << ny << '\n';
    out << "255\n";
    
    unsigned int ired, igreen, iblue;
    unsigned char red, green, blue;
    
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
    return raster[i][j];
}





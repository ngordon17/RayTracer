//
//  main.cpp
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include <vector>
#include <iostream>
#include "Vector3.h"
#include "Color.h"
#include "Image.h"
#include "Shape.h"
#include "Triangle.h"
#include "Sphere.h"
#include "Camera.h"
#include "MarbleTexture.h"
#include "UVSphere.h"
#include "Texture.h"
#include "SolidNoise.h"
#include "NoiseTexture.h"
#include "ImageTexture.h"
#include "TriangleMesh.h"
#include "Mesh.h"

int main(int argc, const char * argv[])
{

    IntersectRecord record;
    bool is_a_hit;
    float tmax; //max valid t parameter
    Vector3 dir(0, 0, -1); //use -z direction for the viewing rays to use a right handed coordinate system
    
    vector<Shape*> shapes;
    
    //adding sphere with center (250, 250, -1000) and radius of 150
    //shapes.push_back(new Sphere(Vector3(0, 0, 0), sqrt(2), Color(.2, .2, .8)));
    //adding triangle
    /*
    shapes.push_back(new Triangle(Vector3(300.0f, 600.0f, -800),
                                  Vector3(0.0f, 100.0f, -1000),
                                  Vector3(450.0f, 20.0f, -1000),
                                  Color(.8, .2, .2)));
     */
    
    //shapes.push_back(new Triangle(Vector3(-0.5, 0, 1), Vector3(0.5, 0, 1), Vector3(0, 1, 0), Color(.2, .2, .8)));
    shapes.push_back(new UVSphere(Vector3(0, 0, 0), sqrt(2), new ImageTexture("/Users/dalin/Desktop/School/Duke/Senior Fall/CS 344/RayTracer/RayTracer/RayTracer/NoiseTexture.ppm")));
    //shapes.push_back(new UVSphere(Vector3(0, 0, 0), sqrt(2), new MarbleTexture(2)));
    //shapes.push_back(new UVSphere(Vector3(0, 0, 0), sqrt(2), new MarbleTexture(10)));
    //shapes.push_back(new UVSphere(Vector3(0, 0, 0), sqrt(2), new NoiseTexture()));

    
    //shapes.push_back(new UVSphere(Vector3(0, 0, 0), sqrt(3), new MarbleTexture(10)));
    
    float res = 101;
    Image im(res, res);
    Camera cam(Vector3(0, 0, 2), Vector3(0, 0, -2), Vector3(0, 1, 0), 0.0, -2, 2, -2, 2, 2);
        
    //for each pixel on a 500x500 pixel image
    for (int i = 0; i < res; i++) {
        for (int j = 0; j < res; j++) {
            tmax = 100000.0f;
            is_a_hit = false;
            //Ray r(Vector3(i, j, 0), dir); //ray with pixel as the origin and dir as directional vector
            Ray r = cam.getRay(i, j, res, res, 0, 0);
            
            for (int k = 0; k < shapes.size(); k++) {
                if (shapes[k]->intersect(r, .00001f, tmax, 0, record)) {
                    tmax = record.t;
                    is_a_hit = true;
                }
            }
            
            //if intersects with a shape, draw the shape's color
            if (is_a_hit)
                im.set(i, j, record.tex -> value(record.uv, record.intersection));
            else
                im.set(i, j, Color(.2, .2, .2));
        }
    }
    im.writePPM(cout);
}


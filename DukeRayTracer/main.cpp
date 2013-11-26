//
//  main.cpp
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include <vector>
#include <iostream>
#include <math.h>
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
#include "Parallelogram.h"
#include "SimpleTexture.h"
#include "DiffuseMaterial.h"
#include "Instance.h"
#include "Lighting.h"


vector<Shape*> makeScene() {
    vector<Shape*> shapes;
    
    //How to implement materials??
    //shapes.push_back(new Parallelogram(Vector3(-1, 0, 0), Vector3(2, 2, 0), Vector3(0, 2, 0), new DiffuseMaterial(new MarbleTexture(2))));
    //shapes.push_back(new Parallelogram(Vector3(-1, 0, 0), Vector3(2, 2, 0), Vector3(0, 2, 0), new DiffuseMaterial(new SimpleTexture(Color(0.5, 0.4, 0.5)))));
    
    /* //create an ellipsoid using instance with sphere and scale matrix
     shapes.push_back(new Instance(Matrix::getScaleMatrix(1.0f, 0.5f, 1.0f), new Sphere(Vector3(250, 250, -1000), 150, Color(.2, .2, .8))));
     */
    
    //texture map sphere with world map i.e. make a globe
    shapes.push_back(new UVSphere(Vector3(0, 0, -250), 150, new ImageTexture("/Users/yankeenjg/Desktop/CPS344 Ray Tracer/world_map.ppm")));
    
    /* //create sphere with triangle
     shapes.push_back(new Sphere(Vector3(250, 250, -1000), 150, Color(.2, .2, .8)));
     shapes.push_back(new Triangle(Vector3(300.0f, 600.0f, -800), Vector3(0.0f, 100.0f, -1000), Vector3(450.0f, 20.0f, -1000), Color(.8, .2, .2)));
     */
    
    //shapes.push_back(new UVSphere(Vector3(0, 0, 0), sqrt(2), new MarbleTexture(2)));
    //shapes.push_back(new UVSphere(Vector3(0, 0, 0), sqrt(2), new MarbleTexture(10)));
    //shapes.push_back(new UVSphere(Vector3(0, 0, 0), sqrt(2), new NoiseTexture()));
    //shapes.push_back(new UVSphere(Vector3(0, 0, 0), sqrt(1), new MarbleTexture(10)));
    //shapes.push_back(new UVSphere(Vector3(0, 0, 0), sqrt(2), new SimpleTexture(Color(.2, .2, .8))));
    return shapes;
    
}

Color makeLightingColor(Vector3 light_source, Color texture_color, Camera cam, IntersectRecord record, float phong_exponent) {
    Color ambient_color = Color(0.1, 0.1 ,0.1);
    Color diffuse_color = Color(1.0, 1.0, 1.0);
    Color specular_color = Color(1.0, 1.0, 1.0);
    
    Vector3 vertex_to_light_vector = light_source - record.intersection;
    Vector3 normalized_vertex_to_light_vector = normalize(vertex_to_light_vector);
    Vector3 vertex_to_eye_vector = cam.getE() - record.intersection;
    Vector3 bisector = normalize(vertex_to_light_vector + vertex_to_eye_vector);
    
    float diffuse_term = dot(record.normal, normalized_vertex_to_light_vector);
    if (diffuse_term < 0.0) diffuse_term = 0.0;
    if (diffuse_term > 1.0) diffuse_term = 1.0;
    
    float specular_term = dot(record.normal, bisector);
    if (specular_term < 0.0) specular_term = 0.0;
    if (specular_term > 1.0) specular_term = 1.0;
    
    float phong_constant = pow(specular_term, phong_exponent);
    Color lighting_color = ambient_color + (diffuse_color * diffuse_term) + (specular_color * phong_constant);
    Color mix_color = (texture_color + lighting_color)/2.0;
    
    return mix_color;
}

int main(int argc, const char * argv[])
{
    IntersectRecord record;
    bool is_a_hit;
    float tmax; //max valid t parameter
    Vector3 dir(0, 0, -1); //use -z direction for the viewing rays to use a right handed coordinate system
    
    
    vector<Shape*> shapes = makeScene();
    
    float res = 512;
    Image im(res, res);
    Camera cam(Vector3(0, 0, 2), Vector3(0, 0, -2), Vector3(0, 1, 0), 0.0, -2, 2, -2, 2, 1);

    Lighting light = Lighting(Vector3(250, 0, -125), cam.getE());
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
            if (is_a_hit) {
                Color texture_color = record.tex-> value(record.uv, record.intersection);
                
                //color, record, camera, phong constant
                
                Color mix_color = light.makeLightingColor(texture_color, record, 80.0);
                
                im.set(i, j, mix_color);
            }
            else {
                im.set(i, j, Color(.2, .2, .2));
            }
        }
    }
    im.writePPM(cout);
}


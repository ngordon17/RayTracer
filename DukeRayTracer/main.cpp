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
#include "SimpleMaterial.h"
#include <OpenGL/OpenGL.h>
#include <GLUT/GLUT.h>
#include "DSphere.h"


float dtime = 0;
float win_width = 1024;
float win_height = 1024;
float* current_pixels;
Image* current_image;

vector<Shape*> makeScene() {
    vector<Shape*> shapes;
    
    shapes.push_back(new Parallelogram(Vector3(10, -1, 0), Vector3(0, 0, -20), Vector3(-20, 0, 0), new SimpleMaterial(new ImageTexture("/Users/yankeenjg/Desktop/CPS344 Ray Tracer/checkerboard.ppm"), Color(0.0, 0.0, 0.0), Color(0.0, 0.0, 0.0), 50, 0, Color(0.9, 0.9, 0.9))));
    
    shapes.push_back(new Sphere(Vector3(0, 1, -14), 2.0, new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(1, 0, 1), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    
    shapes.push_back(new Sphere(Vector3(4, 0, -14), 1.0, new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(1, 1, 0), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    
    shapes.push_back(new Sphere(Vector3(-4, 0, -14), 1.0, new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(0, 1, 1), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    
    shapes.push_back(new Instance(Matrix::getScaleMatrix(1.0, 0.4, 1.0), new Sphere(Vector3(-5, 12, -12), 1.0, new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(0, 0, 1), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9)))));
    
    shapes.push_back(new Triangle(Vector3(2, 6, -12), Vector3(2, 3, -16), Vector3(5, 4, -15), new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(0, 1, 0), Color(1, 1, 1), 50, 0, Color(.7, .9, .7))));

    return shapes;
}

vector<Lighting*> makeLighting() {
    vector<Lighting*> lights;
    
    lights.push_back(new Lighting(Vector3(-4, 8, -10), Color(1, 1, 1)));
    lights.push_back(new Lighting(Vector3(5, 4, -5), Color(0, 0, 1)));
    lights.push_back(new Lighting(Vector3(3, 10, -3), Color(1, 1,1)));
    
    return lights;
}



bool trace(IntersectRecord& record, Ray r, vector<Shape*> shapes, float tmin, float tmax) {
    bool is_hit = false;
    
    for (int k = 0; k < shapes.size(); k++) {
        if (shapes[k] -> intersect(r, tmin, tmax, 0, record)) {
            is_hit = true;
        }
    }
    return is_hit;
}

bool shadowTrace(Ray r, vector<Shape*> shapes, float tmin, float tmax) {
    bool is_hit = false;
    
    for (int k = 0; k < shapes.size(); k++) {
        if (shapes[k] -> shadowIntersect(r, tmin, tmax, 0)) {
            is_hit = true;
        }
    }
    return is_hit;
}


Color traceRay(Ray r, vector<Shape*> shapes, vector<Lighting*> lights, float tmin, float tmax, float depth, float max_depth) {
    
    if (depth > max_depth) {return Color(0.0, 0.0, 0.0);}
    IntersectRecord record;
    bool is_hit = trace(record, r, shapes, tmin, tmax);
    if (is_hit) {
        Color radiance = record.material -> ambientResponse(record.intersection, record.uv);
        //calculate lighting / shadows
        for (int k = 0; k < lights.size(); k++) {
            Vector3 to_light = lights[k] -> getLightVector(record);
            //check for shadow / object blocking light
            if (!shadowTrace(Ray(record.intersection, to_light), shapes, tmin, tmax)) {
                radiance += lights[k] -> getIntensity() * record.material -> emittedRadiance(record.uvw, to_light, -r.direction());
            }
        }
        
        
        if (record.material -> isReflective()) {
            Vector3 reflect_dir = record.material -> getReflectionDirection(record.uvw, r.direction());
            Ray reflect_ray = Ray(record.intersection, reflect_dir);
            Color reflectance = traceRay(reflect_ray, shapes, lights, tmin, tmax, depth + 1, max_depth);
            radiance += reflectance * record.material -> reflectiveResponse(depth);
            //printf("%f %f %f", reflectance.getRed(), reflectance.getGreen(), reflectance.getBlue());
        }
        
        
        /*
        if (record.material -> isTransmissive()) {
            Vector3 trans_dir; float fresnel_scale; Color extinction;
            if (record.material -> getTransmissionDirection(record.uvw, r.direction(), extinction, fresnel_scale, trans_dir)) {
                Ray refract_ray = Ray(record.intersection, trans_dir);
                Color refraction = traceRay(refract_ray, shapes, lights, tmin, tmax, depth + 1, max_depth);
                radiance += refraction * fresnel_scale * extinction;
                //radiance += refraction * record.material -> transmissiveResponse(depth);
                //printf("%f %f %f", refraction.getRed(), refraction.getGreen(), refraction.getBlue());
            }
        }
        */
        
        return radiance;
         
    }

    return Color(0, 0, 0);
}

Image draw(float width, float height) {
    IntersectRecord record;
    vector<Shape*> shapes = makeScene();
    vector<Lighting*> lights = makeLighting();
    
    Image im(width, height);
    Camera cam(Vector3(0, 0, 0), Vector3(0, 0, -1), Vector3(0, 1, 0), 0.0, -2.0, 2.0, -2.0, 2.0, 3, width, height);
    
    //for each pixel
    for (int i = 0; i < width; i++) {
        for (int j = 0; j < height; j++) {
            Ray r = cam.getRay(i, j, 0, 0);
            Color radiance = traceRay(r, shapes, lights, 0.0001f, 100000.0f, 0, 5);
            im.set(i, j, radiance);
        }
    }
    return im;
}



void init( void ){
    glClearColor(0.0, 0.0, 0.0, 0.0);
}

void idle( void ){
    //glutPostRedisplay();
}

void drawImage( void ){

    if(current_pixels != NULL){
        glClear(GL_COLOR_BUFFER_BIT);
        glRasterPos2i(0, 0);
        glDrawPixels(win_width, win_height, GL_RGB, GL_FLOAT, current_pixels);
    }
}

void display( void ) {
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0, win_width, 0, win_height, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    drawImage();
    
    glFlush();
    glutSwapBuffers();
}

void reshape( int w, int h ) {
    glViewport( 0, 0, win_width, win_height );
    
   // glutPostRedisplay();
}

void keyboard( unsigned char key, int x, int y ) {
    switch(key) {
        case 27: // Escape key
            exit(0);
            break;
        case 119: //w - write out the ppm file to the console!
            if (current_image != NULL) {current_image -> writePPM(cout);}
            break;
    }
}

int main(int argc, char * argv[]) {
    Image im = draw(win_width, win_height);
    current_image = &im;
    current_pixels = im.getPixels();

    
    glutInit(&argc, argv);
    glutInitDisplayMode( GLUT_RGB );
    glutInitWindowSize( win_width, win_height );
    glutCreateWindow( "Duke Ray Tracer" );
    init();
    glutDisplayFunc( display );
    glutReshapeFunc( reshape );
    glutKeyboardFunc( keyboard );
    glutIdleFunc( idle );
    glutMainLoop();
    
    
    return 0;
}


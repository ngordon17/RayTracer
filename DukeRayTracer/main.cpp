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


float win_width = 512;
float win_height = 512;
float* current_pixels;
Image* current_image;

vector<Shape*> makeScene() {
    vector<Shape*> shapes;
    
    /*
    shapes.push_back(new Sphere(Vector3(0, 0, -17), 2.0,
            new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(1, 0, 0), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    shapes.push_back(new Sphere(Vector3(0, 4, -17), 1.5,
            new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(0, 1, 0), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    shapes.push_back(new Sphere(Vector3(0, -4, -17), 1.5,
            new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(0, 0, 1), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    shapes.push_back(new Sphere(Vector3(4, 0, -17), 1.5,
            new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(1, 1, 0), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    shapes.push_back(new Sphere(Vector3(-4, 0, -17), 2.0,
            new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(0, 1, 1), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    */
    
    
    
    //How to implement materials??
    //base = vertex, u = offset in one direction, v = offset in other direction, 4th vertex defined because
    //it is a parallelogram
    //shapes.push_back(new Parallelogram(Vector3(-2, -2, 0), Vector3(0, 0, -1), Vector3(2, 0, 0), new MarbleTexture(2)));
    
    //shapes.push_back(new Parallelogram(Vector3(0.5, 0, 0), Vector3(-0.5, 1, 1), Vector3(0.5, 1, 1), new SimpleTexture(Color(1, 0, 0))));
    
    /* //create an ellipsoid using instance with sphere and scale matrix
     shapes.push_back(new Instance(Matrix::getScaleMatrix(1.0f, 0.5f, 1.0f), new Sphere(Vector3(250, 250, -1000), 150, Color(.2, .2, .8))));
     */
    
    //texture map sphere with world map i.e. make a globe
    /*
    shapes.push_back(new UVSphere(Vector3(0, 0, -20), 1.5, new SimpleMaterial(new ImageTexture("/Users/yankeenjg/Desktop/CPS344 Ray Tracer/world_map.ppm"), Color(1.0, 1.0, 1.0), Color(1.0, 1.0, 1.0), 50, 0, Color(0, 0, 0))));
    */
    
    
    /*
    shapes.push_back(new Parallelogram(Vector3(20, -4, 0), Vector3(0, 0, -20), Vector3(-40, 0, 0), new SimpleMaterial(new SimpleTexture(Color(0.1, 0.1, 0.1)), Color(0.5, 0.5, 0.5), Color(1.0, 1.0, 1.0), 50, 0, Color(1, 1, 1))));
    */
    shapes.push_back(new Parallelogram(Vector3(3, -1, 0), Vector3(0, 0, -80), Vector3(-6, 0, 0), new SimpleMaterial(new SimpleTexture(Color(0.1, 0.1, 0.1)), Color(0.1, 0.1, 0.1), Color(1.0, 1.0, 1.0), 50, 0, Color(0.9, 0.9, 0.9))));
    
    shapes.push_back(new Sphere(Vector3(1, 4, -19), 3.0, new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(1, 0, 1), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    
    shapes.push_back(new Sphere(Vector3(-2, 3, -14), 1.0, new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(1, 1, 0), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    
    shapes.push_back(new Sphere(Vector3(-2, 0, -14), 1.0, new SimpleMaterial(new SimpleTexture(Color(.1, .1, .1)), Color(0, 1, 1), Color(1, 1, 1), 50, 0, Color(0.9, 0.9, 0.9))));
    
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

vector<Lighting*> makeLighting() {
    vector<Lighting*> lights;
    //Lighting light = Lighting(Vector3(-1, 0 , -5));
    
    lights.push_back(new Lighting(Vector3(-4, 8, -10), Color(1, 1, 1)));
    lights.push_back(new Lighting(Vector3(6, 4, -2), Color(0, 0, 1)));
    
    lights.push_back(new Lighting(Vector3(3, 10, -3), Color(1, 1,1)));
     
    
    /*
    lights.push_back(new Lighting(Vector3(0.57735027, -0.57735027, -0.57735027), Color(1, 1, 1)));
    lights.push_back(new Lighting(Vector3(-0.57735027, 0.57735027, -0.57735027), Color(1, 1, 1)));
    */
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
        }
        
        /*
        if (record.material -> isTransmissive()) {
            Vector3 trans_dir; float fresnel_scale; Color extinction;
            if (record.material -> getTransmissionDirection(record.uvw, r.direction(), extinction, fresnel_scale, trans_dir)) {
                Ray refract_ray = Ray(record.intersection, trans_dir);
                Color refraction = traceRay(refract_ray, shapes, lights, tmin, tmax, depth + 1, max_depth);
                radiance += refraction * record.material -> transmissiveResponse(depth);
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
            Color radiance = traceRay(r, shapes, lights, .0001f, 100000.0f, 0, 10);
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
        case 119: //w
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


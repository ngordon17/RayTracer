//
//  Camera.cpp
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Camera.h"

Camera::Camera(const Camera& orig)  {
    e = orig.e; //camera center
    corner = orig.corner; //bottom left corner
    across = orig.across; //u vector scaled by width of screen
    up = orig.up; //v vector scaled by height of screen
    basis = orig.basis; //camera basis
    l = orig.l; //left
    r = orig.r; //right
    b = orig.b; //bottom
    t = orig.t; //top
    d = orig.d; //camera distance to screen (calculated using screen normal)
    lens_radius = orig.lens_radius; //radius of lens
    nx = orig.nx;
    ny = orig.ny;
}
Camera::Camera(Vector3 c, Vector3 gaze, Vector3 vup, float aperture, float left,
               float right, float bottom, float top, float distance, float _nx, float _ny) {
    aperture = 0; //set aperture to 0 for now...deal with lens stuff later...
    e = c;
    d = distance;
    l = left;
    r = right;
    b = bottom;
    t = top;
    nx = _nx;
    ny = _ny;
    
    lens_radius = aperture/2.0F; //aperture is diameter of lens
    basis.initFromWV(-gaze, vup); //gaze is the viewing direction (i.e. -w)
    corner = e + l*basis.u() + b*basis.v() - d*basis.w();
    across = (r-l)*basis.u();
    up = (t-b)*basis.v();
}

Ray Camera::getRay(float i, float j, float xi1, float xi2) {
    //xi1 and xi2 are lens samples...set aperture to 0 to ignore lens size...
    float a = (i  + 0.5) / nx;
    float b = (j + 0.5) / ny;
    //change origin based on the fact that our camera is no longer a point. i.e. shift e by some factor of the lens radius.
    Vector3 origin = e + 2.0F*(xi1-0.5F)*lens_radius*basis.u() + 2.0F*(xi2-0.5F)*lens_radius*basis.v();
    //point on the image plane, a and b are pixel coordinates (i / nx = a, j / ny = b) i.e. a and b are between 0 and 1
    Vector3 s = corner + across*a + up*b;
    return Ray(origin, normalize(s-origin)); //p(t) = e + t(s-e) from class notes
}
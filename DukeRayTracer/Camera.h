//
//  Camera.h
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Camera__
#define __RayTracer__Camera__

#include <iostream>
#include "Ray.h"
#include "ONB.h"

class Camera {
public:
    Camera() {}
    Camera(const Camera& orig);
    Camera(Vector3 c, Vector3 gaze, Vector3 vup, float aperture, float left, float right,
           float bottom, float top, float distance);
    Ray getRay(float i, float j, float nx, float ny, float xi1, float xi2);
    Vector3 getE() { return e; }
    
private:
    Vector3 e, corner, across, up;
    ONB basis;
    float lens_radius;
    float l, r, b, t;
    float d;
};

#endif /* defined(__RayTracer__Camera__) */

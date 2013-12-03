//
//  Lighting.h
//  DukeRayTracer
//
//  Created by Dustin Alin on 11/25/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __DukeRayTracer__Lighting__
#define __DukeRayTracer__Lighting__

#include <iostream>
#include "Vector3.h"
#include "Camera.h"
#include "Color.h"
#include "Shape.h"

class Lighting {
public:
    Lighting(Vector3 light_ray, Color intensity) {light_source = light_ray; I = intensity;}
    Vector3 getLightVector(IntersectRecord record);
    Color getIntensity();
    
private:
    Vector3 light_source;
    Color I;
};

#endif /* defined(__DukeRayTracer__Lighting__) */

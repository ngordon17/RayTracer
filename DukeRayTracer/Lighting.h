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
    Lighting(Vector3 light_ray, Vector3 e) { light_source = light_ray; eye = e; }
    Color makeLightingColor(Color texture_color, IntersectRecord record, float phong_exponent);
    
private:
    Vector3 light_source;
    Vector3 eye;
};

#endif /* defined(__DukeRayTracer__Lighting__) */

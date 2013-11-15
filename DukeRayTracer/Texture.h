//
//  Texture.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Texture__
#define __RayTracer__Texture__

#include <iostream>
#include "Vector2.h"
#include "Vector3.h"
#include "Color.h"

class Texture {
public:
    //vector2 is uv coordinate, vector3 is 3d interesection
    virtual Color value(const Vector2&, const Vector3&) const = 0;
};

#endif /* defined(__RayTracer__Texture__) */


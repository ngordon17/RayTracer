//
//  Vertex.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Vertex__
#define __RayTracer__Vertex__

#include <iostream>
#include "Vector2.h"
#include "Vector3.h"

struct VertexUV {
    Vector3 vertex;
    Vector2 uv;
};

struct VertexN {
    Vector3 vertex;
    Vector3 normal;
};

struct VertexUVN {
    Vector3 vertex;
    Vector3 normal;
    Vector2 uv;
};

#endif /* defined(__RayTracer__Vertex__) */

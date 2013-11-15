//
//  Mesh.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Mesh__
#define __RayTracer__Mesh__

#include <iostream>
#include "Vertex.h"
#include "Shape.h"
#include "Texture.h"

class Mesh {
public:
    Mesh() {}
    Texture* getTexture() const {return tex;}
    
//private:
    Texture* tex;
    Vector3* verts;
    VertexUV* vertUVs;
    VertexN* vertNs;
    VertexUVN* vertUVNs;
};

#endif /* defined(__RayTracer__Mesh__) */

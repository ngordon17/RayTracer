//
//  TriangleMesh.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__TriangleMesh__
#define __RayTracer__TriangleMesh__

#include <iostream>
#include "Shape.h"
#include "Mesh.h"
#include "Texture.h"

class MeshTriangleUV : public Shape {
public:
    MeshTriangleUV();
    MeshTriangleUV(Mesh* m, int v0, int v1, int v2, int index);
    ~MeshTriangleUV();
    bool intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const;
    bool shadowIntersect(const Ray& r, float tmin, float tmax, float time) const;
    BBox boundingBox(float time0, float time1) const;
    //bool randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const;
    
private:
    int verts[3]; //indices of vertices in vertex array (array stored in mesh - avoid duplicating shared vertices)
    Mesh* mesh;
};


#endif /* defined(__RayTracer__TriangleMesh__) */

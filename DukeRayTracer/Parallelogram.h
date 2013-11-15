//
//  Parallelogram.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/13/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Parallelogram__
#define __RayTracer__Parallelogram__

#include <iostream>
#include "Shape.h"
#include "Material.h"
#include "BBox.h"
#define PARALLEL_EPSILON 0.00000001f

class Parallelogram : public Shape {
public:
    Parallelogram(const Vector3& _base, const Vector3& _u, const Vector3& _v, Material* mat);
    Parallelogram(const Vector3& _base, const Vector3& _u, const Vector3& _v, const Vector2& _uv0, const Vector2& _uv1, const Vector2& _uv2, Material* mat);
    bool intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const;
    bool shadowIntersect(const Ray& r, float tmin, float tmax, float time) const;
    BBox boundingBox(float time0, float time1) const;
    bool randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const;

private:
    Vector3 base;  //
    Vector3 u;     //one vertex and the offsets to its neighbors
    Vector3 v;     //
    Vector3 norm;  //parallelogram normal
    Vector3 unorm; //normalize u offset
    Vector3 vnorm; //normalized v offset
    Vector2 uv0;   //
    Vector2 uv1;   //texture coords
    Vector2 uv2;   //
    float _pdf;    // precomputed constant pdf (probability density function)
    Material* mptr;
};

#endif /* defined(__RayTracer__Parallelogram__) */

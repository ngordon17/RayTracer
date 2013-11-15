//
//  Triangle.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Triangle__
#define __RayTracer__Triangle__

#include <iostream>
#include "Shape.h"
#include "Ray.h"
#include "Color.h"
#include "Vector3.h"

class Triangle : public Shape {
public:
    Triangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Color& rgb);
    bool intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const;
    bool shadowIntersect(const Ray& r, float tmin, float tmax, float time) const;
    BBox boundingBox(float time0, float time1) const;
    bool randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const;
    
private:
    Vector3 v0, v1, v2;
    Color color;
};













#endif /* defined(__RayTracer__Triangle__) */

//
//  Sphere.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Sphere__
#define __RayTracer__Sphere__

#include <iostream>
#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "Color.h"

class Sphere : public Shape {
public:
    Sphere(const Vector3& c, float r, const Color& rgb) {center = Vector3(c); radius = float(r); color = Color(rgb);}
    bool intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const;
    bool shadowIntersect(const Ray& r, float tmin, float tmax, float time) const;
    BBox boundingBox(float time0, float time1) const;
    bool randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const;
    
private:
    Vector3 center;
    float radius;
    Color color;
};

#endif /* defined(__RayTracer__Sphere__) */

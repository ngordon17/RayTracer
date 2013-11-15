//
//  DSphere.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__DSphere__
#define __RayTracer__DSphere__

#include <iostream>
#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "Color.h"

//Sphere with time dependent function to determine center location at time t
class DSphere : public Shape {
public:
    DSphere(const Vector3& oc, float r, const Color& rgb, float min_time, float max_time);
    bool intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const;
    bool shadowIntersect(const Ray&, float tmin, float tmax, float time) const;
    Vector3 getCenter(float t) const;
    BBox boundingBox(float time0, float time1) const;
    bool randomPoint(const Vector3 &viewpoint, const Vector2 &seed, float time, Vector3 &light_point, Vector3 &N, float &pdf, Color &radiance) const;

private:
    Vector3 ocenter;
    float mintime;
    float maxtime;
    float radius;
    Color color;
};

#endif /* defined(__RayTracer__DSphere__) */
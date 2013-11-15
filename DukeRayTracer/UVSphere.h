//
//  UVSphere.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__UVSphere__
#define __RayTracer__UVSphere__

#include <iostream>
#include "Shape.h"
#include "Vector3.h"
#include "Ray.h"
#include "Texture.h"



class UVSphere : public Shape {
public:
    UVSphere(const Vector3& c, float r, Texture* tex);
    bool intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const;
    bool shadowIntersect(const Ray& r, float tmin, float tmax, float time) const;
    BBox boundingBox(float time0, float time1) const;
    bool randomPoint(const Vector3 &viewpoint, const Vector2 &seed, float time, Vector3 &light_point, Vector3 &N, float &pdf, Color &radiance) const;

private:
    Vector3 center;
    float radius;
    Texture* tex;
    
};




#endif /* defined(__RayTracer__UVSphere__) */

//
//  Shape.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Shape__
#define __RayTracer__Shape__

#include <iostream>
#include "Ray.h"
#include "Texture.h"
#include "Vector3.h"
#include "Color.h"
#include "ONB.h"
#include "BBox.h"
#include "Material.h"
#include "SimpleMaterial.h"

//class Ray;
//class Color;


/*records t value for interesection (so we can retrieve (x, y, z) coordinates from parametric equations as well
 as the normal of the surface intersected and the color to be drawn */
/*
struct IntersectRecord {
    float t;
    Vector3 normal;
    Vector2 uv; //used for 2D textures
    ONB uvw; //used for instancing...correct??
    Vector3 intersection; //point of intersection
    Texture* tex; //texture of nearest interesected object
};
*/

//combination of old and new intersection records...
struct IntersectRecord {
    float t;
    Vector3 intersection;
    Vector3 texture_intersection;
    ONB uvw;
    Vector2 uv;
    SimpleMaterial* material;
};

class Shape {
public:
    //time parameter to be used for motion blur in animation i.e. see DSphere
    virtual bool intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const=0;
    //useful to determine intersections for occluded objects as it is faster / more efficient
    virtual bool shadowIntersect(const Ray& r, float tmin, float tmax, float time) const=0;
    virtual BBox boundingBox(float time0, float time1) const {return bbox;} //correct?
    //virtual bool randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const=0;
protected:
    BBox bbox;
    SimpleMaterial* mptr;
};

#endif /* defined(__RayTracer__Shape__) */

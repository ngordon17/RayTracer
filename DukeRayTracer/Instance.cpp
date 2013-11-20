//
//  ShapeInstance.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Instance.h"
#include "ONB.h"

Instance::Instance(Matrix trans, Matrix trans_inverse, Shape* orig) : M(trans), N(trans_inverse), prim(orig) {}
Instance::Instance(Matrix trans, Shape* orig) : M(trans), N(trans), prim(orig) {N.invert();}

bool Instance::intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const {
    Vector3 no = transformLoc(N, r.origin()); //transformed ray origin into local coordinates
    Vector3 nd = transformVec(N, r.direction()); //transformed ray direction into local coordinates
    Ray tray(no, nd);
    
    if (prim -> intersect(tray, tmin, tmax, time, record)) {
        record.intersection = transformLoc(M, record.intersection);
        Vector3 normal = transformVec(N.getTranspose(), record.uvw.w()); 
        ONB uvw;
        uvw.initFromW(normal);
        record.uvw = uvw;
        return true;
    }
    return false;
}

bool Instance::shadowIntersect(const Ray& r, float tmin, float tmax, float time) const {
    Vector3 no = transformLoc(N, r.origin()); //transformed ray origin into local coordinates
    Vector3 nd = transformVec(N, r.direction()); //transformed ray direction into local coordinates
    Ray tray(no, nd);
    return prim -> shadowIntersect(tray, tmin, tmax, time);
}

BBox Instance::boundingBox(float time0, float time1) const {
    //TODO: implement
    return bbox;
}

bool Instance::randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const {
    //transformations?????
    return prim -> randomPoint(viewpoint, seed, time, light_point, N, pdf, radiance);
    
}


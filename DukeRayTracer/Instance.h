//
//  ShapeInstance.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__ShapeInstance__
#define __RayTracer__ShapeInstance__

#include <iostream>
#include "Shape.h"
#include "Matrix.h"


class Instance : public Shape {
public:
    Instance() {}
    ~Instance() {}
    Instance(Matrix trans, Matrix trans_inverse, Shape* orig);
    Instance(Matrix trans, Shape* orig);
    bool intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const;
    bool shadowIntersect(const Ray& r, float tmin, float tmax, float time) const;
    BBox boundingBox(float time0, float time1) const;
    virtual bool randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const;

private:
    Matrix M; //transformation matrix
    Matrix N; //inverse transformation matrix
    Shape* prim; //base shape (primary shape)

};

#endif /* defined(__RayTracer__ShapeInstance__) */

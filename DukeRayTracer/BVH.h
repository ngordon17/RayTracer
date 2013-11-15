//
//  BVH.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__BVH__
#define __RayTracer__BVH__

#include <iostream>
#include "Shape.h"
#include "Bbox.h"
#include "QSplit.h"

class BVH : public Shape {
public:
    BVH();
    BVH(Shape** surfaces, int num_surfaces);
    BVH(Shape* orig1, Shape* orig2);
    BVH(Shape* orig1, Shape* orig2, const BBox& box);
    bool intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const;
    bool shadowIntersect(const Ray& r, float tmin, float tmax, float time) const;
    BBox boundingBox(float time0, float time1) const;
    bool randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const;
    //build binary tree-like bounding box hierarchy for fast i.e. O(logn) search time for intersected shape / area.
    Shape* buildBranch(Shape** surfaces, int num_surfaces, int axis = 0);
    
private:
    BBox bbox; //current bounding box
    Shape* left; //left child
    Shape* right; //right child
};

inline BVH::BVH(Shape* orig1, Shape* orig2, const BBox& box) {
    bbox = box;
    left = orig1;
    right = orig2;
}

inline BVH::BVH(Shape* orig1, Shape* orig2) {
    left = orig1;
    right = orig2;
    bbox = surround(orig1 -> boundingBox(0.0f, 0.0f), orig2 -> boundingBox(0.0f, 0.0f));
}

#endif /* defined(__RayTracer__BVH__) */

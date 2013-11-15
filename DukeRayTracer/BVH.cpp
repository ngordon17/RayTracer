//
//  BVH.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "BVH.h"

BVH::BVH() {}

BVH::BVH(Shape** shapes, int num_shapes) {
    if (num_shapes == 1) {*this = BVH(shapes[0], shapes[0]);}
    else if (num_shapes == 2) {*this = BVH(shapes[0], shapes[1]);}
    
    //find midpoint of bbox to use as qsplit pivot
    bbox = shapes[0] -> boundingBox(0.0f, 0.0f);
    for (int i = 1; i < num_shapes; i++) {
        bbox = surround(bbox, shapes[i] -> boundingBox(0.0f, 0.0f));
    }
    Vector3 pivot = (bbox.max() + bbox.min()) / 2.0f;
    
    int midpt = QSplit::qsplit(shapes, num_shapes, pivot.x(), 0);
    
    //create new bounding volume
    left = buildBranch(shapes, midpt, 1);
    right = buildBranch(&shapes[midpt], num_shapes - midpt, 1);
}

BBox BVH::boundingBox(float time0, float time1) const {
    return bbox;
}

bool BVH::intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const {
    if (!(bbox.rayIntersect(r, tmin, tmax))) {return false;}
    //otherwise call intersect on branches
    record.t = tmax;
    
    bool intersect1 = right -> intersect(r, tmin, tmax, time, record);
    bool intersect2 = left -> intersect(r, tmin, record.t, time, record);
    
    return intersect1 || intersect2;
}

bool BVH::shadowIntersect(const Ray& r, float tmin, float tmax, float time) const {
    if (!(bbox.rayIntersect(r, tmin, tmax))) {return false;}
    //otherwise call intersect on branches

    bool intersect1 = right -> shadowIntersect(r, tmin, tmax, time);
    bool intersect2 = left -> shadowIntersect(r, tmin, tmax, time);
    
    return intersect1 || intersect2;
}

bool BVH::randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const {
    //implement??
    return true;
}

Shape* BVH::buildBranch(Shape** shapes, int shape_size, int axis) {
    if (shape_size == 1) {return shapes[0];}
    else if (shape_size == 2) {return new BVH(shapes[0], shapes[1]);}
    
    //find midpoint of bbox to use as qsplit pivot
    BBox box = shapes[0] -> boundingBox(0.0f, 0.0f);
    for (int i = 1; i < shape_size; i++) {
        box = surround(box, shapes[i] -> boundingBox(0.0f, 0.0f));
    }
    Vector3 pivot = (box.max() + box.min()) / 2.0f;
    
    //split according to correct axis
    int midpt = QSplit::qsplit(shapes, shape_size, pivot[axis], axis);
    
    //create new bounding volume
    Shape* left = buildBranch(shapes, midpt, (axis + 1) % 3);
    Shape* right = buildBranch(&shapes[midpt], shape_size - midpt, (axis + 1) %3);
    return new BVH(left, right, box);
}






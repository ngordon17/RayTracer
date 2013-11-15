//
//  Ray.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Ray__
#define __RayTracer__Ray__

#include <iostream>
#include "Vector3.h"

class Ray {
public:
    Ray() {}
    Ray(const Vector3& a, const Vector3& b) {data[0] = a; setDirection(b);}
    Ray(const Ray& r) {*this = r;}
    Ray& operator=(const Ray& orig) {setOrigin(orig.data[0]); setDirection(orig.data[1]); return *this;}
    Vector3 origin() const {return data[0];}
    Vector3 direction() const {return data[1];}
    Vector3 invDirection() const {return data[2];}
    void setOrigin(const Vector3& v) {data[0] = v;}
    void setDirection(const Vector3& v) {
        data[1] = v;
        data[2] = Vector3(1.0f / v.x(), 1.0f / v.y(), 1.0f / v.z());
        posneg[0] = (data[1].x() > 0 ? 0 : 1);
        posneg[1] = (data[1].y() > 0 ? 0 : 1);
        posneg[2] = (data[1].z() > 0 ? 0 : 1);
        
    }
    Vector3 pointAtParameter(float t) const {return data[0] + t*data[1];}
    int posneg[3]; //used for optimization in BVH (BBox.h) implementation
    
private:
    Vector3 data[3];
    
};

#endif /* defined(__RayTracer__Ray__) */

//
//  SolidNoise.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__SolidNoise__
#define __RayTracer__SolidNoise__

#include <iostream>
#include <math.h>
#include "Vector3.h"

class SolidNoise {
public:
    SolidNoise();
    float noise(const Vector3&) const;
    float turbulence(const Vector3& p, int depth) const;
    float dturbulence(const Vector3& p, int depth, float d) const;
    float omega(float t) const;
    Vector3 gamma(int i, int j, int k) const;
    int intGamma(int i, int j) const;
    float knot(int i, int j, int k, Vector3& v) const;
    
private:
    Vector3 grad[16];
    int phi[16];
};







#endif /* defined(__RayTracer__SolidNoise__) */

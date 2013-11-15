//
//  MarbleTexture.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "MarbleTexture.h"

Color MarbleTexture::value(const Vector2& uv, const Vector3& p) const {
    float temp = scale*noise.turbulence(freq*p, octaves);
    float t = 2.0f*fabs(sin(freq*p.x() + temp));
    if (t < 1.0f) {return c1*t + (1.0f - t) * c2;}
    else {t -= 1.0f; return c0*t + (1.0f - t) * c1;}
}
//
//  NoiseTexture.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "NoiseTexture.h"

Color NoiseTexture::value(const Vector2& uv, const Vector3& p) const {
    float t = (1.0f + solid_noise.noise(p* scale)) / 2.0f;
    return t*c0 + (1.0f - t) * c1;
}
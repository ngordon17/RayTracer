//
//  NoiseTexture.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__NoiseTexture__
#define __RayTracer__NoiseTexture__

#include <iostream>
#include <math.h>
#include "Texture.h"
#include "Color.h"
#include "SolidNoise.h"

class NoiseTexture : public Texture {
public:
    NoiseTexture(float scal = 1.0f) {scale = scal; c0 = Color(0.8, 0.0, 0.0); c1 = Color(0.0, 0.0, 0.8);}
    NoiseTexture(const Color& col0, const Color& col1, float scal = 1.0f) {c0 = Color(col0); c1 = Color(col1); scale = float(scal);}
    virtual Color value(const Vector2& uv, const Vector3& p) const;

private:
    float scale;
    Color c0, c1;
    SolidNoise solid_noise;
    
};


#endif /* defined(__RayTracer__NoiseTexture__) */

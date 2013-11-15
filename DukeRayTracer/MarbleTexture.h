//
//  MarbleTexture.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__MarbleTexture__
#define __RayTracer__MarbleTexture__

#include <iostream>
#include <math.h>
#include "Texture.h"
#include "SolidNoise.h"

class MarbleTexture : public Texture {
public:
    MarbleTexture(float stripes_per_unit, float scal = 5.0f, int octs = 8) {
        freq = M_PI * stripes_per_unit;
        scale = scal;
        octaves = octs;
        c0 = Color(0.8, 0.8, 0.8);
        c1 = Color(0.4, 0.2, 0.1);
        c2 = Color(0.06, 0.04, 0.02);
    }
    MarbleTexture(const Color& col0, const Color& col1, const Color& col2, float stripes_per_unit, float scal = 3.0f, int octs = 8) {
        c0 = Color(col0); c1 = Color(col1); c2 = Color(col2);
        freq = M_PI * stripes_per_unit;
        scale = scal;
        octaves = octs;
    }
    virtual Color value(const Vector2& uv, const Vector3&  p) const;
    
private:
    float freq, scale;
    int octaves;
    Color c0, c1, c2;
    SolidNoise noise;
};

#endif /* defined(__RayTracer__MarbleTexture__) */

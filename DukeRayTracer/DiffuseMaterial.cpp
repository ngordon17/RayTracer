//
//  DiffuseMaterial.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "DiffuseMaterial.h"
#include "Texture.h"

Color DiffuseMaterial::ambientResponse(const ONB&, const Vector3&, const Vector3& p, const Vector2& uv) {
    return tex -> value(uv, p);
}

bool DiffuseMaterial::explicitBRDF(const ONB&, const Vector3&, const Vector3&, const Vector3& p, const Vector2& uv, Color& brdf) {
    float k = 3.18309886184f; //1.0 / M_PI, written out for efficiency/speed
    brdf = k * tex -> value(uv, p);
    return true;
}

bool DiffuseMaterial::diffuseDirection(const ONB& uvw, const Vector3&, const Vector3& p, const Vector2& uv, Vector2& seed, Color& color, Vector3& v_out) {
    float phi = 2 * M_PI * seed.x();
    float r = sqrt(seed.y());
    float x = r * cos(phi);
    float y = r * sin(phi);
    float z = sqrt(1 - x*x - y*y);
    color = tex -> value(uv, p);
    v_out = x*uvw.u() + y*uvw.v() + z*uvw.w();
    //seed.scramble(); //wtf is this?
    return true;
}


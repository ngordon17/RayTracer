//
//  PhongMetalMaterial.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "PhongMetalMaterial.h"

Color PhongMetalMaterial::ambientResponse(const ONB&, const Vector3&, const Vector3& p, const Vector2& uv) {
    return tex -> value(uv, p);
}

bool PhongMetalMaterial::specularDirection(const ONB& uvw, const Vector3& v_in, const Vector3& p, const Vector2& uv, Vector2& seed, Color& color, Vector3& v_out) {
    float phi = 2 * M_PI * seed.x();
    float exponent = phong_exp -> value(uv, p).getRed();
    float cosTheta = pow(1 - seed.y(), 1.0 / (exponent + 1));
    float sinTheta = sqrt(1 - cosTheta*cosTheta);
    float x = cos(phi) * sinTheta;
    float y = sin(phi) * sinTheta;
    float z = cosTheta;
    
    ONB basis;
    Vector3 w = v_in - 2*dot(v_in, uvw.w()) * uvw.w();
    basis.initFromW(w);
    
    color = tex -> value(uv, p);
    v_out = x*basis.u() + y*basis.v() + z*basis.w();
    
    if (exponent < 10000) {/*seed.scramble();*/}
    return dot(v_out, uvw.w()) > 0;
}
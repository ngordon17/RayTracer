//
//  DiffSpecMaterial.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/13/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "DiffSpecMaterial.h"

Color DiffSpecMaterial::ambientResponse(const ONB& uvw, const Vector3& v_in, const Vector3& p, const Vector2& uv) {
    float cosine = dot(v_in, uvw.w());
    if (cosine < 0.0f) {cosine = -cosine;}
    float temp1 = 1.0f - cosine;
    float R = R0 + (1.0f - R0) * pow(temp1, 5);
    float P = (R + 0.5f) / 2.0f;
    
    if (drand48() <= P) {return spec_mat -> ambientResponse(uvw, v_in, p, uv);}
    else {return diff_mat -> ambientResponse(uvw, v_in, p, uv);}
}

bool DiffSpecMaterial::explicitBRDF(const ONB& uvw, const Vector3& v0, const Vector3& v1, const Vector3& p, const Vector2& uv, Color& brdf) {
    return diff_mat -> explicitBRDF(uvw, v0, v1, p, uv, brdf);
}

bool DiffSpecMaterial::scatterDirection(const Vector3& v_in, const IntersectRecord& rec, Vector2& seed, Color& color, bool& CEL, float& brdf, Vector3& v_out) {
    float cosine = dot(v_in, rec.uvw.w());
    if (cosine < 0.0f) {cosine = -cosine;}
    float temp1 = 1.0f - cosine;
    float R = R0 + (1.0f - R0) * pow(temp1, 5);
    float P = (R + 0.5f) / 2.0f;
    
    //assume that spec_mat and diff_mat return brdf_scales of 1
    if (drand48() <= P) {
        brdf = R / P;
        return spec_mat -> specularDirection(rec.uvw, v_in, rec.intersection, rec.uv, seed, color, v_out); //scatterDirection doesn't exist for material? this correct?
    }
    else {
        brdf = (1.0f - R) / (1.0f - P);
        return diff_mat -> diffuseDirection(rec.uvw, v_in, rec.intersection, rec.uv, seed, color, v_out); //scatterDirection doesn't exist for material? this correct?
    }
}
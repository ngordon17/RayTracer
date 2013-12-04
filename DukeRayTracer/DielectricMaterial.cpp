//
//  DielectricMaterial.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/13/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "DielectricMaterial.h"
#include <math.h>

DielectricMaterial::DielectricMaterial(float _nt, const Color& _ex) : nt(_nt), extinction(_ex) {
    R0 = (nt - 1.0f) / (nt + 1.0f);
    R0 *= R0;
    float r = log(extinction.getRed());
    float g = log(extinction.getGreen());
    float b = log(extinction.getBlue());
    
    extinction = Color(r, g, b);
}

bool DielectricMaterial::specularDirection(const ONB& uvw, const Vector3& in_dir, const Vector3& texp, const Vector2& uv, Vector2& rseed, Color& ratio, Vector3& reflection) {
    float scale;
    Vector3 normal = uvw.w();
    float cosine = dot(in_dir, normal);
    if (cosine < 0.0f) { //ray incoming
        reflection = reflect(in_dir, uvw.w()); //write this?
        cosine = -cosine;
        //assume dielectrics embedded in air so dont check for total internal reflection
        float temp1 = 1.0f - cosine;
        scale = R0 + (1.0f - R0) * pow(temp1, 5);
    }
    else { //(cosine > 0.0f) so ray is outgoing
        reflection = reflect(in_dir, -uvw.w()); //write this?
        float temp2 = -(dot(in_dir, -normal));
        float root = 1.0f - (nt*nt) * (1.0f - temp2*temp2); //snell's law for cosines, assume n = 1 for air (and/or for incoming material)
        if (root < 0.0f) {scale = 1.0f;} //total internal reflection
        else {
            scale = R0 + (1.0f - R0) * pow(1.0f - cosine, 5);
        }
    }
    //pass back amount of reflected light
    ratio = Color(scale, scale, scale);
    return true;
}


Vector3 DielectricMaterial::reflect(const Vector3& in_dir, const Vector3& normal) {
    float cosine = dot(normal, in_dir); //use dot product to get cos(theta) where theta angle between in_dir and normal
    return in_dir + 2 * cosine * normal; //use cosine to calculate reflected ray (angle of incidence same as exit angle)
}

bool DielectricMaterial::transmissionDirection(const ONB &uvw, const Vector3 &in_dir, const Vector3 &texp, const Vector2 &uv, const Vector2 &rseed, Color& _extinction, float &fresnel_scale, Vector3 &transmission) {
    Vector3 normal = uvw.w();
    float cosine = dot(in_dir, normal);
    if (cosine < 0.0f) {//incoming ray
        float temp1 = 1.0f / nt;
        cosine = -cosine;
        float root = 1.0f - (temp1 * temp1) * (1.0f - cosine * cosine);
        //assume dielectrics embedded in air dont check for total internal refelction, yay physics
        transmission = in_dir * temp1 + normal * (temp1 * cosine - sqrt(root));
        _extinction = Color(1.0f, 1.0f, 1.0f);
    }
    else { //(consine > 0.0f) ray outgoing
        float temp2 = (dot(in_dir, normal));
        float root = 1.0f - (nt*nt) * (1.0f - temp2 * temp2);
        if (root < 0.0f) {return false;} //total internal reflection
        else {transmission = in_dir * nt + -normal * (nt * temp2 - sqrt(root));}
        _extinction = extinction;
    }
    fresnel_scale = 1.0f - (R0 + (1.0f - R0) * pow(1.0f - cosine, 5));
    return true;
}


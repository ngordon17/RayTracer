//
//  SimpleMaterial.cpp
//  DukeRayTracer
//
//  Created by Nicholas Gordon on 12/2/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "SimpleMaterial.h"


SimpleMaterial::SimpleMaterial(Texture* texture, Color kd, Color ks, float phong_exponent, float _n, Color kr) : tex(texture), diffuse(kd), specular(ks), phong_exp(phong_exponent), n(_n), reflective(kr), transmissive(kr){
    R0 = (n - 1.0f) / (n + 1.0f);
    R0 *= R0;
};

Color SimpleMaterial::ambientResponse(const Vector3& p, const Vector2& uv) {
    return tex -> value(uv, p);
}

Color SimpleMaterial::diffuseResponse(const ONB& normal, const Vector3& light_vector) {
    float diffuse_term = dot(normal.w(), normalize(light_vector));
    if (diffuse_term < 0.0) diffuse_term = 0.0;
    if (diffuse_term > 1.0) diffuse_term = 1.0;
    return diffuse * diffuse_term;
}

Color SimpleMaterial::specularResponse(const ONB& normal, const Vector3& light_vector, const Vector3& eye_vector) {
    Vector3 bisector = normalize(light_vector + eye_vector);
    float specular_term = dot(normal.w(), bisector);
    if (specular_term < 0.0) specular_term = 0.0;
    if (specular_term > 1.0) specular_term = 1.0;
    float phong_constant = pow(specular_term, phong_exp);
    return specular * phong_constant;
}

Color SimpleMaterial::emittedRadiance(const ONB& normal, const Vector3& light_vector, const Vector3& eye_vector) {
    return diffuseResponse(normal, light_vector) + specularResponse(normal, light_vector, eye_vector);
}

Color SimpleMaterial::reflectiveResponse(float depth) {
    float r = pow(reflective.getRed(), depth + 1);
    float g = pow(reflective.getGreen(), depth + 1);
    float b = pow(reflective.getBlue(), depth + 1);
    return Color(r, g, b);
}

Color SimpleMaterial::transmissiveResponse(float depth) {
    float r = pow(transmissive.getRed(), depth + 1);
    float g = pow(transmissive.getGreen(), depth + 1);
    float b = pow(transmissive.getBlue(), depth + 1);
    return Color(r, g, b);
}

//http://cse.csusb.edu/tong/courses/cs621/notes/ray.php
Vector3 SimpleMaterial::getReflectionDirection(const ONB& normal, const Vector3& in_dir) {
    Vector3 reflection = normal.w();
    reflection *= -2.0 * dot(in_dir, normal.w());
    reflection += in_dir;
    reflection.normalize();
    return reflection;
    
    /*
    //use dot product to get cos(theta) where theta angle between in_dir and normal
    float cosine = dot(normal.w(), in_dir);
    //use cosine to calculate reflected ray (angle of incidence same as exit angle)
    return in_dir + 2 * cosine * normal.w();
     */
     
}

bool SimpleMaterial::isReflective() {
    return !(reflective.getGreen() == 0 && reflective.getRed() == 0 && reflective.getBlue() == 0);
}

bool SimpleMaterial::isTransmissive() {
    return !(transmissive.getGreen() == 0 && transmissive.getRed() == 0 && transmissive.getBlue() == 0);
}

bool SimpleMaterial::getTransmissionDirection(const ONB &uvw, const Vector3 &in_dir, Color& _extinction, float &fresnel_scale, Vector3& transmission) {
    
    Vector3 normal = uvw.w();
    float cosine = dot(in_dir, normal);
    if (cosine < 0.0f) {//incoming ray
        float temp1 = 1.0f / n;
        cosine = -cosine;
        float root = 1.0f - (temp1 * temp1) * (1.0f - cosine * cosine);
        //assume dielectrics embedded in air dont check for total internal refelction, yay physics
        transmission = in_dir * temp1 + normal * (temp1 * cosine - sqrt(root));
        _extinction = Color(1.0f, 1.0f, 1.0f);
    }
    else { //(cosine > 0.0f) ray outgoing
        float temp2 = (dot(in_dir, normal));
        float root = 1.0f - (n*n) * (1.0f - temp2 * temp2);
        if (root < 0.0f) {false;} //total internal reflection
        else {transmission = in_dir * n + -normal * (n * temp2 - sqrt(root));}
        _extinction = transmissive;
    }
    fresnel_scale = 1.0f - (R0 + (1.0f - R0) * pow(1.0f - cosine, 5));
    return true;
}



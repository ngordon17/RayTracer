//
//  SimpleMaterial.cpp
//  DukeRayTracer
//
//  Created by Nicholas Gordon on 12/2/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "SimpleMaterial.h"


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

Color SimpleMaterial::reflectiveResponse(Color reflection) {
    return reflection * reflective;
}

Vector3 SimpleMaterial::getReflectionDirection(const ONB& normal, const Vector3& in_dir) {
    //use dot product to get cos(theta) where theta angle between in_dir and normal
    float cosine = dot(normal.w(), in_dir);
    //use cosine to calculate reflected ray (angle of incidence same as exit angle)
    return in_dir + 2 * cosine * normal.w();
}


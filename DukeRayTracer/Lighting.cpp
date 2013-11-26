//
//  Lighting.cpp
//  DukeRayTracer
//
//  Created by Dustin Alin on 11/25/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Lighting.h"

Color Lighting::makeLightingColor(Color texture_color, IntersectRecord record, float phong_exponent) {
    Color ambient_color = Color(0.1, 0.1 ,0.1);
    Color diffuse_color = Color(1.0, 1.0, 1.0);
    Color specular_color = Color(1.0, 1.0, 1.0);
        
    Vector3 vertex_to_light_vector = light_source - record.intersection;
    Vector3 normalized_vertex_to_light_vector = normalize(vertex_to_light_vector);
    Vector3 vertex_to_eye_vector = eye - record.intersection;
    Vector3 bisector = normalize(vertex_to_light_vector + vertex_to_eye_vector);
        
    float diffuse_term = dot(record.normal, normalized_vertex_to_light_vector);
    if (diffuse_term < 0.0) diffuse_term = 0.0;
    if (diffuse_term > 1.0) diffuse_term = 1.0;
        
    float specular_term = dot(record.normal, bisector);
    if (specular_term < 0.0) specular_term = 0.0;
    if (specular_term > 1.0) specular_term = 1.0;
        
    float phong_constant = pow(specular_term, phong_exponent);
    Color lighting_color = ambient_color + (diffuse_color * diffuse_term) + (specular_color * phong_constant);
    Color mix_color = (texture_color + lighting_color)/2.0;
        
    return mix_color;
}
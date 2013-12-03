//
//  SimpleMaterial.h
//  DukeRayTracer
//
//  Created by Nicholas Gordon on 12/2/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#import "Color.h"
#import "Vector3.h"
#import "Vector2.h"
#import "Shape.h"
#import "Texture.h"
#import "Material.h"
#ifndef DukeRayTracer_SimpleMaterial_h
#define DukeRayTracer_SimpleMaterial_h

class SimpleMaterial : Material {

public:
    SimpleMaterial(Texture* texture, Color kd, Color ks, float phong_exponent, float _n, Color kr) : tex(texture), diffuse(kd), specular(ks), phong_exp(phong_exponent), n(_n), reflective(kr) {};
    Color ambientResponse(const Vector3& p, const Vector2& uv);
    Color diffuseResponse(const ONB& normal, const Vector3& light_vector);
    Color specularResponse(const ONB& normal, const Vector3& light_vector, const Vector3& eye_vector);
    Color emittedRadiance(const ONB& normal, const Vector3& light_vector, const Vector3& eye_vector);
    Color reflectiveResponse(Color reflection);
    Vector3 getReflectionDirection(const ONB& normal, const Vector3& in_dir);
    
private:
    Texture* tex;
    Color diffuse;
    Color specular;
    Color reflective;
    float phong_exp;
    float n; //refractive index (0 for totally reflective)
};


#endif


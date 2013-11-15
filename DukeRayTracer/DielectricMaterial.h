//
//  DielectricMaterial.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/13/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__DielectricMaterial__
#define __RayTracer__DielectricMaterial__

#include <iostream>
#include "Material.h"
#include "Color.h"
#include "Vector3.h"
#include "Texture.h"

class DielectricMaterial : public Material {
public:
    DielectricMaterial() {}
    DielectricMaterial(float nt, const Color& _ex);
    //incident vector, texture point, texture coordinate, random seed
    bool specularDirection(const ONB& uvw, const Vector3& in_dir, const Vector3& texp, const Vector2& uv, Vector2& rseed, Color& ratio, Vector3& reflection);
    //incident unit vector, texture point, texture coordinate, random seed
    bool transmissionDirection(const ONB& uvw, const Vector3& in_dir, const Vector3& texp, const Vector2& uv, const Vector2& rseed, Color& _extinction, float& fresnel_scale, Vector3& transmission);
    Vector3 reflect(const Vector3& in_dir, const Vector3& normal);

private:
    float R0;
    float nt; //refractive index (used to implement reflect with Snell's Law)
    Color extinction;
    
};




#endif /* defined(__RayTracer__DielectricMaterial__) */

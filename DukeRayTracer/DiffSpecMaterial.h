//
//  DiffSpecMaterial.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/13/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__DiffSpecMaterial__
#define __RayTracer__DiffSpecMaterial__

#include <iostream>
#include "Material.h"
#include "Shape.h"


class DiffSpecMaterial : public Material {
public:
    DiffSpecMaterial() {}
    DiffSpecMaterial(Material* d, Material* s, float r0 = .05f) {diff_mat = d; spec_mat = s; R0 = r0;}
    //ONB of hit point, incident direction, texture point, texture coordinate
    virtual Color ambientResponse(const ONB&, const Vector3&, const Vector3&, const Vector2&);
    //ONG of hit point, outgoing vector v0, outgoing vector v1, texture point, texture coordinate
    virtual bool explicitBRDF(const ONB&, const Vector3&, const Vector3&, const Vector3&, const Vector2&, Color&);
    //incident vector, intersection to shade, random seed, color to attenuate by, count emitted light?, brdf scale, scattered direction
    virtual bool scatterDirection(const Vector3&, const IntersectRecord&, Vector2&, Color&, bool&, float&, Vector3&);
    Texture* getTexture() {return NULL;}
    
private:
    float R0;
    Material* diff_mat;
    Material* spec_mat;
    
    
    
};

#endif /* defined(__RayTracer__DiffSpecMaterial__) */

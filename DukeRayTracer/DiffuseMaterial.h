//
//  DiffuseMaterial.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__DiffuseMaterial__
#define __RayTracer__DiffuseMaterial__

#include <iostream>
#include "Material.h"
#include "Texture.h"

class DiffuseMaterial : public Material {
public:
    DiffuseMaterial(Texture *t) {tex = t;}
    //incident direction, texture point, texture coordinate
    virtual Color ambientResponse(const ONB&, const Vector3&, const Vector3&, const Vector2&);
    //unit vector v1, unit vector v0, texture point, texture coordinate
    virtual bool explicitBRDF(const ONB&, const Vector3&, const Vector3&, const Vector3&, const Vector2&, Color&);
    //incident unit vector, texture point, texture coordinate, random seed
    virtual bool diffuseDirection(const ONB&, const Vector3&, const Vector3&, const Vector2&, Vector2&, Color&, Vector3&);
    Texture* getTexture() {return tex;}
    
private:
    Texture* tex;
};

#endif /* defined(__RayTracer__DiffuseMaterial__) */

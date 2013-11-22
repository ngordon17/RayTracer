//
//  PhongMetalMaterial.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__PhongMetalMaterial__
#define __RayTracer__PhongMetalMaterial__

#include <iostream>
#include "Material.h"
#include "Texture.h"

class PhongMetalMaterial : public Material {
public:
    PhongMetalMaterial(Texture* rt, Texture* et) {tex = rt; phong_exp = et;}
    //incident direction, texture point, texture coordinate
    virtual Color ambientResponse(const ONB&, const Vector3&, const Vector3&, const Vector2&);
    //incident unit vector, texture point, texture coordinate, random seed
    virtual bool specularDirection(const ONB&, const Vector3&, const Vector3&, const Vector2&, Vector2&, Color&, Vector3&);
    Texture* getTexture() {return tex;}
    
private:
    Texture* tex;
    Texture* phong_exp;
    
};







#endif /* defined(__RayTracer__PhongMetalMaterial__) */

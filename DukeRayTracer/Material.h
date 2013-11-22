//
//  Material.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Material__
#define __RayTracer__Material__

#include <iostream>
#include "Vector2.h"
#include "Color.h"
#include "ONB.h"
#include "Ray.h"
#include "Texture.h"

class Material {
public:
    virtual bool emits() const {return false;}
    //ONB of hit point, outgoing light direction, texture point, texture coordinate
    virtual Color emittedRadiance(const ONB&, const Vector3&, const Vector3&, const Vector2&) {return Color(0.0f, 0.0f, 0.0f);}
    //ONB of hit point, incident direction, texture point, texture coordinate
    virtual Color ambientResponse(const ONB&, const Vector3&, const Vector3&, const Vector2&) {return Color(0.0f, 0.0f, 0.0f);}
    //ONB of hit point, outgoing vector v0, outgoing vectorv1, texture point, texture coordinate
    virtual bool explicitBRDF(const ONB&, const Vector3&, const Vector3&, const Vector3&, const Vector2&, Color&) {return false;}
    //ONB of hit point, incident vector, texture point, texture coordinate, random seen, value returned by texture
    virtual bool diffuseDirection(const ONB&, const Vector3&, const Vector3&, const Vector2&, Vector2&, Color&, Vector3&) {return false;}
    //ONB of hit point, incident vector, texture point, texture coordinate, random seed, value returned by texutre
    virtual bool specularDirection(const ONB&, const Vector3&, const Vector3&, const Vector2&, Vector2&, Color&, Vector3&) {return false;}
    //ONB of hit point, incident unit vector, texture point, texture coordinate, random seed, extinction color, fresnel_scale
    virtual bool transmissionDirection(const ONB&, const Vector3&, const Vector3&, const Vector2&, const Vector2&, Color&, float&, Vector3&) {return false;}
    virtual bool isDiffuse() {return false;}
    virtual bool isSpecular() {return false;}
    virtual bool isTransmissive() {return false;}
    virtual int causticPhotons() {return 0;}
    virtual int globalPhotons() {return 0;}
    virtual Color photonColor() {return Color(0.0f, 0.0f, 0.0f);}
    virtual Texture* getTexture() = 0;
};

#endif /* defined(__RayTracer__Material__) */

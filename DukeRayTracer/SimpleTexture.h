//
//  SimpleTexture.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__SimpleTexture__
#define __RayTracer__SimpleTexture__

#include <iostream>
#include "Texture.h"

//use for constant color objects
class SimpleTexture : public Texture {
public:
    SimpleTexture(Color c) {color = c;}
    virtual Color value(const Vector2&, const Vector3&) const {return color;}
private:
    Color color;
};




#endif /* defined(__RayTracer__SimpleTexture__) */

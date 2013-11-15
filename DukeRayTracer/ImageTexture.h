//
//  ImageTexture.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__ImageTexture__
#define __RayTracer__ImageTexture__

#include <iostream>
#include "Texture.h"
#include "Image.h"

class ImageTexture : public Texture {
public:
    ImageTexture(char* file_name);
    ~ImageTexture(void);
    virtual Color value(const Vector2& uv, const Vector3& p) const;
    
private:
    Image* image;

};

#endif /* defined(__RayTracer__ImageTexture__) */

//
//  ImageTexture.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "ImageTexture.h"
#include "Image.h"

ImageTexture::ImageTexture(char* file_path) {
    image = new Image();
    image -> readPPM(file_path);
}

ImageTexture::~ImageTexture(void) {
    delete image;
}


Color ImageTexture::value(const Vector2& uv, const Vector3& p) const {
    float u = uv.x() - int(uv.x());
    float v = uv.y() - int(uv.y());
    u *= (image -> width() - 3);
    v *= (image -> height() - 3);
    
    int iu = (int) u;
    int iv = (int) v;
    
    float tu = u - iu;
    float tv = v - iv;
    
    return image -> getPixel(iu, iv) * (1 - tu) * (1 - tv) +
        image -> getPixel(iu + 1, iv) * tu * (1 - tv) +
        image -> getPixel(iu, iv + 1) * (1 - tu) * tv +
        image -> getPixel(iu + 1, iv + 1) * tu * tv;
    
}
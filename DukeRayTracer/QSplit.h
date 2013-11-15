//
//  Qsplit.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/12/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Qsplit__
#define __RayTracer__Qsplit__

#include <iostream>
#include "BBox.h"
#include "Shape.h"

class QSplit {
public:
    static int qsplit(Shape** list, int size, float pivot_val, int axis) {
        BBox bbox;
        double centroid;
        int rv = 0;
        
        for (int i = 0; i < size; i++) {
            bbox = list[i] -> boundingBox(0.0f, 0.0f);
            centroid = ((bbox.min())[axis] + (bbox.max())[axis]) / 2.0f;
            if (centroid < pivot_val) {
                Shape* temp = list[i];
                list[i] = list[rv];
                list[rv] = temp;
                rv++;
            }
        }
        if (rv == 0 || rv == size) {rv = size / 2;}
        return rv;
    }
};



#endif /* defined(__RayTracer__Qsplit__) */

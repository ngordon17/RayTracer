//
//  Lighting.cpp
//  DukeRayTracer
//
//  Created by Dustin Alin on 11/25/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Lighting.h"


Color Lighting::getIntensity() {
    return I;
}

Vector3 Lighting::getLightVector(IntersectRecord record) {
    return light_source - record.intersection;
}

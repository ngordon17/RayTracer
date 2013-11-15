//
//  Sample.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Sample__
#define __RayTracer__Sample__

#include <iostream>
#include "Vector2.h"
#include <math.h>
#include <stdlib.h>

//2D sampling
void random(Vector2* samples, int num_samples);
void jitter(Vector2* samples, int num_samples); //assumes num_samples perfect square
void nrooks(Vector2* samples, int num_samples);
void multiJitter(Vector2* samples, int num_samples); //assumes num_samples perfect square
void shuffle(Vector2* samples, int num_samples);
void boxFilter(Vector2* samples, int num_samples);
void tentFilter(Vector2* samples, int num_samples);
void cubicSplineFilter(Vector2* samples, int num_samples);


//1D sampling

void random(float* samples, int num_samples);
void jitter(float* samples, int num_samples);
void shuffle(float * samples, int num_samples);

//helpers for cubic spline filter
inline float solve(float r) {
    float u = r;
    for (int i = 0; i < 5; i++) {
        u = (11.0f * r + u * u * (6.0f + u * (8.0f - 9.0f * u))) /
        (4.0f + 12.0f * u * (1.0f + u * (1.0f + u * (1.0f - u))));
    }
    return u;
}


inline float cubicFilter(float x) {
    if (x < 1.0f / 24.0f) {return pow(24*x, 0.25f) - 2.0f;}
    else if (x < 0.5) {return solve(24.0f * (x - 1.0f / 24.0f) / 11.0f) - 1.0f;}
    else {return 2 - pow(24.0f * (1.0f - x), 0.25f);}
}

#endif /* defined(__RayTracer__Sample__) */

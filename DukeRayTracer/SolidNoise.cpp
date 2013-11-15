//
//  SolidNoise.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "SolidNoise.h"

SolidNoise::SolidNoise() {

    grad[0] = Vector3(1, 1, 0);   grad[8] = Vector3(0, 1, 1);
    grad[1] = Vector3(-1, 1, 0);  grad[9] = Vector3(0, -1, 1);
    grad[2] = Vector3(1, -1, 0);  grad[10] = Vector3(0, 1, -1);
    grad[3] = Vector3(-1, -1, 0); grad[11] = Vector3(0, -1, -1);
    grad[4] = Vector3(1, 0, 1);   grad[12] = Vector3(1, 1, 0);
    grad[5] = Vector3(-1, 0, 1);  grad[13] = Vector3(-1, 1, 0);
    grad[6] = Vector3(1, 0, -1);  grad[14] = Vector3(0, -1, 1);
    grad[7] = Vector3(-1, 0, -1); grad[15] = Vector3(0, -1, -1);
    
    for (int i = 0; i < 16; i++) {
        phi[i] = i;
        //shuffle phi
        for (int j = 14; j >= 0; j--) {
            int target = int((double)rand()/RAND_MAX * i);
            int temp = phi[i + 1];
            phi[i + 1] = phi[target];
            phi[target] = temp;
        }
    }
}

float SolidNoise::turbulence(const Vector3& p, int depth) const {
    float sum = 0.0f;
    float weight = 1.0f;
    Vector3 ptemp(p);
    sum = fabs(noise(ptemp));
    
    for (int i = 1; i < depth ; i++) {
        weight *= 2;
        ptemp.setX(p.x() * weight);
        ptemp.setY(p.y() * weight);
        ptemp.setZ(p.z() * weight);
        sum +=fabs(noise(ptemp)) / weight;
    }
    return sum;
}

float SolidNoise::dturbulence(const Vector3& p, int depth, float d) const {
    float sum = 0.0f;
    float weight = 1.0f;
    Vector3 ptemp(p);
    sum += fabs(noise(ptemp)) / d;
    
    for (int i = 1; i < depth; i++) {
        weight *= d;
        ptemp.setX(p.x() * weight);
        ptemp.setY(p.y() * weight);
        ptemp.setZ(p.z() * weight);
        sum +=fabs(noise(ptemp)) / weight;
    }
    return sum;
}

float SolidNoise::noise(const Vector3& p) const {
    int fi = int(floor(p.x()));
    int fj = int(floor(p.y()));
    int fk = int(floor(p.z()));
    float fu = p.x() - float(fi);
    float fv = p.y() - float(fj);
    float fw = p.z() - float(fk);
    float sum = 0.0f;
    
    Vector3 v = Vector3(fu, fv, fw);
    sum += knot(fi, fj, fk, v);
    v = Vector3(fu - 1, fv, fw);
    sum += knot(fi + 1, fj, fk, v);
    v = Vector3(fu, fv - 1, fw);
    sum += knot(fi, fj + 1, fk, v);
    v = Vector3(fu, fv, fw - 1);
    sum += knot(fi, fj, fk + 1, v);
    v = Vector3(fu - 1, fv - 1, fw);
    sum += knot(fi + 1, fj + 1, fk, v);
    v = Vector3(fu - 1, fv, fw - 1);
    sum += knot(fi + 1, fj , fk + 1, v);
    v = Vector3(fu, fv - 1, fw - 1);
    sum += knot(fi, fj + 1, fk + 1, v);
    v = Vector3(fu - 1, fv - 1, fw - 1);
    sum += knot(fi + 1, fj + 1, fk + 1, v);
    return sum;
}

float SolidNoise::omega(float t) const {
    t = (t > 0.0f) ? t : -t;
    //assume t is in [-1, 1]
    return (-6.0f*pow(t, 5) + 15.0f*pow(t, 4) - 10.0f*pow(t, 3) + 1.0f);
}

Vector3 SolidNoise::gamma(int i, int j, int k) const {
    return grad[phi[abs(i + phi[abs(j + phi[abs(k) % 16]) % 16]) % 16]];
}

int SolidNoise::intGamma(int i, int j) const {
    return phi[abs(i + phi[abs(j) % 16]) % 16];
}

float SolidNoise::knot(int i, int j, int k, Vector3& v) const {
    return omega(v.x()) * omega(v.y()) * omega(v.z()) * dot(gamma(i, j, k), v);
}
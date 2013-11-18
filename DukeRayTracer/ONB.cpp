//
//  ONB.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "ONB.h"
#define ONB_EPSILON 0.001f

void ONB::initFromU(const Vector3& u) {
    Vector3 t1(1.0f, 0.0f, 0.0f);
    Vector3 t2(0.0f, 1.0f, 0.0f);
    U = normalize(u);
    V = cross(U, t1);
    //check if V is 0, this means t1 was linear with U so cross with t2 instead
    if (V.magnitude() < ONB_EPSILON) {V = cross(U, t2);}
    W = cross(U,V);
}

void ONB::initFromV(const Vector3& v) {
    Vector3 t1(1.0f, 0.0f, 0.0f);
    Vector3 t2(0.0f, 1.0f, 0.0f);
    V = normalize(v);
    U = cross(V, t1);
    if (U.magnitude() < ONB_EPSILON) {U = cross(V, t2);}
    W = cross(U,V);
}

void ONB::initFromW(const Vector3& w) {
    Vector3 t1(1.0f, 0.0f, 0.0f);
    Vector3 t2(0.0f, 1.0f, 0.0f);
    W = normalize(w);
    U = cross(W, t1);
    if (U.magnitude() < ONB_EPSILON) {U = cross(W, t2);}
    V = cross(W, U);
}

void ONB::initFromUV(const Vector3& u, const Vector3& v) {
    U = normalize(u);
    W = normalize(cross(u, v));
    V = cross(W, U);
}

void ONB::initFromVU(const Vector3& v, const Vector3& u) {
    V = normalize(v);
    W = normalize(cross(u, v));
    U = cross(V, W);
}

void ONB::initFromUW(const Vector3& u, const Vector3& w) {
    U = normalize(u);
    V = normalize(cross(w, u));
    W = cross(U, V);
}

void ONB::initFromWU(const Vector3& w, const Vector3& u) {
    W = normalize(w);
    V = normalize(cross(w, u));
    U = cross(V, W);
}

void ONB::initFromVW(const Vector3& v, const Vector3& w) {
    V = normalize(v);
    U = normalize(cross(v, w));
    W = cross(U, V);
}

void ONB::initFromWV(const Vector3& w, const Vector3& v) {
    W = normalize(w);
    U = normalize(cross(v, w));
    V = cross(W, U);
}

//checks if the u, v, and w vectors of two orthnormal bases are equal to each other
bool operator==(const ONB& o1, const ONB& o2) {
    return (o1.u() == o2.u() && o1.v() == o2.v() && o1.w() == o2.w());
}






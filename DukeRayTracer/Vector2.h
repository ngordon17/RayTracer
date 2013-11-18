//
//  Vector2.h
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Vector2__
#define __RayTracer__Vector2__

#include <math.h>
#include <iostream>

/*
 This class is nearly the same as Vector3 except it is a two-dimensional vector
 rather than a three-dimensional vector.
 */
class Vector2 {
public:
    Vector2() {}
    Vector2(float x, float y);
    Vector2(const Vector2 &v) { *this = v; }
    
    float x() const { return e[0]; }
    float y() const { return e[1]; }
    void setX(float x) { e[0] = x; }
    void setY(float y) { e[1] = y; }
    
    const Vector2& operator+() const;
    Vector2 operator-() const;
    
    float magnitude() const;
    float squaredMagnitude() const;
    void normalize();
    
    float minComponent() const;
    float maxComponent() const;
    float minAbsComponent() const;
    float maxAbsComponent() const;

    friend bool operator==(const Vector2& v1, const Vector2& v2);
    friend bool operator!=(const Vector2& v1, const Vector2& v2);
    
    friend Vector2 operator+(const Vector2& v1, const Vector2& v2);
    friend Vector2 operator-(const Vector2& v1, const Vector2& v2);
    friend Vector2 operator/(const Vector2& v1, float scal);
    friend Vector2 operator*(const Vector2& v1, float scal);
    friend Vector2 operator*(float scalar, const Vector2& v1);
    
    Vector2& operator=(const Vector2& v2);
    Vector2& operator+=(const Vector2& v2);
    Vector2& operator-=(const Vector2& v2);
    Vector2& operator*=(const float scal);
    Vector2& operator/=(const float scal);
    
    friend float determinant(const Vector2& v1, const Vector2& v2);
    friend float dot(const Vector2& v1, const Vector2& v2);
    friend float findAngle(const Vector2& v1, const Vector2& v2);
    friend Vector2 normalize(const Vector2& v);
    
private:
    float e[2];
};

#endif /* defined(__RayTracer__Vector2__) */

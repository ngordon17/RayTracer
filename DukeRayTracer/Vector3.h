//
//  Vector3.h
//  Ray Tracer
//
//  Created by Dustin Alin on 11/3/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Vector3__
#define __RayTracer__Vector3__

#include <math.h>
#include <iostream>

//no pointers, references in some cases.

class Vector3 {
public:
    Vector3() {}
    Vector3(float x, float y, float z);
    Vector3(const Vector3& v) { *this = v; }
    
    //getters and setters for the x, y, and z components of a 3D vector
    float x() const { return e[0]; }
    float y() const { return e[1]; }
    float z() const { return e[2]; }
    void setX(float x) { e[0] = x; }
    void setY(float y) { e[1] = y; }
    void setZ(float z) { e[2] = z; }
    
    const Vector3& operator+() const;
    Vector3 operator-() const;
    float operator[](int i) const {return e[i];}
    float& operator[](int i) {return e[i];}
    
    float magnitude() const;
    float squaredMagnitude() const;
    void normalize();
    
    float minComponent() const;
    float maxComponent() const;
    float minAbsComponent() const;
    float maxAbsComponent() const;
    
    friend bool operator==(const Vector3& v1, const Vector3& v2);
    friend bool operator!=(const Vector3& v1, const Vector3& v2);
    
    /*
     These are arithmetic operations that result in the creation of a new Vector3. This utilizes
     overloading operators so that mathematical operations could be used directly on 
     Vector3 objects.
     */
    friend Vector3 operator+(const Vector3& v1, const Vector3& v2);
    friend Vector3 operator-(const Vector3& v1, const Vector3& v2);
    friend Vector3 operator/(const Vector3& v1, float scal);
    friend Vector3 operator*(const Vector3& v1, float scal);
    friend Vector3 operator*(float scalar, const Vector3 &v1);
    
    /*
     These are arithmetic operations that operate on an existing vector. Returns a 
     reference to the vector being operated on.
     */
    Vector3& operator=(const Vector3& v2);
    Vector3& operator+=(const Vector3& v2);
    Vector3& operator-=(const Vector3& v2);
    Vector3& operator*=(const float scal);
    Vector3& operator/=(const float scal);
    
    friend Vector3 cross(const Vector3& v1, const Vector3& v2);
    friend float dot(const Vector3& v1, const Vector3& v2);
    friend float findAngle(const Vector3& v1, const Vector3& v2);
    friend float tripleProduct(const Vector3& v1, const Vector3& v2, const Vector3& v3);
    friend Vector3 normalize(const Vector3& v);
    
private:
    float e[3];
    
};

#endif /* defined(__Ray_Tracer__Vector3__) */

//
//  Matrix.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__Matrix__
#define __RayTracer__Matrix__

#include <iostream>
#include <iomanip>
#include <stdio.h>
#include <math.h>
#include "Vector3.h"



class Matrix {
public:
    Matrix() {}
    Matrix(const Matrix& mat);
    void invert();
    void transpose();
    Matrix getInverse() const;
    Matrix getTranspose() const;
    float getDeterminant();
    
    Matrix& operator+=(const Matrix& right_op);
    Matrix& operator-=(const Matrix& right_op);
    Matrix& operator*=(const Matrix& right_op);
    Matrix& operator*=(float right_op);
    
    friend Matrix operator-(const Matrix& left_op, const Matrix& right_op);
    friend Matrix operator+(const Matrix& left_op, const Matrix& right_op);
    friend Matrix operator*(const Matrix& left_op, const Matrix& right_op);
    friend Matrix operator*(const Matrix& left_op, float right_op);
    
    friend Vector3 operator*(const Matrix& left_op, const Vector3& right_op);
    
    friend Vector3 transformLoc(const Matrix& left_op, const Vector3& right_op);
    friend Vector3 transformVec(const Matrix& left_op, const Vector3& right_op);
    
    friend Matrix getZeroMatrix();
    friend Matrix getIdentityMatrix();
    friend Matrix getTranslationMatrix(float xt, float yt, float zt);
    friend Matrix getScaleMatrix(float xs, float ys, float zs);
    friend Matrix getRotationMatrix(const Vector3& axis, float angle);
    friend Matrix getXRotationMatrix(float angle);
    friend Matrix getYRotationMatrix(float angle);
    friend Matrix getZRotationMatrix(float angle);
    friend Matrix getViewMatrix(const Vector3& eye, const Vector3& gaze, const Vector3& up);
    
    friend std::ostream& operator<<(std::ostream& out, const Matrix& right_op);
    
private:
    float matrix[4][4];
};

//3x3 matrix determinant -- helper
inline float det3 (float a, float b, float c, float d, float e, float f, float g, float h, float i) {
    return a*e*i + d*h*c + g*b*c - g*e*c - d*b*i - a*h*f;
}

#endif /* defined(__RayTracer__Matrix__) */

//
//  Matrix.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Matrix.h"

Matrix::Matrix(const Matrix& mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] = mat.matrix[i][j];
        }
    }
}

void Matrix::invert() {
    float det = getDeterminant();
    Matrix inverse;
    inverse.matrix[0][0] = det3(matrix[1][1], matrix[1][2], matrix[1][3], matrix[2][1], matrix[2][2], matrix[2][3],
                                matrix[3][1], matrix[3][2], matrix[3][3]) / det;
    inverse.matrix[0][1] = -det3(matrix[0][1], matrix[0][2], matrix[0][3], matrix[2][1], matrix[2][2], matrix[2][3],
                                 matrix[3][1], matrix[3][2], matrix[3][3]) / det;
    inverse.matrix[0][2] = det3(matrix[0][1], matrix[0][2], matrix[0][3], matrix[1][1], matrix[1][2], matrix[1][3],
                                matrix[3][1], matrix[3][2], matrix[3][3]) / det;
    inverse.matrix[0][3] = -det3(matrix[0][1], matrix[0][2], matrix[0][3], matrix[1][1], matrix[1][2], matrix[1][3],
                                 matrix[2][1], matrix[2][2], matrix[2][3]) / det;
    
    inverse.matrix[1][0] = -det3(matrix[1][0], matrix[1][2], matrix[1][3], matrix[2][0], matrix[2][2], matrix[2][3],
                                 matrix[3][0], matrix[3][2], matrix[3][3]) / det;
    inverse.matrix[1][1] = det3(matrix[0][0], matrix[0][2], matrix[0][3], matrix[1][0], matrix[1][2], matrix[1][3],
                                matrix[3][0], matrix[3][2], matrix[3][3]) / det;
    inverse.matrix[1][2] = -det3(matrix[0][0], matrix[0][2], matrix[0][3], matrix[1][0], matrix[1][2], matrix[1][3],
                                 matrix[3][0], matrix[3][2], matrix[3][3]) / det;
    inverse.matrix[1][3] = det3(matrix[0][0], matrix[0][2], matrix[0][3], matrix[1][0], matrix[1][2], matrix[1][3],
                                matrix[2][0], matrix[2][2], matrix[2][3]) / det;
    
    inverse.matrix[2][0] = det3(matrix[1][0], matrix[1][1], matrix[1][3], matrix[2][0], matrix[2][1], matrix[2][3],
                                matrix[3][0], matrix[3][1], matrix[3][3]) / det;
    inverse.matrix[2][1] = -det3(matrix[0][0], matrix[0][1], matrix[0][3], matrix[2][0], matrix[2][1], matrix[2][3],
                                 matrix[3][0], matrix[3][1], matrix[3][3]) / det;
    inverse.matrix[2][2] = det3(matrix[0][0], matrix[0][1], matrix[0][3], matrix[1][0], matrix[1][1], matrix[1][3],
                                matrix[3][0], matrix[3][1], matrix[3][3]) / det;
    inverse.matrix[2][3] = -det3(matrix[0][0], matrix[0][1], matrix[0][3], matrix[1][0], matrix[1][1], matrix[1][3],
                                 matrix[2][0], matrix[2][1], matrix[2][3]) / det;
    
    inverse.matrix[3][0] = -det3(matrix[1][0], matrix[1][1], matrix[1][2], matrix[2][0], matrix[2][1], matrix[2][2],
                                 matrix[3][0], matrix[3][1], matrix[3][2]) / det;
    inverse.matrix[3][1] = det3(matrix[0][0], matrix[0][1], matrix[0][2], matrix[2][0], matrix[2][1], matrix[2][2],
                                matrix[3][0], matrix[3][1], matrix[3][2]) / det;
    inverse.matrix[3][2] = -det3(matrix[0][0], matrix[0][1], matrix[0][2], matrix[1][0], matrix[1][1], matrix[1][2],
                                 matrix[3][0], matrix[3][1], matrix[3][2]) / det;
    inverse.matrix[3][3] = det3(matrix[0][0], matrix[0][1], matrix[0][2], matrix[1][0], matrix[1][1], matrix[1][2],
                                matrix[2][0], matrix[2][1], matrix[2][2]) / det;
    *this = inverse;
}

void Matrix::transpose() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float temp = matrix[i][j];
            matrix[i][j] = matrix[j][i];
            matrix[j][i] = temp;
        }
    }
}

Matrix Matrix::getInverse() const {
    Matrix ret = *this;
    ret.invert();
    return ret;
}

Matrix Matrix::getTranspose() const {
    Matrix ret = *this;
    ret.transpose();
    return ret;
    
}

float Matrix::getDeterminant() {
    float det;
    det = matrix[0][0] * det3(matrix[1][1], matrix[1][2], matrix[1][3], matrix[2][1], matrix[2][2], matrix[2][3],
                              matrix[3][1], matrix[3][2], matrix[3][3]);
    det -= matrix[0][1] * det3(matrix[1][0], matrix[1][2], matrix[1][3], matrix[2][0], matrix[2][2], matrix[2][3],
                               matrix[3][0], matrix[3][2], matrix[3][3]);
    det += matrix[0][2] * det3(matrix[1][0], matrix[1][1], matrix[1][3], matrix[2][0], matrix[2][1], matrix[2][3],
                               matrix[3][0], matrix[3][1], matrix[3][3]);
    det -= matrix[0][3] * det3(matrix[1][0], matrix[1][1], matrix[1][2], matrix[2][0], matrix[2][1], matrix[2][2],
                               matrix[3][0], matrix[3][1], matrix[3][2]);
    return det;
}

Matrix& Matrix::operator+=(const Matrix& right_op) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] += right_op.matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator-=(const Matrix& right_op) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] -= right_op.matrix[i][j];
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(const Matrix& right_op) {
    Matrix ret = *this; //copy?
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0;
            for (int k = 0; k < 4; k++) {
                sum += ret.matrix[i][k] * right_op.matrix[k][j];
            }
            matrix[i][j] = sum;
        }
    }
    return *this;
}

Matrix& Matrix::operator*=(float right_op) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            matrix[i][j] *= right_op;
        }
    }
    return *this;
}

Matrix operator-(const Matrix& left_op, const Matrix& right_op) {
    Matrix ret;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ret.matrix[i][j] = left_op.matrix[i][j] - right_op.matrix[i][j];
        }
    }
    return ret;
}

Matrix operator+(const Matrix& left_op, const Matrix& right_op) {
    Matrix ret;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ret.matrix[i][j] = left_op.matrix[i][j] + right_op.matrix[i][j];
        }
    }
    return ret;
}

Matrix operator*(const Matrix& left_op, const Matrix& right_op) {
    Matrix ret;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            float sum = 0;
            for (int k = 0; k < 4; k++) {
                sum += left_op.matrix[i][k] * right_op.matrix[k][j];
            }
            ret.matrix[i][j] = sum;
        }
    }
    return ret;
    
}

Matrix operator*(const Matrix& left_op, float right_op) {
    Matrix ret;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ret.matrix[i][j] *= right_op;
        }
    }
    return ret;
}

Vector3 operator*(const Matrix& left_op, const Vector3& right_op) {
    Vector3 ret;
    
    ret[0] = right_op[0] * left_op.matrix[0][0] + right_op[1] * left_op.matrix[0][1] +
        right_op[2] * left_op.matrix[0][2] + left_op.matrix[0][3];
    ret[1] = right_op[0] * left_op.matrix[1][0] + right_op[1] * left_op.matrix[1][1] +
        right_op[2] * left_op.matrix[1][2] + left_op.matrix[1][3];
    ret[2] = right_op[0] * left_op.matrix[2][0] + right_op[1] * left_op.matrix[2][1] +
        right_op[2] * left_op.matrix[2][2] + left_op.matrix[2][3];
    
    float temp = right_op[0] * left_op.matrix[3][0] + right_op[1] * left_op.matrix[3][1] +
        right_op[2] * left_op.matrix[3][2] + left_op.matrix[3][3];
    
    ret /= temp;
    return ret;
}

Vector3 transformLoc(const Matrix& left_op, const Vector3& right_op) {
    return left_op * right_op;
}


Vector3 transformVec(const Matrix& left_op, const Vector3& right_op) {
    Vector3 ret;
    ret[0] = right_op[0] * left_op.matrix[0][0] + right_op[1] *left_op.matrix[0][1] +
        right_op[2] * left_op.matrix[0][2];
    ret[1] = right_op[0] * left_op.matrix[1][0] + right_op[1] * left_op.matrix[1][1] +
        right_op[2] * left_op.matrix[1][2];
    ret[2] = right_op[0] * left_op.matrix[2][0] + right_op[1] * left_op.matrix[2][1] +
        right_op[2] * left_op.matrix[2][2];
    return ret;
}

Matrix getZeroMatrix() {
    Matrix ret;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            ret.matrix[i][j] = 0.0f;
        }
    }
    return ret;
}

Matrix getIdentityMatrix() {
    Matrix ret;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (i == j) {ret.matrix[i][j] = 1.0f;}
            else {ret.matrix[i][j] = 0.0f;}
        }
    }
    return ret;
}

Matrix getTranslationMatrix(float xt, float yt, float zt) {
    Matrix ret = getIdentityMatrix();
    ret.matrix[0][3] = xt;
    ret.matrix[1][3] = yt;
    ret.matrix[2][3] = zt;
    return ret;
}

Matrix getScaleMatrix(float xs, float ys, float zs) {
    Matrix ret = getZeroMatrix();
    ret.matrix[0][0] = xs;
    ret.matrix[1][1] = ys;
    ret.matrix[2][2] = zs;
    ret.matrix[3][3] = 1.0f;
    return ret;
}

//angle in radians
Matrix getRotationMatrix(const Vector3& axis, float angle) {
    Vector3 raxis = normalize(axis);
    Matrix ret;
    float x = raxis.x(); float y = raxis.y(); float z = raxis.z();
    float cosine = cos(angle);
    float sine = sin(angle);
    float t = 1 - cosine;
    
    ret.matrix[0][0] = t*x*x + cosine;
    ret.matrix[0][1] = t*x*y - sine*y;
    ret.matrix[0][2] = t*x*z + sine*y;
    ret.matrix[0][3] = 0.0f;
    
    ret.matrix[1][0] = t*x*y + sine*z;
    ret.matrix[1][1] = t*y*y + cosine;
    ret.matrix[1][2] = t*y*z - sine*x;
    ret.matrix[1][3] = 0.0f;
    
    ret.matrix[2][0] = t*x*z - sine*y;
    ret.matrix[2][1] = t*y*z + sine*x;
    ret.matrix[2][2] = t*z*z + cosine;
    ret.matrix[2][3] = 0.0f;
    
    ret.matrix[3][0] = 0.0f;
    ret.matrix[3][1] = 0.0f;
    ret.matrix[3][2] = 0.0f;
    ret.matrix[3][3] = 1.0f;
    return ret;

}

Matrix getXRotationMatrix(float angle) {
    Matrix ret = getIdentityMatrix();
    float cosine = cos(angle);
    float sine = sin(angle);
    ret.matrix[1][1] = cosine;
    ret.matrix[1][2] = -sine;
    ret.matrix[2][1] = sine;
    ret.matrix[2][2] = cosine;
    return ret;
}

Matrix getYRotationMatrix(float angle) {
    Matrix ret = getIdentityMatrix();
    float cosine = cos(angle);
    float sine = sin(angle);
    ret.matrix[0][0] = cosine;
    ret.matrix[0][2] = sine;
    ret.matrix[2][0] = -sine;
    ret.matrix[2][2] = cosine;
    return ret;
}

Matrix getZRotationMatrix(float angle) {
    Matrix ret = getIdentityMatrix();
    float cosine = cos(angle);
    float sine = sin(angle);
    ret.matrix[0][0] = cosine;
    ret.matrix[0][1] = -sine;
    ret.matrix[1][0] = sine;
    ret.matrix[1][1] = cosine;
    return ret;
}

Matrix getViewMatrix(const Vector3& eye, const Vector3& gaze, const Vector3& up) {
    Matrix ret = getIdentityMatrix();
    //make orthonormal basis
    Vector3 w = (-normalize(gaze));
    Vector3 u = normalize(cross(up, w));
    Vector3 v = cross(w, u);
    
    ret.matrix[0][0] = u.x();
    ret.matrix[0][1] = u.y();
    ret.matrix[0][2] = u.z();
    
    ret.matrix[1][0] = v.x();
    ret.matrix[1][1] = v.y();
    ret.matrix[1][2] = v.z();
    
    ret.matrix[1][0] = w.x();
    ret.matrix[1][1] = w.y();
    ret.matrix[1][2] = w.z();
    
    //translate eye to xyz origin
    Matrix move = getIdentityMatrix();
    move.matrix[0][3] = -(eye.x());
    move.matrix[1][3] = -(eye.y());
    move.matrix[2][3] = -(eye.z());
    
    ret = ret * move;
    return ret;
}

std::ostream& operator<<(std::ostream& out, const Matrix& right_op) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            out << std::setprecision(3) << std::setw(10) << right_op.matrix[i][j];
            out << std::endl;
        }
    }
    return out;
}
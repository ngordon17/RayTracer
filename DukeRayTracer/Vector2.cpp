//
//  Vector2.cpp
//  RayTracer
//
//  Created by Dustin Alin on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Vector2.h"

Vector2::Vector2(float x, float y) {
    e[0] = x;
    e[1] = y;
}

const Vector2& Vector2::operator+() const {
    return *this;
}

Vector2 Vector2::operator-() const {
    return Vector2(-e[0], -e[1]);
}

float Vector2::magnitude() const {
    return sqrt(e[0]*e[0] + e[1]*e[1]);
}

float Vector2::squaredMagnitude() const {
    return e[0]*e[0] + e[1]*e[1];
}

void Vector2::normalize() {
    *this = *this /(*this).magnitude();
}

float Vector2::minComponent() const {
    if (e[0] < e[1]) return e[0];
    return e[1];
}

float Vector2::maxComponent() const {
    if (e[0] > e[1]) return e[0];
    return e[1];
}

float Vector2::minAbsComponent() const {
    if (fabs(e[0]) < fabs(e[1])) return fabs(e[0]);
    return fabs(e[1]);
}

float Vector2::maxAbsComponent() const {
    if (fabs(e[0]) > fabs(e[1])) return fabs(e[0]);
    return fabs(e[1]);
}

bool operator==(const Vector2& v1, const Vector2& v2) {
    if (v1.x() != v2.x()) return false;
    if (v1.y() != v2.y()) return false;
    return true;
}

bool operator!=(const Vector2& v1, const Vector2& v2) {
    return !(v1 == v2);
}

Vector2 operator+(const Vector2& v1, const Vector2& v2) {
    return Vector2(v1.x() + v2.x(), v1.y() + v2.y());
}

Vector2 operator-(const Vector2& v1, const Vector2& v2) {
    return Vector2(v1.x() - v2.x(), v1.y() - v2.y());
}

Vector2 operator/(const Vector2& v1, float scal) {
    return Vector2(v1.x() / scal, v1.y() / scal);
}

Vector2 operator*(const Vector2& v1, float scal) {
    return Vector2(v1.x() * scal, v1.y() * scal);
}

Vector2 operator*(float scal, const Vector2& v1) {
    return Vector2(v1.x() * scal, v1.y() * scal);
}

Vector2& Vector2::operator=(const Vector2& v2) {
    (*this).setX(v2.x());
    (*this).setY(v2.y());
    return *this;
}

Vector2& Vector2::operator+=(const Vector2& v2) {
    *this = *this + v2;
    return *this;
}

Vector2& Vector2::operator-=(const Vector2& v2) {
    *this = *this - v2;
    return *this;
}

Vector2& Vector2::operator*=(const float scal) {
    *this = *this * scal;
    return *this;
}

Vector2& Vector2::operator/=(const float scal) {
    *this = *this / scal;
    return *this;
}

float determinant(const Vector2& v1, const Vector2& v2) {
    return v1.x() * v2.y() - v1.y() * v2.x();
}

float dot(const Vector2& v1, const Vector2& v2) {
    return v1.x() * v2.x() + v1.y() * v2.y();
}

float findAngle(const Vector2& v1, const Vector2& v2) {
    float dotProduct = dot(v1, v2);
    float cos = v1.magnitude() * v2.magnitude();
    return acos(dotProduct/cos);
}

Vector2 normalize(const Vector2& v) {
    return v / v.magnitude();
}


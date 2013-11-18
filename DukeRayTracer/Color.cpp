//
//  Color.cpp
//  Ray Tracer
//
//  Created by Dustin Alin on 11/1/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Color.h"

Color::Color(float red, float green, float blue) {
    r = red;
    g = green;
    b = blue;
}

Color& Color::operator=(const Color& right_op) {
    r = right_op.getRed();
    g = right_op.getGreen();
    b = right_op.getBlue();
    return *this;
}

Color& Color::operator+=(const Color &right_op) {
    *this = *this + right_op;
    return *this;
}

Color& Color::operator*=(float right_op) {
    *this = *this * right_op;
    return *this;
}

Color& Color::operator/=(float right_op) {
    *this = *this / right_op;
    return *this;
}

Color& Color::operator*=(const Color& right_op) {
    *this = *this * right_op;
    return *this;
}

Color& Color::operator/=(const Color& right_op) {
    *this = *this / right_op;
    return *this;
}

void Color::clamp() {
    if (r > 1.0f) r = 1.0f;
    if (g > 1.0f) g = 1.0f;
    if (b > 1.0f) b = 1.0f;
    
    if (r < 0.0f) r = 0.0f;
    if (g < 0.0f) g = 0.0f;
    if (b < 0.0f) b = 0.0f;
}

//writes the r, g, and b components of a color to an output stream
ostream& operator<<(ostream &out, const Color &the_rgb) {
    out << the_rgb.getRed() << ' '
    << the_rgb.getGreen() << ' '
    << the_rgb.getBlue() << ' ';
    return out;
}

Color operator*(const Color& c, float f) {
    return Color(c.getRed()*f, c.getGreen()*f, c.getBlue()*f);
}

Color operator*(float f, const Color& c) {
    return Color(c.getRed()*f, c.getGreen()*f, c.getBlue()*f);
}

Color operator/(const Color& c, float f) {
    return Color(c.getRed()/f, c.getGreen()/f, c.getBlue()/f);
}

Color operator*(const Color& c1, const Color& c2) {
    return Color(c1.getRed()*c2.getRed(), c1.getGreen()*c2.getGreen(), c1.getBlue()*c2.getBlue());
}

Color operator/(const Color& c1, const Color& c2) {
    return Color(c1.getRed()/c2.getRed(), c1.getGreen()/c2.getGreen(), c1.getBlue()/c2.getBlue());
}

Color operator+(const Color& c1, const Color& c2) {
    return Color(c1.getRed()+c2.getRed(), c1.getGreen()+c2.getGreen(), c1.getBlue()+c2.getBlue());
}
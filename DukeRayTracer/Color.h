 //
//  Color.h
//  Ray Tracer
//
//  Created by Dustin Alin on 11/1/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

//using namespace
//friend?
//inline

#ifndef __RayTracer__Color__
#define __RayTracer__Color__

#include <iostream>

using namespace std;

class Color {
    
public:
    Color() { r = g = b = 0; }
    Color(float red, float green, float blue);
    Color(const Color& original) { *this = original; }
    
    //getters and setters for individual RGB components
    void setRed(float red) { r = red; }
    void setGreen(float green) { g = green; }
    void setBlue(float blue ) { b = blue; }
    float getRed() const { return r; }
    float getGreen() const { return g; }
    float getBlue() const { return b; }
    
    /*
     These are arithmetic operations that operate on an existing color. This utilizes
     overloading operators so that mathematical operations could be used directly on
     Color objects.
     */
    Color& operator=(const Color& right_op);
    Color& operator+=(const Color& right_op);
    Color& operator*=(const Color& right_op);
    Color& operator/=(const Color& right_op);
    Color& operator*=(float right_op);
    Color& operator/=(float right_op);
    Color operator+()const { return *this; }
    Color operator-()const { return Color(-r, -g, -b); }
    
    void clamp();
    
    friend ostream& operator<<(ostream &ut, const Color &the_rgb);
    
    //arithmetic operations that result in a new Color
    friend Color operator*(const Color& c, float f);
    friend Color operator*(float f, const Color& c);
    friend Color operator/(const Color& c, float f);
    friend Color operator*(const Color& c1, const Color& c2);
    friend Color operator/(const Color& c1, const Color& c2);
    friend Color operator+(const Color& c1, const Color& c2);
    
    
private:
    float r;
    float g;
    float b;
    
};

#endif /* defined(__Ray_Tracer__Color__) */

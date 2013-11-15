//
//  ONB.h
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#ifndef __RayTracer__ONB__
#define __RayTracer__ONB__

#include <iostream>
#include "Vector3.h"

class ONB {
public:
    ONB() {}
    ONB(const Vector3& a, const Vector3& b, const Vector3& c) {U = a; V = b; W= c;}
    void initFromU(const Vector3& u);
    void initFromV(const Vector3& v);
    void initFromW(const Vector3& w);
    
    void set(const Vector3& a, const Vector3& b,  const Vector3& c) {U = a; V = b; W = c;}
    
    void initFromUV(const Vector3& u, const Vector3& v);
    void initFromVU(const Vector3& v, const Vector3& u);
    void initFromUW(const Vector3& u, const Vector3& w);
    void initFromWU(const Vector3& w, const Vector3& u);
    void initFromVW(const Vector3& v, const Vector3& w);
    void initFromWV(const Vector3& w, const Vector3& v);
  
    friend bool operator==(const ONB& o1, const ONB& o2);
    
    Vector3 u() const {return U;}
    Vector3 v() const {return V;}
    Vector3 w() const {return W;}
    
private:
    Vector3 U,V,W;
    
};




#endif /* defined(__RayTracer__ONB__) */

//
//  Triangle.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "Triangle.h"
#include "SimpleTexture.h"

Triangle::Triangle(const Vector3& p0, const Vector3& p1, const Vector3& p2, const Color& rgb) {
    v0 = p0; v1 = p1; v2 = p2;
    color = rgb;
}

bool Triangle::intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const {
    float tval;
    //using barycentric coordinates
    float A = v0.x() - v1.x(); float B = v0.y() - v1.y(); float C = v0.z() - v1.z();
    float D = v0.x() - v2.x(); float E = v0.y() - v2.y(); float F = v0.z() - v2.z();
    float G = r.direction().x(); float H = r.direction().y(); float I = r.direction().z();
    float J = v0.x() - r.origin().x(); float K = v0.y() - r.origin().y(); float L = v0.z() - r.origin().z();
    
    //calculate beta and gamma which parameterize a nonorthogonal coordinate system on the triangle plane
    float EIHF = E*I - H*F; float GFDI = G*F - D*I; float DHEG = D*H - E*G;
    float denom = A*EIHF + B*GFDI + C*DHEG;
    float beta  = (J*EIHF + K*GFDI + L*DHEG) / denom;
    //if beta <= 0 || beta + gamma >= 1 (i.e. true if beta >= 1) then no points in triangle
    if (beta <= 0.0f || beta >= 1.0f) {return false;}
    
    float AKJB = A*K - J*B; float JCAL = J*C - A*L; float BLKC = B*L - K*C;
    float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
     //if gamma <= 0 || beta + gamma >= 1 (i.e. true if gamma >= 1) then no points in triangle
    if (gamma <= 0.0f || beta + gamma >= 1.0f) {return false;}
    
    tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    //if t is not between our min and our max values then ignore
    if (tval >= tmin && tval <= tmax) {
        record.t = tval;
        record.normal = normalize(cross((v1 - v0), (v2 - v0)));
        record.tex = new SimpleTexture(color);
        return true;
    }
    
    return false;
}

bool Triangle::shadowIntersect(const Ray& r, float tmin, float tmax, float time) const {
    float tval;
    //using barycentric coordinates
    float A = v0.x() - v1.x(); float B = v0.y() - v1.y(); float C = v0.z() - v1.z();
    float D = v0.x() - v2.x(); float E = v0.y() - v2.y(); float F = v0.z() - v2.z();
    float G = r.direction().x(); float H = r.direction().y(); float I = r.direction().z();
    float J = v0.x() - r.origin().x(); float K = v0.y() - r.origin().y(); float L = v0.z() - r.origin().z();
    
    //calculate beta and gamma which parameterize a nonorthogonal coordinate system on the triangle plane
    float EIHF = E*I - H*F; float GFDI = G*F - D*I; float DHEG = D*H - E*G;
    float denom = A*EIHF + B*GFDI + C*DHEG;
    float beta  = (J*EIHF + K*GFDI + L*DHEG) / denom;
    //if beta <= 0 || beta + gamma >= 1 (i.e. true if beta >= 1) then no points in triangle
    if (beta <= 0.0f || beta >= 1.0f) {return false;}
    
    float AKJB = A*K - J*B; float JCAL = J*C - A*L; float BLKC = B*L - K*C;
    float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    //if gamma <= 0 || beta + gamma >= 1 (i.e. true if gamma >= 1) then no points in triangle
    if (gamma <= 0.0f || beta + gamma >= 1.0f) {return false;}
    
    tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    return (tval >= tmin && tval <= tmax);
}

BBox Triangle::boundingBox(float time0, float time1) const {
    //TODO: implement
    return bbox;
}

bool Triangle::randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const {
    float temp = sqrt(1.0f - seed.x());
    float beta = (1.0f - temp);
    float gamma = temp*seed.y();
    light_point = (1.0f - beta - gamma) * v0 + beta * v1 + gamma * v2;
    Vector3 from_light = normalize(viewpoint - light_point);
    ONB uvw;
    N = normalize(cross((v1 - v0), (v2 - v0)));
    uvw.initFromW(N);
    radiance = mptr -> emittedRadiance(uvw, from_light, light_point, Vector2(0.0f, 0.0f));
    return true;
}








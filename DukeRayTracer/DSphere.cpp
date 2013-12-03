//
//  DSphere.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/7/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "DSphere.h"
#include "SimpleTexture.h"
#include <cfloat>

DSphere::DSphere(const Vector3& oc, float r, SimpleMaterial* mat, float min_time, float max_time) {
    ocenter = Vector3(oc); radius = float(r); mptr = mat;
    mintime = float(min_time); max_time = float(max_time);
}

bool DSphere::intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const {
    Vector3 center = getCenter(time);
    Vector3 temp = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2*dot(r.direction(), temp);
    double c = dot(temp, temp) - radius*radius;
    //discriminant of quadratic equation -- check if > 0 to determine number roots/interesctions
    double discriminant = b*b - 4*a*c;
    
    if (discriminant > 0) {//ray intersects sphere at two places
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2*a);
        if ( t < tmin) {t = (-b + discriminant) / (2*a);} //check if t is within tmin and tmax
        if (t < tmin || t > tmax) {return false;} //t is not within valid interval
        
        //have a valid intersection
        record.t = t;
        record.uvw.initFromW(normalize(r.origin() + t*r.direction() - center));
        record.material = mptr;
        return true;
    }
    return false;
}

bool DSphere::shadowIntersect(const Ray& r, float tmin, float tmax, float time) const {
    Vector3 center = getCenter(time);
    Vector3 temp = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2*dot(r.direction(), temp);
    double c = dot(temp, temp) - radius*radius;
    
    //discriminant of quadratic equation -- check if > 0 to determin number roots/interesctions
    double discriminant = b*b - 4*a*c;
    
    if (discriminant > 0) {//ray intersects sphere at two places
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2*a);
        if (t < tmin) {t = (-b + discriminant) / (2*a);} //check if t is within tmin and tmax
        if (t < tmin || t > tmax) {return false;} //t is not within valid interval
        
        //have a valid interesction
        return true;
    }
    return false;
}

Vector3 DSphere::getCenter(float t) const {
    float realtime = t * maxtime + (1.0f - t) * mintime;
    return Vector3(ocenter.x() + realtime, ocenter.y() + realtime, ocenter.x() + realtime);
}

BBox DSphere::boundingBox(float time0, float time1) const {
    //TODO: implement
    return bbox;
}

/*
bool DSphere::randomPoint(const Vector3 &viewpoint, const Vector2 &seed, float time, Vector3 &light_point, Vector3 &N, float &pdf, Color &radiance) const {
    float d = (viewpoint - getCenter(0)).magnitude();
    if (d < radius) {return false;}
    float r = radius;
    //internal angle of cone surrounding light seen from viewpoint
    float sin_alpha_max = r / d;
    float cos_alpha_max = sqrt(1 - sin_alpha_max * sin_alpha_max);
    float q = 1.0 / (2*M_PI*(1 - cos_alpha_max));
    float cos_alpha = 1 + seed.x() * (cos_alpha_max - 1);
    float sin_alpha = sqrt(1 - cos_alpha * cos_alpha);
    float phi = 2*M_PI*seed.y();
    float cos_phi = cos(phi);
    float sin_phi = sin(phi);
    Vector3 k_i(cos_phi * sin_alpha, sin_phi * sin_alpha, cos_alpha);
    //construct local coordinate system UVW where viewpoint at origin and sphere at (0,0,d) in UVW
    ONB UVW;
    UVW.initFromW(getCenter(0) - viewpoint);
    Ray to_light(viewpoint, k_i.x() * UVW.u() + k_i.y() * UVW.v() + k_i.z() * UVW.w());
    
    IntersectRecord rec;
    if (this -> intersect(to_light, 0.00001, FLT_MAX, time, rec)) {
        light_point = rec.intersection;
        float cos_theta_prime = -dot(rec.uvw.w(), to_light.direction());
        pdf = q * cos_theta_prime / (light_point - viewpoint).squaredMagnitude();
        N = rec.uvw.w();
        radiance = mptr -> emittedRadiance(rec.uvw, -to_light.direction(), light_point, rec.uv);
        return true;
    }
    return false;
}
*/

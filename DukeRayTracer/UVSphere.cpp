//
//  UVSphere.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "UVSphere.h"
#include "SimpleTexture.h"
#include <cfloat>


UVSphere::UVSphere(const Vector3& c, float r, SimpleMaterial* mat) {
    center = Vector3(c); radius = float(r); mptr = mat;
}

bool UVSphere::intersect(const Ray& r, float tmin, float tmax, float time, IntersectRecord& record) const {
    Vector3 temp = r.origin() - center;
    double a = dot(r.direction(), r.direction());
    double b = 2*dot(r.direction(), temp);
    double c = dot(temp, temp) - radius*radius;
    double discriminant = b*b - 4.0*a*c;
    
    if (discriminant > 0.0f) {
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2.0*a);
        if (t < tmin) {t = (-b + discriminant) / (2.0*a);}
        if (t < tmin || t > tmax) {return false;}
        
        //valid intersection
        record.t = t;
        record.intersection = r.pointAtParameter(t);
        Vector3 n = record.uvw.w() = (record.intersection - center) / radius;
        
        //calculate UV coords
        float two_pi = 6.28318530718f;
        float theta = acos(n.z());
        float phi = atan2(n.y(), n.x());
        if (phi < 0.0f) {phi += two_pi;}
        
        float one_over_two_pi = .159154943092f;
        float one_over_pi = .3183098861874f;
        
        record.uv = Vector2(phi*one_over_two_pi, (M_PI - theta) * one_over_pi);
        record.material = mptr;
        return true;
    }
    return false;
}

bool UVSphere::shadowIntersect(const Ray& r, float tmin, float tmax, float time) const {
    Vector3 temp = r.origin() - center;
    
    double a = dot(r.direction(), r.direction());
    double b = 2*dot(r.direction(), temp);
    double c = dot(temp, temp) - radius*radius;
    
    double discriminant = b*b - 4*a*c;
    
    //check if ray intersects sphere
    
    if (discriminant > 0) {
        discriminant = sqrt(discriminant);
        double t = (-b - discriminant) / (2.0*a);
        if (t < tmin) {t = (-b + discriminant) / (2.0*a);}
        if (t < tmin || t > tmax) {return false;}
        
        //valid intersection
        return true;
    }
    return false;
}

BBox UVSphere::boundingBox(float time0, float time1) const {
    //TODO: implement
    return bbox;
}

/*
bool UVSphere::randomPoint(const Vector3 &viewpoint, const Vector2 &seed, float time, Vector3 &light_point, Vector3 &N, float &pdf, Color &radiance) const {
    float d = (viewpoint - center).magnitude();
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
    UVW.initFromW(center - viewpoint);
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
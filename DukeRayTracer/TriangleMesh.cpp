//
//  TriangleMesh.cpp
//  RayTracer
//
//  Created by Nicholas Gordon on 11/11/13.
//  Copyright (c) 2013 Dustin Alin. All rights reserved.
//

#include "TriangleMesh.h"
#include "Mesh.h"
#include "Texture.h"

MeshTriangleUV::MeshTriangleUV() {}

MeshTriangleUV::MeshTriangleUV(Mesh* m, int v0, int v1, int v2, int index) : mesh(m) {
    verts[0] = v0; verts[1] = v1; verts[2] = v2;
}

MeshTriangleUV::~MeshTriangleUV() {}

bool MeshTriangleUV::intersect(const Ray&r, float tmin, float tmax, float time, IntersectRecord& record) const {
    Vector3 v0((mesh -> vertUVs[verts[0]]).vertex);
    Vector3 v1((mesh -> vertUVs[verts[1]]).vertex);
    Vector3 v2((mesh -> vertUVs[verts[2]]).vertex);
    
    float A = v0.x() - v1.x(); float B = v0.y() - v1.y(); float C = v0.z() - v1.z();
    float D = v0.x() - v2.x(); float E = v0.y() - v2.y(); float F = v0.z() - v2.z();
    float G = r.direction().x(); float H = r.direction().y(); float I = r.direction().z();
    float J = v0.x() - r.origin().x(); float K = v0.y() - r.origin().y(); float L = v0.z() - r.origin().z();
    float EIHF = E*I-H*F; float GFDI = G*F-D*I; float DHEG = D*H-E*G;
    
    float denom = (A*EIHF + B*GFDI + C*DHEG);
    float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
    if (beta <= 0.0f || beta >= 1.0f) {return false;}
    
    float AKJB = A*K-J*B; float JCAL = J*C-A*L; float BLKC = B*L-K*C;
    
    float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    if (gamma <= 0.0f || beta + gamma >= 1.0f) {return false;}
    
    float tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    if (tval >= tmin && tval <= tmax) {
        double alpha = 1.0 - beta - gamma;
        Vector2 u0((mesh -> vertUVs[verts[0]]).uv);
        Vector2 u1((mesh -> vertUVs[verts[1]]).uv);
        Vector2 u2((mesh -> vertUVs[verts[2]]).uv);
        record.uv = Vector2(alpha*u0.x() + beta*u1.x() + gamma*u2.x(), alpha*u0.y() + beta*u1.y() + gamma*u2.y());
        record.t = tval;
        record.material = mptr;
        record.uvw.initFromW(normalize(cross((v1 - v0), (v2 - v0))));
        return true;
    }
    return false;
}

bool MeshTriangleUV::shadowIntersect(const Ray& r, float tmin, float tmax, float time) const {
    Vector3 v0((mesh -> vertUVs[verts[0]]).vertex);
    Vector3 v1((mesh -> vertUVs[verts[1]]).vertex);
    Vector3 v2((mesh -> vertUVs[verts[2]]).vertex);
    
    float A = v0.x() - v1.x(); float B = v0.y() - v1.y(); float C = v0.z() - v1.z();
    float D = v0.x() - v2.x(); float E = v0.y() - v2.y(); float F = v0.z() - v2.z();
    float G = r.direction().x(); float H = r.direction().y(); float I = r.direction().z();
    float J = v0.x() - r.origin().x(); float K = v0.y() - r.origin().y(); float L = v0.z() - r.origin().z();
    float EIHF = E*I-H*F; float GFDI = G*F-D*I; float DHEG = D*H-E*G;
    
    float denom = (A*EIHF + B*GFDI + C*DHEG);
    float beta = (J*EIHF + K*GFDI + L*DHEG) / denom;
    if (beta <= 0.0f || beta >= 1.0f) {return false;}
    
    float AKJB = A*K-J*B; float JCAL = J*C-A*L; float BLKC = B*L-K*C;
    
    float gamma = (I*AKJB + H*JCAL + G*BLKC) / denom;
    if (gamma <= 0.0f || beta + gamma >= 1.0f) {return false;}
    float tval = -(F*AKJB + E*JCAL + D*BLKC) / denom;
    return tval >= tmin && tval <= tmax;
}

BBox MeshTriangleUV::boundingBox(float time0, float time1) const {
    //TODO: implement
    return bbox;
}

/*
bool MeshTriangleUV::randomPoint(const Vector3& viewpoint, const Vector2& seed, float time, Vector3& light_point, Vector3& N, float& pdf, Color& radiance) const {
    Vector3 v0((mesh -> vertUVs[verts[0]]).vertex);
    Vector3 v1((mesh -> vertUVs[verts[1]]).vertex);
    Vector3 v2((mesh -> vertUVs[verts[2]]).vertex);
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
*/

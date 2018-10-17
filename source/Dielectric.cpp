
#include "Dielectric.h"

using namespace rtow::render;

Dielectric::Dielectric (
    float p_ri
) {
    m_refIdx = p_ri;
}

bool 
Dielectric::scatter (
    Ray p_rayIn, 
    Intersection p_record, 
    Vector3 &p_attenuation,
    Ray &p_scattered
) {
    p_attenuation = Vector3(1,1,1);

    Vector3 reflected = reflect(p_rayIn.direction(), p_record.normal);
    Vector3 refracted;
    
    Vector3 outwardNormal;

    float refractiveIndex;
    float reflectedProb;
    float cosine;
    
    if (dot(p_rayIn.direction(), p_record.normal) > 0) {
        outwardNormal = -1.0f * p_record.normal;
        refractiveIndex = m_refIdx;
        cosine = m_refIdx * dot(p_rayIn.direction(), p_record.normal) / length(p_rayIn.direction()); 
    } else {
        outwardNormal = p_record.normal;
        refractiveIndex = 1.0f / m_refIdx;
        cosine = -dot(p_rayIn.direction(), p_record.normal) / length(p_rayIn.direction());
    }
    
    if (refract(p_rayIn.direction(), outwardNormal, refractiveIndex, refracted)) {
        reflectedProb = schlick(cosine, m_refIdx);
    } else {
        reflectedProb = 1.0f;
    }
    
    if (rand() / float(RAND_MAX) < reflectedProb) {
        p_scattered = Ray(p_record.point, reflected);
    } else {
        p_scattered = Ray(p_record.point, refracted);
    }
    
    return true;
}

float
Dielectric::schlick (
    float p_cosine,
    float p_refIdx
) {
    float r0 = (1-p_refIdx) / (1 + p_refIdx);
    r0 = pow(r0,2);
    
    return r0 + (1-r0) * pow((1-p_cosine), 5);
}

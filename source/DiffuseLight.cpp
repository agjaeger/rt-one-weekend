
#include "DiffuseLight.h"

using namespace rtow::render;

DiffuseLight::DiffuseLight (
    Texture *p_emissive
) {
    m_emissive = p_emissive;
}

DiffuseLight::~DiffuseLight () {
    free(m_emissive);
}

bool 
DiffuseLight::scatter (
    Ray p_rayIn, 
    Intersection p_record, 
    Vector3 &p_attenuation, 
    Ray &p_scattered
) {
    return false;
}

Vector3 
DiffuseLight::emitted (
    float p_ssU, 
    float p_ssV, 
    Vector3 p_wsPoint
) {
    return m_emissive->value(p_ssU, p_ssV, p_wsPoint);
}
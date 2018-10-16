
#include "Lambertian.h"

using namespace rtow::render;

Lambertian::Lambertian (
    Texture *p_albedo
) {
    m_albedo = p_albedo;
}

Lambertian::~Lambertian () {
    free(m_albedo);
}

bool
Lambertian::scatter (
    Ray p_rayIn, 
    Intersection p_record, 
    Vector3 &p_attenuation, 
    Ray &p_scatterOut
) {
    p_attenuation = m_albedo->value(0, 0, p_record.point);
    p_scatterOut = Ray(
        p_record.point, 
        p_record.normal
    );

    return true;
}
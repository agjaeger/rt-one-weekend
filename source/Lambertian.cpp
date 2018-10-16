
#include "Lambertian.h"

using namespace rtow::render;

#include <iostream>

Lambertian::Lambertian (
    Vector3 p_albedo
) {
    m_albedo = p_albedo;
}

bool
Lambertian::scatter (
    Ray p_rayIn, 
    Intersection p_record, 
    Vector3 &p_attenuation, 
    Ray &p_scatterOut
) {
//    std::cout << "in scatter" << std::endl;

    p_attenuation = m_albedo;
    p_scatterOut = Ray(
        p_record.point, 
        p_record.normal
    );

    return true;
}
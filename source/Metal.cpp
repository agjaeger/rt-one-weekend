
#include "Metal.h"

using namespace rtow::render;

Metal::Metal (
    Texture *p_albedo
) {
    m_albedo = p_albedo;
}

Metal::~Metal () {
    free(m_albedo);
}

bool 
Metal::scatter (
    Ray p_rayIn, 
    Intersection p_record, 
    Vector3 &p_attentuation,
    Ray &p_scatterOut
) {
    Vector3 reflected = reflect(unitVector(p_rayIn.direction()), p_record.normal);
    
    p_scatterOut = Ray(p_record.point, reflected);
    p_attentuation = m_albedo->value(0,0,p_record.point);
    
    return (dot(p_scatterOut.direction(), p_record.normal) > 0);
}

#include "Camera.h"

using namespace::rtow::render;

Camera::Camera (
    Vector3 p_lookfrom,
    Vector3 p_lookat,
    Vector3 p_vup,
    float p_vfov,
    float p_aspect,
    float p_aperature,
    float p_focusPlaneDist
) {
    float theta = p_vfov * (M_PI / 180.0f);
    float halfHeight = tan(theta/2);
    float halfWidth = p_aspect * halfHeight;

    Vector3 w = unitVector(p_lookfrom - p_lookat);
    Vector3 u = unitVector(cross(p_vup, w));
    Vector3 v = cross(w, u);

    m_lensRadius = p_aperature / 2;
    m_origin = p_lookfrom;
    m_wsLowerLeft = m_origin - halfWidth * p_focusPlaneDist * u - halfHeight * p_focusPlaneDist * v - p_focusPlaneDist * w;
    m_wsHorizontal = 2 * halfWidth * p_focusPlaneDist * u;
    m_wsVertical =  2 * halfHeight * p_focusPlaneDist * v;
}

Ray
Camera::getRay (
    float p_ssU,    // screen space u coord
    float p_ssV     // screen space v coord
) {
    Vector3 radDir = m_lensRadius * Random::unitDisk();
    float offset = p_ssU * radDir.x() + p_ssV * radDir.y();
    
    return Ray (
        m_origin + offset, 
        m_wsLowerLeft + p_ssU * m_wsHorizontal + p_ssV * m_wsVertical - m_origin - offset
    );
}
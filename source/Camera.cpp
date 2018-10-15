
#include "Camera.h"

Ray
rtow::render::Camera::getRay (
    float p_ssU,    // screen space u coord
    float p_ssV     // screen space v coord
) {
    return Ray(m_origin, m_wsLowerLeft + p_ssU * m_wsHorizontal + p_ssV * m_wsVertical);
}
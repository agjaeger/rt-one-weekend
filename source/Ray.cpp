
#include "Ray.h"

Ray::Ray (
    Vector3 p_origin, 
    Vector3 p_dir
) {
    m_origin = p_origin;
    m_direction = p_dir;
}

Vector3
Ray::origin () {
    return m_origin;
}

Vector3
Ray::direction () {
    return m_direction;
}

Vector3
Ray::at(
    float p_t
) {
    return m_origin + p_t * m_direction;
}

#include "ConstantTexture.h"

using namespace rtow::render;

ConstantTexture::ConstantTexture(
    Vector3 p_rgb
) {
    m_color = p_rgb;
}

Vector3
ConstantTexture::value (
    float p_ts_x, 
    float p_ts_y, 
    Vector3 p_ws_xyz
) {
    return m_color;
}
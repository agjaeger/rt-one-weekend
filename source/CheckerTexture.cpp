
#include "CheckerTexture.h"

using namespace rtow::render;

CheckerTexture::CheckerTexture (
    Texture *p_even,
    Texture *p_odd
) {
    m_even = p_even;
    m_odd = p_odd;
}

CheckerTexture::~CheckerTexture () {
    free(m_even);
    free(m_odd);
}

Vector3
CheckerTexture::value (
    float p_ts_x,
    float p_ts_y,
    Vector3 p_ws_xyz
) {
    int tileWidth = 10;
    float sines = 
        sin(tileWidth * p_ws_xyz.x()) 
      * sin(tileWidth * p_ws_xyz.y())
      * sin(tileWidth * p_ws_xyz.z());

    if (sines < 0) {
        return m_odd->value(p_ts_x, p_ts_y, p_ws_xyz);
    }  else {
        return m_even->value(p_ts_x, p_ts_y, p_ws_xyz);
    }
}
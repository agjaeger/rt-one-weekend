
#pragma once

#include "Vector3.h"
#include "Texture.h"

namespace rtow {
    namespace render {
        class ConstantTexture : public Texture {
            public:
                ConstantTexture (Vector3 rgb);
                virtual Vector3 value (float ts_x, float ts_y, Vector3 ws_xyz);
            
            private:
                Vector3 m_color;
        };
    };
};

#pragma once

#include "Vector3.h"

using namespace rtow::math;

namespace rtow {
    namespace render {
        class Texture {
            public:
                virtual Vector3 value (float ts_x, float ts_y, Vector3 ws_xyz) = 0;
        };
    };
};
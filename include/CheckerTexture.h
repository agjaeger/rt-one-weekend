
#pragma once

#include "Texture.h"

namespace rtow {
    namespace render {
        class CheckerTexture : public Texture {
            public:
                CheckerTexture (Texture *even, Texture *odd);
                ~CheckerTexture();

                virtual Vector3 value (float ts_x, float ts_y, Vector3 ws_xyz);

            private:
                Texture *m_even;
                Texture *m_odd;
        };
    };
};
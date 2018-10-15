
#pragma once

#include "Vector3.h"
#include "Ray.h"

namespace rtow {
    namespace render {
        class Camera {
            public:
                Ray getRay (float u, float v);

            private:
                Vector3 m_origin = Vector3(0,0,0);
                Vector3 m_wsLowerLeft = Vector3(-2, -1, -1);
                Vector3 m_wsHorizontal = Vector3(4, 0, 0);
                Vector3 m_wsVertical = Vector3(0, 2, 0);        
        };
    };
};

#pragma once

#include "Vector3.h"

using namespace rtow::math;

namespace rtow {
    namespace math {
        class Ray {
            public:
                Ray();
                Ray(Vector3 origin, Vector3 dir);

                Vector3 origin();
                Vector3 direction();
                Vector3 at(float t);

            private:
                Vector3 m_origin;
                Vector3 m_direction;
        };
    };
};